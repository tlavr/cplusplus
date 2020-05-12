#include <iostream>
#include <thread>
#include <chrono>
#include "main.h"
#include "lesson1.h"
#include "lesson2.h"
#include "lesson3.h"
#include "lesson4.h"
#include "lesson5.h"
#include "lesson6.h"

using namespace std;

int main() {
	setlocale(LC_ALL, "ru");
	//thread th1(doLesson1), th2(doLesson2);
	//th1.join();
	//th2.join();
	doLesson6();
	return 0;
}