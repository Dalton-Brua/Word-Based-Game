#pragma once
#include "Item.h"
#include "Room.h"

class Player {

	Room* prevRoom;
	Room* currRoom;
	vector<Item*> inventory;
	vector<Key*> keys;

public:
	Player(Room* room);
	bool travel(Direction d);
	Room* getRoom();
	void take(Item* item);
	void drop(int i);
	vector<Item*> getInventory();

};
