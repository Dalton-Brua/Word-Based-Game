#pragma once
#include "Item.h"
#include <string>

class Person : public Item {

	string dialogue;

public:
	Person(string n, string d, string di) {
		this->description = d;
		this->name = n;
		this->dialogue = di;
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
