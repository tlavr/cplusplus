// Last edit 05.05.2020 by Lavrukhin Timur
//
// This file contains functions to determine the prime number and put the first N prime number into array passed to it:
//
// main()	-	main function of the programm, 
//				allows to input the number of prime words N,
//				and outputs the first N prime words 
//
// b = isPrime(x)	- function checks is passed number N is prime number or not and return true or false
//		  x		- integer number which need to check
//		  b		- true or false 	
//
// void primeNums(N,arr)  - function finds the first N prime numbers and puts them into arr
//		  N		-	number of prime numbers needed to find
//		  arr	-	array passed to the function which has the length of N


#include <iostream>
#include <cmath>
using namespace std;

bool isPrime(long long x){
	long long s;
	int ii = 2;
	s = round(sqrt(x));
	while(x % ii != 0 && ii <= s)
		++ii;
	if (ii > s)
		return true;
	return false;
}


void primeNums(int N, int* arr){
	int cnt = 0, ii = 1;
	while(cnt < N){
		if (isPrime(ii)){
			arr[cnt] = ii;
			++cnt;
		}
		++ii;
	}	
}

int main(){
	int N;
	cout << "Please, input N: ";
	cin >>	N;
	
	if (N < 0){
		cout << "Invalid N" << endl;
		return 0;
	}
	
	int* arr = new int[N];
	primeNums(N, arr);
	
	cout << "The first " << N << " prime numbers are:" << endl;
	for (int ii = 0; ii < N; ++ii){
		cout.width(3);
		cout.setf(ios::left);	
		cout << ii+1 << ": ";
		cout << arr[ii] << endl;
	}
	
	
	delete[] arr;
	system("pause");
	return 0;
}