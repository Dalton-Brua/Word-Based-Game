#pragma once
#include <vector>
#include "Item.h"
#include "Person.h"
#include "Direction.h"
using namespace std;

class Room {

	string name = "";
	string description = "";

	vector<Item*> items;
	Item* roomKey;
	vector<Person*> people;

	bool locked = false;


public:
	Room* doors[8];

	Room(string name, string description);
	void setDescription(string description);
	void link(Room* dest, Direction d);
	Room* getDoor(Direction d);
	void addItem(Item* item);
	void removeItem(int index);
	void addPerson(Person* person);
	void removePerson(int index);
	void setKey(Item* key);
	Item* getKey();
	Room* getRoom(Direction d);
	string getDescription();
	string getName();
	vector<Item*> getItems();
	vector<Person*> getPeople();
	void lock();
	void unlock();
	bool isLocked();

};
