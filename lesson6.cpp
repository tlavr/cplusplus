#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
#include "lesson6.h"
#include "SimpleTimer.h"

using namespace std;

mutex mtx;
// how to use mutex and lock_guard
// deadlock - if there 2 mutex for example and th1 took mtx1 th2 took mtx2 and they are waiting for unlock
// recursive_mutex rm; - можно несколько раз лочить и соответственно разлочить столько же раз обычно для рекурсии исопльзуется
// unique_lock<mutex> ul(mtx, defer_lock); - более гибкая структура чем lock_guard

void printRect(char ch) {
	this_thread::sleep_for(chrono::milliseconds(1000));
	//mtx.lock();
	{
		lock_guard<mutex> guard(mtx);
		for (int ii = 0; ii < 5; ii++) {
			for (int ii = 0; ii < 10; ++ii)
				cout << ch;
			this_thread::sleep_for(chrono::milliseconds(200));
			cout << endl;
		}
		cout << endl;
	}
	//mtx.unlock();
	this_thread::sleep_for(chrono::milliseconds(1000));
}

void doLesson6() {
	SimpleTimer timer;
	thread th1(printRect, '*');
	thread th2(printRect, '#');

	th1.join();
	th2.join();
}