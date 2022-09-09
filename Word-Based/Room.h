#pragma once
#include <string>
#include <vector>
#include "Door.h"
#include "Item.h"

class Room {

	string name;
	string description;
	Door doors[8];

	vector<Item> items;

public:
	Room(string, string);
	void addItem(Item);

};
