#include <iostream>
#include <string>

using namespace std;


class Shoe {
protected:
	string name;
	int strength;
public:
	Shoe(string n, int s) :name(n), strength(s) {};
	string getName() { return name; }
	int getStrength() { return strength; }
};

class CoolShoe : public Shoe {
public:
	CoolShoe() : Shoe("Cool Shoe", 99) {}
};

class SimpleShoe : public Shoe {
public:
	SimpleShoe() : Shoe("Simple Shoe", 60) {}
};

class Shirt {
protected:
	string name;
	string color;
public:
	Shirt(string n, string c) :name(n), color(c) {};
	string getName() { return name; }
	string getColor() { return color; }
};

class CoolShirt : public Shirt {
public:
	CoolShirt() : Shirt("Cool Shirt", "Red") {}
};

class SimpleShirt : public Shirt {
public:
	SimpleShirt() : Shirt("Simple Shirt", "Green") {}
};

class Brand {
protected:
	string name;
	Shoe* shoe;
	Shirt* shirt;
public:
	Brand(string n) :name(n) {}
	void setShoe(Shoe* s) { shoe = s; }
	void setShirt(Shirt* s) { shirt = s; }
	void showDetails() {
		cout << endl << "Brand:\t" << name << endl;
		cout << "Shoe:\t" << shoe->getName() << "\tStrength:\t" << shoe->getStrength() << endl;
		cout << "Shirt:\t" << shirt->getName() << "\tColor:\t" << shirt->getColor() << endl << endl;

	}
};

class SportsFactory{
private:
	Brand* brand;
protected:
	virtual Shoe* getShoe() = 0;
	virtual Shirt* getShirt() = 0;
public:
	virtual Brand* getClothes() = 0;
};

class NikeFactory : public SportsFactory{
	Shoe* getShoe() {
		return new CoolShoe();
	}
	Shirt* getShirt() {
		return new SimpleShirt();
	}
	Brand* getClothes() {
		Brand* brand = new Brand("Nike");
		brand->setShoe(getShoe());
		brand->setShirt(getShirt());
		return brand;
	}
};

class AdidasFactory : public SportsFactory {
	Shoe* getShoe() {
		return new SimpleShoe();
	}
	Shirt* getShirt() {
		return new CoolShirt();
	}
	Brand* getClothes() {
		Brand* brand = new Brand("Adidas");
		brand->setShoe(getShoe());
		brand->setShirt(getShirt());
		return brand;
	}
};


void doAbstractFactory() {
	short choice;
	SportsFactory* factory = nullptr;
	Brand* clothes = nullptr;
	while (1) {
		cout << "Please, choose your sports factory or press 0 to exit:" << endl << "\t1\t-\tNike" << endl \
			<< "\t2\t-\tAdidas" << endl << "Your choice: ";
		cin >> choice;
		if (choice == 0)
			break;
		switch (choice) {
		case(1):
			factory = new NikeFactory;
			break;
		case(2):
			factory = new AdidasFactory;
			break;
		default:
			cout << "Oops! We don't have that choice yet!" << endl;
			break;
		}
		if (factory){
			clothes = factory->getClothes();
			clothes->showDetails();
		}
	}
	cout << endl << "Enjoy your clothes!" << endl;
}