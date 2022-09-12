#include "Player.h"
#include "Direction.h"

Player::Player(Room* room) {
	currRoom = room;
	prevRoom = nullptr;
}
bool Player::travel(Direction d) {
	if (this->currRoom->getRoom(d) == nullptr) {
		return false;
	}
	this->prevRoom = this->currRoom;
	this->currRoom = currRoom->getRoom(d);
	return true;
}

Room* Player::getRoom() {
	return this->currRoom;
}