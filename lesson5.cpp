#include <iostream>
#include <thread>
#include <chrono>
#include "lesson5.h"

using namespace std;

// how to use class methods to work with threads

class MyClass{
public:
	void doWork5() {
		this_thread::sleep_for(chrono::milliseconds(500));
		cout << "thread ID = " << this_thread::get_id() << "\tdoWork5 STARTED\t" << endl;
		this_thread::sleep_for(chrono::milliseconds(1000));
		cout << "thread ID = " << this_thread::get_id() << "\tdoWork5 ENDED\t" << endl;
		this_thread::sleep_for(chrono::milliseconds(1000));
	}

	int sum(int a, int b) {
		this_thread::sleep_for(chrono::milliseconds(500));
		cout << "thread ID = " << this_thread::get_id() << "\tdoWork5 STARTED\t" << endl;
		this_thread::sleep_for(chrono::milliseconds(1000));
		return a + b;
		this_thread::sleep_for(chrono::milliseconds(1000));
		cout << "thread ID = " << this_thread::get_id() << "\tdoWork5 ENDED\t" << endl;
	}
};


void doLesson5() {
	MyClass m;
	int result;
	thread th5([&]() { result = m.sum(5, 4); m.doWork5(); });

	for (size_t ii = 0; ii < 10; ++ii) {
		cout << "thread ID = " << this_thread::get_id() << "\tlesson5\t" << ii << endl;
		this_thread::sleep_for(chrono::milliseconds(500));
	}
	th5.join();
	cout << result << endl;
}