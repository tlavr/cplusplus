#include <iostream>
#include <string>
#include "singleton.h"

using namespace std;

class DestinationIP{
	static DestinationIP* _address;
	string _hostname;
	unsigned int _hostIP;
	short _checkPeriod;
	DestinationIP() : _hostname(""), _checkPeriod(10), _hostIP(0) {}
	short getOctet(short num) {	 // 3.2.1.0 -> octet nums
		switch (num) {
		case(0):
			return this->_hostIP & 0xFF;
			break;
		case(1):
			return (this->_hostIP & 0xFF00) >> 8;
			break;
		case(2):
			return (this->_hostIP & 0xFF0000) >> 16;
			break;
		case(3):
			return (this->_hostIP & 0xFF000000) >> 24;
			break;
		default:
			return 0;
		}
	}

public:
	static DestinationIP* getInstance() {
		if (_address == nullptr)
			_address = new DestinationIP();
		return _address;
	}
	void setHostname(string name) { _hostname = name; }
	void setIP(unsigned int ip) { _hostIP = ip; }
	void setCheckPeriod(short period) { _checkPeriod = period; }
	
	string getHostname() { return _hostname; }
	short getCheckPeriod() { return _checkPeriod; }
	unsigned int getIP() { return _hostIP; }
	void showSettings() {
		cout << "Destination host name is " << _hostname << endl \
			<< "IP:\t" << getOctet(3) << "." << getOctet(2) << "." << getOctet(1) << "."\
			<< getOctet(0) << endl << "Check host reachability period is " << _checkPeriod \
			<< " seconds." << endl << endl;
	}
};

DestinationIP* DestinationIP::_address = nullptr;

void setNewIP(unsigned int addr, string hostname, short period) {
	DestinationIP* ip = DestinationIP::getInstance();
	ip->setIP(addr);
	ip->setHostname(hostname);
	ip->setCheckPeriod(period);
}

void doSingleton() {
	DestinationIP* ip = DestinationIP::getInstance();
	ip->showSettings();
	setNewIP(1212371283, "www.nothing.no", 30);
	ip->showSettings();
}