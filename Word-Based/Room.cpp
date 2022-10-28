#include "Room.h"
#include "Direction.h"
#include "Person.h"
#include <vector>
using namespace std;

void Room::addItem(Item* item) {
	this->items.push_back(item);
}

void Room::removeItem(int i) {
	items.shrink_to_fit();
	items.at(i) = items.at(items.size() - 1);
	items.pop_back();
}

void Room::addPerson(Person* person) {
	this->people.push_back(person);
}

void Room::removePerson(int i) {
	people.shrink_to_fit();
	people.at(i) = people .at(people.size() - 1);
	people.pop_back();
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

void Room::setKey(Item* key) {
	this->roomKey = key;
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

vector<Item*> Room::getItems() {
	return this->items;
}

vector<Person*> Room::getPeople() {
	return this->people;
}

Item* Room::getKey() {
	return this->roomKey;
}

void Room::lock() {
	this->locked = true;
}

void Room::unlock() {
	this->locked = false;
}

bool Room::isLocked() {
	return this->locked;
}