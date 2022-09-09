#include "Room.h"
#include <vector>
using namespace std;

void Room::addItem(Item item) {
	this->items.push_back(item);
}

Room::Room(string n, string d) {
	this->name = n;
	this->description = d;
}
