#pragma once
#include <string>
#include "Door.h"
using namespace std;

class Item {

	string name;
	string description;

public:
	Item(string n, string d);

};

class Key : Item {
	Door doorToUnlock;
};
