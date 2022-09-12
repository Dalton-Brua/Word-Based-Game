#include "Room.h"
#include "Direction.h"
#include <vector>
using namespace std;

void Room::addItem(Item* item) {
	this->items.push_back(item);
}

Room::Room(string n, string d) {
	this->name = n;
	this->description = d;

	for (int i = 0; i < 8; i++) {
		doors[i] = nullptr;
	}
}

void Room::setDescription(string d) {
	this->description = d;
}

void Room::link(Room* roomToLink, Direction d) {
	this->doors[d] = roomToLink;
	roomToLink->doors[(d + 4) % 8] = this;
}

Room* Room::getDoor(Direction d) {
	return this->doors[d];
}

string Room::getDescription() {
	return this->description;
}

string Room::getName() {
	return this->name;
}

Room* Room::getRoom(Direction d) {
	return this->doors[d];
}