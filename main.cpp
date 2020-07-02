#include <iostream>
#include <vector>
#include <array>

using namespace std;

class Matrix {
protected:
	double** mtx;
	int rows;
	int cols;

public:
	Matrix() : mtx(nullptr), rows(0), cols(0) {
		cout << "Empty matrix constructor called!" << endl;
	};

	Matrix(int rows, int cols) {
		this->rows = rows;
		this->cols = cols;
		mtx = new double*[rows];
		for (int ii = 0; ii < rows; ++ii) {
			double* tmp = new double[cols];
			for (int jj = 0; jj < cols; ++jj)
				tmp[jj] = 0;
			mtx[ii] = tmp;
		}
		cout << "Specified matrix constructor called!" << endl;
	}
	
	Matrix(int rows, int cols, double** data) : Matrix(rows, cols) {
		for (int row = 0; row < this->rows; ++row)
			for (int col = 0; col < this->cols; ++col)
				this->mtx[row][col] = data[row][col];
		cout << "Data Specified  matrix constructor called!" << endl;
	}
	~Matrix() {
		this->clearMtx();
		cout << "Matrix desctructor called!" << endl;
	}

	Matrix(const Matrix& B) : Matrix(B.rows, B.cols) {
		for (int row = 0; row < B.rows; ++row)
			for (int col = 0; col < B.cols; ++col)
				this->mtx[row][col] = B.mtx[row][col];
		cout << "Matrix copy constructor called!" << endl;
	}

	void printMtx() {
		for (int row = 0; row < this->rows; ++row) {
			for (int col = 0; col < this->cols; ++col)
				cout << this->mtx[row][col] << "\t";
			cout << endl;
		}
	}

	void setValue(int row, int col, double value) {
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

	Matrix operator+(const Matrix& B) {
		if (this->rows != B.rows || this->cols != B.cols) {
			cout << "+ operator dimensions mismatch!" << endl;
			Matrix* tmp = new Matrix();
			return *tmp;
		}

		for (int row = 0; row < this->rows; ++row)
			for (int col = 0; col < this->cols; ++col)
				this->mtx[row][col] += B.mtx[row][col];
		return *this;
	}



	Matrix operator*(const Matrix& B) {
		if (this->cols != B.rows) {
			cout << "* operator dimensions mismatch!" << endl;
			Matrix* tmp = new Matrix();
			return *tmp;
		}
		Matrix* out = new Matrix(this->rows, B.cols);
		for (int row = 0; row < this->rows; ++row)
			for (int col = 0; col < B.cols; ++col)
				for (int ii = 0; ii < this->cols; ++ii)
					out->mtx[row][col] += this->mtx[row][ii] * B.mtx[ii][col];
		return *out;
	}

	Matrix operator*(double a) {
		for (int row = 0; row < this->rows; ++row)
			for (int col = 0; col < this->cols; ++col)
				this->mtx[row][col] *= a;
		return *this;
	}

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
		return *this;
	}

	void clearMtx() {
		for (int ii = 0; ii < rows; ++ii)
			delete[] this->mtx[ii];
		delete[] this->mtx;
	}

	void transpose() {
		Matrix tmp = *this;
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

	//вычисление определител€
	double det() {
		if (this->rows != this->cols) {
			cout << " Matrix is not square!" << endl;
			return 0;
		}
		Matrix B = *this;
		double coeff = 0;
		//приведение матрицы к верхнетреугольному виду
		for (int step = 0; step < this->cols - 1; ++step)
			for (int row = step + 1; row < this->cols; ++row) {
				coeff = -B.mtx[row][step] / B.mtx[step][step]; //метод √аусса
				for (int col = step; col < this->cols; col++)
					B.mtx[row][col] += B.mtx[step][col] * coeff;
			}
		B.printMtx();
		//–ассчитать определитель как произведение элементов главной диагонали
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
		/* „исленное вычисление обратной матрицы по методу Ќьютона-Ўульца
	   1. «аписать начальное приближение [Pan, Schreiber]:
		   1) “ранспонировать данную матрицу
		   2) Ќормировать по столбцам и строкам
	   2. ѕовтор€ть процесс до достижени€ заданной точности.
   */

		double N1 = 0, Ninf = 0; //норма матрицы по столбцам и по строкам
		Matrix A0 = *this;       //инициализаци€ начального приближени€
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
		//инициализаци€ удвоенной единичной матрицы нужного размера
		Matrix E2 = Matrix(this->cols, this->cols);
		E2.makeUnit();
		E2 = E2 * 2;
		
		Matrix inv = A0;
		double eps = 0.00001;   //погрешность

		if (this->det() != 0) { //если матрица не вырождена
			while (fabs(((*this) * inv).det() - 1) >= eps) //пока |det(A * A[k](^-1)) - 1| >= EPS
			{
				Matrix prev = inv; //A[k-1]
				inv = ((*this) * prev) * -1 + E2;   //2E - A.(A[k-1]^(-1))                 
				inv = prev * inv; //(A[k-1]^(-1)).(2E - A.(A[k-1]^(-1)))
			}
			return inv;
		}
		else
			cout << "Impossible" << endl;
		return Matrix();
	}
};


int main() {
	int r = 2;
	int c = 2;
	double** tmp;
	tmp = new double* [r];
	for (int ii = 0; ii < r; ++ii)
		tmp[ii] = new double[c];
	
	for (int ii = 0; ii < r; ++ii)
		for (int jj = 0; jj < c; ++jj)
			tmp[ii][jj] = ii+jj+1;
	Matrix mtx1 = Matrix(r, c, tmp);
	mtx1.printMtx();
	mtx1.transpose();
	mtx1.printMtx();
	cout << "mtx1 det is:\t" << mtx1.det() << endl;
	Matrix mtx1Inv = mtx1.getInversedMtx();
	mtx1Inv.printMtx();
	Matrix isE = mtx1 * mtx1Inv;
	isE.printMtx();
	for (int ii = 0; ii < r; ++ii)
		delete[] tmp[ii];
	delete[] tmp;
	return 0;
}