#pragma once
#include "Room.h"

class Player {

	Room* prevRoom;
	Room* currRoom;
	vector<Item*> inventory;

public:
	Player(Room* room);
	int travel(Direction d);
	Room* getRoom();
	void take(Item* item);
	void drop(int i);
	vector<Item*> getInventory();

};
