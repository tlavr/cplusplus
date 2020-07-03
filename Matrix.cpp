#include <iostream>
#include <vector>
#include <array>
#include <memory>

using namespace std;

class Matrix {
protected:
	double** mtx;
	int rows;
	int cols;

public:
	static short copyCnt;
	static short constEmptyCnt;
	static short constSpecCnt;
	static short constDataCnt;
	static short destrCnt;
	static short eqCnt;

	Matrix() : mtx(nullptr), rows(0), cols(0) {
		cout << "Empty matrix constructor called!" << endl;
		++constEmptyCnt;
	};
	Matrix(const int& rows, const int& cols) {
		this->rows = rows;
		this->cols = cols;
		this->mtx = new double*[rows];
		for (int ii = 0; ii < rows; ++ii) {
			this->mtx[ii] = new double[cols];
			for (int jj = 0; jj < cols; ++jj)
				this->mtx[ii][jj] = 0;
		}
		cout << "Specified matrix constructor called!" << endl;
		++constSpecCnt;
	}
	Matrix(const int& rows, const int& cols, double** data) {
		this->rows = rows;
		this->cols = cols;
		this->mtx = new double* [rows];
		for (int row = 0; row < this->rows; ++row) {
			this->mtx[row] = new double[cols];
			for (int col = 0; col < this->cols; ++col)
				this->mtx[row][col] = data[row][col];
		}
		cout << "Data Specified  matrix constructor called!" << endl;
		++constDataCnt;
	}
	~Matrix() {
		this->clearMtx();
		cout << "Matrix desctructor called!" << endl;
		++destrCnt;
	}
	Matrix(const Matrix& B) : Matrix(B.rows, B.cols, B.mtx) {
		cout << "Matrix copy constructor called!" << endl;
		++copyCnt;
	}
	void clearMtx() {
		for (int ii = 0; ii < this->rows; ++ii)
			delete[] this->mtx[ii];
		delete[] this->mtx;
	}

	friend Matrix operator+(const Matrix& A, const Matrix& B);
	friend Matrix operator+(const Matrix& A, const double& value);
	friend Matrix operator*(const Matrix& A, const Matrix& B);
	friend Matrix operator*(const Matrix& A, const double& value);
	Matrix operator=(const Matrix& B) {
		this->clearMtx();
		this->rows = B.rows;
		this->cols = B.cols;
		this->mtx = new double* [this->rows];
		for (int ii = 0; ii < B.rows; ++ii) {
			this->mtx[ii] = new double[this->cols];
			for (int jj = 0; jj < B.cols; ++jj)
				this->mtx[ii][jj] = B.mtx[ii][jj];
		}
		cout << "= operator called!" << endl;
		++eqCnt;
		return Matrix(*this);
	}

	void printMtx() {
		for (int row = 0; row < this->rows; ++row) {
			for (int col = 0; col < this->cols; ++col)
				cout << this->mtx[row][col] << "\t\t";
			cout << endl << endl;
		}
	}
	void setValue(const int& row, const int& col, const double& value) {
		if (row >= this->rows || col >= this->cols)
			return;
		this->mtx[row][col] = value;
	}
	void makeUnit() {
		for (int row = 0; row < this->rows; ++row) {
			for (int col = 0; col < this->cols; ++col){
				if (row == col)
					this->setValue(row, col, 1);
				else
					this->setValue(row, col, 0);
			}
		}
	}
	void transpose() {
		Matrix tmp(*this);
		this->clearMtx();
		this->rows = tmp.cols;
		this->cols = tmp.rows;
		this->mtx = new double* [this->rows];
		for (int ii = 0; ii < this->rows; ++ii) {
			this->mtx[ii] = new double[this->cols];
			for (int jj = 0; jj < this->cols; ++jj)
				this->mtx[ii][jj] = tmp.mtx[jj][ii];
		}
	}
	double det() {
		if (this->rows != this->cols) {
			cout << " Matrix is not square!" << endl;
			return 0;
		}
		Matrix B(*this);
		double coeff = 0;
		//приведение матрицы к верхнетреугольному виду
		for (int step = 0; step < this->cols - 1; ++step)
			for (int row = step + 1; row < this->cols; ++row) {
				coeff = -B.mtx[row][step] / B.mtx[step][step]; //метод Гаусса
				for (int col = step; col < this->cols; col++)
					B.mtx[row][col] += B.mtx[step][col] * coeff;
			}
		B.printMtx();
		//Рассчитать определитель как произведение элементов главной диагонали
		double detOut = 1;
		for (int ii = 0; ii < this->cols; ++ii)
			detOut *= B.mtx[ii][ii];
		return detOut;
	}
	Matrix getInversedMtx() {
		if (this->rows != this->cols) {
			cout << " Matrix is not square!" << endl;
			return Matrix();
		}
		/* Численное вычисление обратной матрицы по методу Ньютона-Шульца
	   1. Записать начальное приближение [Pan, Schreiber]:
		   1) Транспонировать данную матрицу
		   2) Нормировать по столбцам и строкам
	   2. Повторять процесс до достижения заданной точности.
   */

		double N1 = 0, Ninf = 0; //норма матрицы по столбцам и по строкам
		Matrix A0(*this);       //инициализация начального приближения
		for (int row = 0; row < this->cols; ++row) {
			double colsum = 0, rowsum = 0;
			for (int col = 0; col < this->cols; ++col) {
				rowsum += fabs(A0.mtx[row][col]);
				colsum += fabs(A0.mtx[col][row]);
			}
			N1 = std::max(colsum, N1);
			Ninf = std::max(rowsum, Ninf);
		}
		//транспонирование
		A0.transpose();
		A0 = A0 * (1 / (N1 * Ninf)); //нормирование матрицы
		//инициализация удвоенной единичной матрицы нужного размера
		Matrix E2(this->cols, this->cols);
		E2.makeUnit();
		E2 = E2 * 2;
		
		Matrix inv(A0);
		double eps = 0.000001;   //погрешность

		if (this->det() != 0) { //если матрица не вырождена
			while (fabs(((*this) * (inv)).det() - 1) >= eps) //пока |det(A * A[k](^-1)) - 1| >= EPS
			{
				Matrix prev((inv)); //A[k-1]
				inv = (((*this) * prev) * -1 + E2);   //2E - A.(A[k-1]^(-1))                 
				inv = (prev * (inv)); //(A[k-1]^(-1)).(2E - A.(A[k-1]^(-1)))
			}
			return Matrix(inv);
		}
		else
			cout << "Impossible" << endl;
		return Matrix();
	}
};

