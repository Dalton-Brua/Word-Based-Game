#include "Door.h"
#include "Player.h"
#include "Room.h"
#include "Item.h"

bool Door::isLocked() {
	return this->locked;
}

Door::Door(bool l) {
	locked = l;
}

void Door::unlock(Door doorToUnlock) {

}

void Door::lock(Door doorToLock) {

}


