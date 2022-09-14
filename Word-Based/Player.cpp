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