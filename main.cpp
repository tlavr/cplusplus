#include <iostream>
#include "main.h"
#include "factory.h"
#include "abstract_factory.h"
#include "singleton.h"

using namespace std;

int main() {
	setlocale(LC_ALL, "ru");
	//doFactory();
	//doAbstractFactory();
	doSingleton();
	return 0;
}