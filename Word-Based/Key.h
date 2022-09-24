#pragma once
#include "Item.h"
#include "Room.h"

struct Key : Item {
	Room* roomToUnlock = nullptr;
	Key(Room* room) { roomToUnlock = room; }
};
