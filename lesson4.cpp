#include <iostream>
#include <thread>
#include <chrono>
#include "lesson4.h"

using namespace std;

// how to use lambda expression to get result from the thread

int sum(int a, int b) {
	this_thread::sleep_for(chrono::milliseconds(500));
	cout << "thread ID = " << this_thread::get_id() << "\tdoWork4 STARTED\t" << endl;
	this_thread::sleep_for(chrono::milliseconds(1000));
	return a + b;
	this_thread::sleep_for(chrono::milliseconds(1000));
	cout << "thread ID = " << this_thread::get_id() << "\tdoWork4 ENDED\t" << endl;
}

void doLesson4() {
	int result;
	thread th4([&result]() { result = sum(5, 4); });

	for (size_t ii = 0; ii < 10; ++ii) {
		cout << "thread ID = " << this_thread::get_id() << "\tlesson4\t" << ii << endl;
		this_thread::sleep_for(chrono::milliseconds(500));
	}
	th4.join();
	cout << result << endl;
}