#pragma once
#include <string>
using namespace std;

class Item {

	string name;
	string description;

public:
	Item() {};
	Item(string n, string d);

};

class Key : Item {
	
};
