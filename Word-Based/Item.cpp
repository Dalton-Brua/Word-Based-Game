#include "Item.h"
#include <string>
using namespace std;

Item::Item(string n, string d, bool f) {
	this->name = n;
	this->description = d;
	this->furniture = f;
	this->key = false;
}

Item::Item(string n, string d, bool f, bool k) {
	this->name = n;
	this->description = d;
	this->furniture = f;
	this->key = k;
}

bool Item::isFurniture() {
	return this->furniture;
}

string Item::getName() {
	return this->name;
}

string Item::getDescription() {
	return this->description;
}

bool Item::isKey() {
	return this->key;
}