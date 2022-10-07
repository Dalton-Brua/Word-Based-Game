#pragma once
#include <string>
using namespace std;

class Item {

	bool key;

protected:
	bool furniture;
	string name;
	string description;

public:
	Item() {};
	Item(string n, string d, bool f);
	Item(string n, string d, bool f, bool k);
	bool isFurniture();
	string getName();
	string getDescription();
	bool isKey();
};
