#include <iostream>
#include <thread>
#include <chrono>
#include "lesson2.h"

using namespace std;

// to pass the parameter to the thread

void doWork2(int a, int b) {
	this_thread::sleep_for(chrono::milliseconds(500));
	cout << "thread ID = " << this_thread::get_id() << "\tdoWork2 STARTED\t" << endl;
	this_thread::sleep_for(chrono::milliseconds(1000));
	cout << a << "+" << b << " = " << a + b << endl;
	this_thread::sleep_for(chrono::milliseconds(1000));
	cout << "thread ID = " << this_thread::get_id() << "\tdoWork2 ENDED\t" << endl;
}

void doLesson2() {
	thread th2(doWork2,1,3);

	for (size_t ii = 0; ii < 10; ++ii) {
		cout << "thread ID = " << this_thread::get_id() << "\tlesson2\t" << ii << endl;
		this_thread::sleep_for(chrono::milliseconds(500));
	}
	th2.join();
}