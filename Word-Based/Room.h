#pragma once
#include <vector>
#include "Door.h"
#include "Item.h"
using namespace std;

class Room {

	string name = "";
	string description = "";
	Door doors[8];

	vector<Item> items;


public:
	Room(string name, string description);
	void addItem(Item);

};
