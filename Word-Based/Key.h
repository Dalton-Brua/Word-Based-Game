#pragma once
#include "Item.h"
#include "Room.h"

struct Key : Item {
	Room* roomToUnlock;
	Key(Room* room) { roomToUnlock = room; }
};
