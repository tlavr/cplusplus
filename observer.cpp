#include <iostream>
#include <vector>
#include <algorithm>
#include "observer.h"

//some kind of BPSK...

using namespace std;

class ReceivedBit {
	bool _bit;
	vector<Observer*> _obsVec;
public:

	bool getBit() {
		return _bit;
	}

	void setBit(bool newBit) {
		_bit = newBit;
		notify();
	}
	void attach(Observer* obs) {
		_obsVec.push_back(obs);
	}
	void detach(Observer* obs) {
		_obsVec.erase(remove(_obsVec.begin(), _obsVec.end(), obs), _obsVec.end());
	}
	void notify();
};

class Observer {
	ReceivedBit* _bit;
public:
	Observer(ReceivedBit* rbit) {
		_bit = rbit;
		_bit->attach(this);
	}
	virtual void update() = 0;
protected:
	ReceivedBit* getRBit() {
		return _bit;
	}
};

class DownObs : public Observer {
public:
	DownObs(ReceivedBit* bit) : Observer(bit) {}
	void update() {
		bool bit = getRBit()->getBit();
		if (!bit)
			cout << "Received -1" << endl;
	}
};

class UpObs : public Observer {
public:
	UpObs(ReceivedBit* bit) : Observer(bit) {}
	void update() {
		bool bit = getRBit()->getBit();
		if (bit)
			cout << "Received +1" << endl;
	}
};

void ReceivedBit::notify() {
	for (auto obs : _obsVec)
		obs->update();
}

void doObserver() {
	ReceivedBit* bit = new ReceivedBit();
	DownObs dObs(bit), dObs1(bit);
	UpObs uObs(bit), uObs2(bit), uObs3(bit);

	
	short tmp;

	while(1){
		cout << "Input transmitted bit (1 or 0) or any other digit to exit: ";
		cin >> tmp;
		if (tmp == 0 || tmp == 1)
			bit->setBit((bool)tmp);
		else
			break;
	}
}