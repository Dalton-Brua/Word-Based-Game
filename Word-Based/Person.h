#pragma once
#include "Item.h"
#include <string>

class Person : public Item {

	string name;
	string description;
	string dialogue;

public:
	Person(string n, string d, string di) {
		this->dialogue = di;
		this->name = n;
		this->description = d;
	}

	string getName() {
		return this->name;
	}
	string getDescription() {
		return this->description;
	}
	string getDialogue() {
		return this->dialogue;
	}
};
