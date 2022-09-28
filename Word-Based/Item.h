#pragma once
#include <string>
using namespace std;

class Item {

	bool furniture;

protected:
	string name;
	string description;

public:
	Item() {};
	Item(string n, string d, bool f);
	bool isFurniture();
	string getName();
	string getDescription();
};
