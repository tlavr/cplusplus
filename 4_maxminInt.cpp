// Last edit 05.05.2020 by Lavrukhin Timur
//
// main()	-	main function of the programm, 
//				allows to input the number to process,
//				and outputs the max and min numbers obtained in dec and hex formats
//
// This file contains functions to count the max and min unsigned int numbers which can be created using the same
//    number of "1" as in the passed number
//
// arr = findMaxMin(x)	-	function counts the number of "1" in x and return an array with created min and max number
//		x	-	unsigned int number to process
//		arr	-	arr[0] contains created Min number
//				arr[1] contains created Max number


#include <iostream>

using namespace std;

void printResult(short cnt, unsigned int x, unsigned int *ans) {
	cout.width(15);
	cout << "Number of \"1\": " << cnt << endl;
	cout.width(15);
	cout << "Your number: ";
	cout.width(12);
	cout << showbase << x << " hex: " << hex << x << endl;
	cout.width(15);
	cout << "Min: ";
	cout.width(12);
	cout << dec << ans[0] << " hex: " << hex << ans[0] << endl;
	cout.width(15);
	cout << "Max: ";
	cout.width(12);
	cout << dec << ans[1] << " hex: " << hex << ans[1] << endl;
}

unsigned int* findMaxMin(unsigned int x) {
	unsigned int tmp = x;
	unsigned int* ans = new unsigned int[2];
	ans[0] = 0;
	ans[1] = 0;

	short cnt = 0;
	while (tmp != 0) {
		if (tmp & 1 == 1)
			++cnt;
		tmp >>= 1;
	}

	for (short ii = 1; ii <= cnt; ++ii) {
		ans[0] <<= 1;
		ans[0] |= 1;
		ans[1] >>= 1;
		ans[1] |= 0x80000000;
	}
	printResult(cnt, x, ans);
	return ans;
}



int main() {
	unsigned int tmp;
	unsigned int* arr;
	cout << "Input your number: ";
	cin >> tmp;
	arr = findMaxMin(tmp);
	return 0;
	
}