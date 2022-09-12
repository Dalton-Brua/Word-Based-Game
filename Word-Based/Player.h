#pragma once
#include "Item.h"
#include "Room.h"

class Player {

	Room* prevRoom;
	Room* currRoom;
	Item hand;
	vector<Key> keys;

public:
	Player(Room* room);
	bool travel(Direction d);
	Room* getRoom();

};