Matrix operator+(const Matrix& A, const Matrix& B) {
	if (A.rows != B.rows || A.cols != B.cols) {
		cout << "+ operator dimensions mismatch!" << endl;
		return Matrix();
	}

	Matrix out(A);
	for (int row = 0; row < out.rows; ++row)
		for (int col = 0; col < out.cols; ++col)
			out.mtx[row][col] += B.mtx[row][col];
	return Matrix(out);
}
Matrix operator+(const Matrix& A, const double& value) {
	Matrix out(A);
	for (int row = 0; row < out.rows; ++row)
		for (int col = 0; col < out.cols; ++col)
			out.mtx[row][col] += value;
	return Matrix(out);
}
Matrix operator*(const Matrix& A, const Matrix& B){
	if (A.cols != B.rows) {
		cout << "* operator dimensions mismatch!" << endl;
		return Matrix();
	}
	Matrix out(A.rows, B.cols);
	for (int row = 0; row < A.rows; ++row)
		for (int col = 0; col < B.cols; ++col)
			for (int ii = 0; ii < A.cols; ++ii)
				out.mtx[row][col] += A.mtx[row][ii] * B.mtx[ii][col];
	return Matrix(out);
}
Matrix operator*(const Matrix& A, const double& value){
	Matrix out(A);
	for (int row = 0; row < out.rows; ++row)
		for (int col = 0; col < out.cols; ++col)
			out.mtx[row][col] *= value;
	return Matrix(out);
}

short Matrix::copyCnt = 0;
short Matrix::constEmptyCnt = 0;
short Matrix::constSpecCnt = 0;
short Matrix::constDataCnt = 0;
short Matrix::destrCnt = 0;
short Matrix::eqCnt = 0;

int main() {
	int r = 3;
	int c = 3;
	// matrix data generation
	double** tmp;
	tmp = new double* [r];
	for (int ii = 0; ii < r; ++ii)
		tmp[ii] = new double[c];
	
	for (int ii = 0; ii < r; ++ii)
		for (int jj = 0; jj < c; ++jj) {
			tmp[ii][jj] = (double)ii + 2;
		}

	Matrix mtx1(r, c);
	double inpVal;
	for (int ii = 0; ii < r; ++ii)
		for (int jj = 0; jj < c; ++jj) {
			cout << "Input mtx value:";
			cin >> inpVal;
			mtx1.setValue(ii, jj, inpVal);
		}
	cout << "Your matrix: " << endl;
	mtx1.printMtx();
	cout << "Matrix det is:\t" << mtx1.det() << endl;

	Matrix mtx1Inv(mtx1.getInversedMtx());
	cout << "Inversed matrix: " << endl;
	mtx1Inv.printMtx();

	cout << "A * A^-1: " << endl;
	(mtx1 * mtx1Inv).printMtx();

	cout << "Copy count:\t" << Matrix::copyCnt << endl;
	cout << "Constructor count:\t" << Matrix::constEmptyCnt << endl;
	cout << "Spec constructor count:\t" << Matrix::constSpecCnt << endl;
	cout << "Data constructor count:\t" << Matrix::constDataCnt << endl;
	cout << "Destructor count:\t" << Matrix::destrCnt << endl;
	cout << "= count:\t" << Matrix::eqCnt << endl;

	for (int ii = 0; ii < r; ++ii)
		delete[] tmp[ii];
	delete[] tmp;
	return 0;
}