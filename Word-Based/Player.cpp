#include "Player.h"

Player::Player(Room* room) {
	currRoom = room;
	prevRoom = nullptr;
}
int Player::travel(Direction d) {
	if (this->currRoom->getRoom(d) == nullptr) {
		return 0;
	}
	if (this->currRoom->getRoom(d)->isLocked()) {
		return 1;
	}
	this->currRoom = currRoom->getRoom(d);
	this->currRoom->setDiscovered();
	return 2;
}

Room* Player::getRoom() {
	return this->currRoom;
}

void Player::take(Item* item) {
	inventory.push_back(item);
}

void Player::drop(int i) {
	inventory.shrink_to_fit();
	inventory.at(i) = inventory.at(inventory.size() - 1);
	inventory.pop_back();
}

vector<Item*> Player::getInventory() {
	return this->inventory;
}