#include <iostream>
#include <thread>
#include <chrono>
#include "lesson3.h"

using namespace std;

// to pass the parameter to the thread

void doWork3(int& a, int& b) {
	this_thread::sleep_for(chrono::milliseconds(500));
	cout << "thread ID = " << this_thread::get_id() << "\tdoWork3 STARTED\t" << endl;
	this_thread::sleep_for(chrono::milliseconds(1000));
	a *= b;
	this_thread::sleep_for(chrono::milliseconds(1000));
	cout << "thread ID = " << this_thread::get_id() << "\tdoWork3 ENDED\t" << endl;
}

void doLesson3() {
	int b = 3;
	thread th3(doWork3, ref(b), ref(b));

	for (size_t ii = 0; ii < 10; ++ii) {
		cout << "thread ID = " << this_thread::get_id() << "\tlesson3\t" << ii << endl;
		this_thread::sleep_for(chrono::milliseconds(500));
	}
	th3.join();
	cout << b << endl;
}