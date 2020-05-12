#include <iostream>
#include <string>
#include "factory.h"

using namespace std;

class Pizza {
protected:
	string pizzaName;
	float pizzaWeight;
public:
	virtual void makeDough() = 0;
	virtual void addIngredients() = 0;
	virtual void showProduct() = 0;
};

class Pepperoni : public Pizza {
public:
	Pepperoni() {
		this->pizzaName = "Pepperoni";
		this->pizzaWeight = 150;
	}
	void makeDough() {
		cout << "Dough is made for the Pepperoni!" << endl;
	}
	void addIngredients() {
		cout << "Pepperoni and mozarella added to Pepperoni pizza!" << endl;
	}
	void showProduct() {
		cout << "Here is your " << this->pizzaName << " pizza!\tWeight:\t" << this->pizzaWeight << endl;
	}
};

class FourCheese : public Pizza {
public:
	FourCheese() {
		this->pizzaName = "Four Cheese";
		this->pizzaWeight = 120;
	}
	void makeDough() {
		cout << "Dough is made for the Four Cheese!" << endl;
	}
	void addIngredients() {
		cout << "Parmezan, bluecheese, brynza and maasdam added to Four Cheese pizza!" << endl;
	}
	void showProduct() {
		cout << "Here is your " << this->pizzaName << " pizza!\tWeight:\t" << this->pizzaWeight << endl;
	}
};

class Margarita: public Pizza {
public:
	Margarita() {
		this->pizzaName = "Margarita";
		this->pizzaWeight = 100;
	}
	void makeDough() {
		cout << "Dough is made for the Margarita!" << endl;
	}
	void addIngredients() {
		cout << "Tomatoes and mozarella added to Margarita pizza!" << endl;
	}
	void showProduct() {
		cout << "Here is your " << this->pizzaName << " pizza.\tWeight:\t" << this->pizzaWeight << endl << endl;
	}
};

class PizzaFactory{
public:
	static Pizza* makePizza(short pizzaNumber) {
		Pizza* p = nullptr;
		switch (pizzaNumber) {
		case(1):
			p = new Pepperoni();
			break;
		case(2):
			p = new Margarita();
			break;
		case(3):
			p = new FourCheese();
			break;
		default:
			cout << "Sorry we don't have that kind of pizza yet!" << endl;
		}
		p->makeDough();
		p->addIngredients();
		return p;
	}

};

void doFactory(){
	short choice;
	while (1) {
		cout << "Please, choose your pizza or press 0 to exit:" << endl << "\t1\t-\tPepperoni" << endl \
			<< "\t2\t-\tMargarita" << endl << "\t3\t-\tFour Cheese" << endl << "Your choice: ";
		cin >> choice;
		if (choice == 0)
			break;
		Pizza* pizza = PizzaFactory::makePizza(choice);
		if (pizza)
			pizza->showProduct();
	}
	cout << endl << "Enjoy your meal!" << endl;
}