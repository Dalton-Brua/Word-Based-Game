#pragma once
#include <string>
using namespace std;

class Item {

	string name;
	string description;
	bool furniture;

public:
	Item() {};
	Item(string n, string d, bool f);
	bool isFurniture();
	string getName();
	string getDescription();

};

class Key : Item {
	
};
