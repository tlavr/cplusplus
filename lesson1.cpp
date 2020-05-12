#include <iostream>
#include <thread>
#include <chrono>
#include "lesson1.h"
  
// get id of thread and create a thread

using namespace std;

void doWork1() {
	for (size_t ii = 0; ii < 10; ++ii) {
		cout << "thread ID = " << this_thread::get_id() << "\tdoWork1\t" << ii << endl;
		this_thread::sleep_for(chrono::milliseconds(600));
	}
}

void doLesson1(){
	thread th1(doWork1);

	for (size_t ii = 0; ii < 10; ++ii) {
		cout << "thread ID = " << this_thread::get_id() << "\tlesson1\t" << ii << endl;
		this_thread::sleep_for(chrono::milliseconds(500));
	}
	th1.join();
}