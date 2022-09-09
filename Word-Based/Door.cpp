#include "Door.h"

void Door::travel(Door door) {

}

bool Door::isLocked() {
	return this->locked;
}

Door::Door(bool l) {
	locked = l;
}
