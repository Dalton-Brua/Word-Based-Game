#include <iostream>
#include <algorithm>
#include <string>
#include <stdio.h>
#include <map>
#include "Room.h"
#include "Player.h"
#include "Lore.h"

using namespace std;

int main() {

	int clues = 0;
	string input = "";
	string command;
	string dest;

	map<string, Direction> const directions = {
		{"N", N}, {"NE", NE},
		{"E", E}, {"SE", SE},
		{"S", SE}, {"SW", SW},
		{"W", W}, {"NW", NW} };
	
	Lore* lore = new Lore();
	
	Room* detRoom = new Room("Detective's Room", lore->detRoomDescription);
	Room* NHall = new Room("North Hallway", lore->NHallDescription);
	Room* northBath = new Room("North Bathrooms", lore->northBathDescription);
	Room* docRoom = new Room("Doctor's Room", lore->docRoomDescription);
	Room* diningRoom = new Room("Dining Room", lore->diningDescription);
	Room* butRoom = new Room("Butler's Room", lore->butRoomDescription);
	Room* kitchen = new Room("Kitchen", lore->kitchenDescription);

	Person* Doctor = new Person("Doctor", lore->docDescription, lore->docConversation);
	Person* Engineer = new Person("Engineer", lore->engDescription, lore->engConversation);
	Person* Butler = new Person("Butler", lore->butDescription, lore->butConversation);
	Person* Chef = new Person("Chef", lore->chefDescription, lore->chefConverstaion);

	Item* syringe = new Item("Syringe", lore->syringeDescription, false);
	Item* wrench = new Item("Wrench", lore->wrenchDescription, false);
	
	
	Item* deadBody = new Item("Body", lore->northBathCorpse, true);
	Item* docWindow = new Item("Window", lore->docWindowDescription, true);
	Item* docBed = new Item("Bed", lore->docBedDescription, true);
	Item* docDresser = new Item("Dresser", lore->docDresserDescription, true);
	Item* docSatchel = new Item("Satchel", lore->docSatchelDescription, true);
	Item* booths = new Item("Booths", lore->boothDescription, true);
	Item* knives = new Item("Knives", lore->knivesDescription, true);

	Item* butRoomKey = new Item("Butler's Room Key", lore->keyDescription, false, true);

	detRoom->link(NHall, W);
	NHall->link(northBath, NW);
	NHall->link(docRoom, SE);
	NHall->link(diningRoom, S);
	NHall->link(butRoom, NE);
	diningRoom->link(kitchen, E);

	docRoom->addItem(docWindow);
	docRoom->addItem(docBed);
	docRoom->addItem(docDresser);
	docRoom->addItem(docSatchel);
	
	northBath->addPerson(Doctor);
	northBath->addItem(Doctor);
	northBath->addItem(syringe);
	northBath->addItem(deadBody);

	diningRoom->addPerson(Engineer);
	diningRoom->addItem(Engineer);
	diningRoom->addItem(booths);
	diningRoom->addItem(wrench);

	butRoom->addPerson(Butler);
	butRoom->addItem(Butler);

	kitchen->addPerson(Chef);
	kitchen->addItem(Chef);
	kitchen->addItem(knives);

	butRoom->lock();
	
	Player* player = new Player(detRoom);

	// map<string, Item*> const keys = { 
	//	{butRoom->getName(), butRoomKey}};

	cout << lore->introduction;
	cout << lore->detRoomDescription << endl;

	while (clues < 5) {

		command = "";
		dest = "";
		input = "";
		string origDest = "";

		getline(cin, input);
		input += " ";

		for (int i = 0; i < input.length(); i++) {
			string sub = input.substr(i, 1);

			if (sub == " ") {

				command = input.substr(0, i);
				transform(command.begin(), command.end(), command.begin(), ::toupper);
				
				dest = input.substr(i + 1, input.length() - command.length() - 2);
				origDest = dest;
				transform(dest.begin(), dest.end(), dest.begin(), ::toupper);

			}

			if (command != "") {
				break;
			}
		}
		if (command == "ROOM") {
			cout << player->getRoom()->getName() << endl;
		}
		else if (command == "LOOK") {
			cout << player->getRoom()->getDescription() << endl;
		}
		else if (command == "EXAMINE") {
			vector<Item*> items = player->getRoom()->getItems();
			bool found = false;
			int foundAt = 0;
			if (dest == "") {
				cout << "You examine nothing in particular\n" << endl;
				continue;
			}
			for (int i = 0; i < items.size(); i++) {
				string name = items.at(i)->getName();
				transform(name.begin(), name.end(), name.begin(), ::toupper);
				if (name == dest) {
					found = true;
					foundAt = i;
					break;
				}
			}
			if (found == true) {
				cout << items.at(foundAt)->getDescription() << endl;
			}
			else {
				cout << "You did not see anything useful\n" << endl;
			}
		}
		else if (command == "TALK") {
			vector<Person*> people = player->getRoom()->getPeople();
			bool found = false;
			int foundAt = 0;
			if (dest == "") {
				cout << "You talk to no one in particular\n" << endl;
				continue;
			}
			if (people.size() == 0) {
				cout << "There is no one to talk to\n" << endl;
				continue;
			}
			for (int i = 0; i < people.size(); i++) {
				string name = people.at(i)->getName();
				transform(name.begin(), name.end(), name.begin(), ::toupper);
				if (name == dest) {
					found = true;
					foundAt = i;
					break;
				}
			}
			if (found == true) {
				cout << people.at(foundAt)->getDialogue() << endl;
			}
			else {
				cout << "There is no " << origDest << " to talk to\n" << endl;
			}
			
		}
		else if (command == "TAKE") {
			if (dest == "") {
				cout << "You took nothing in particular\n" << endl;
				continue;
			}
			vector<Item*> items = player->getRoom()->getItems();

			if (items.size() == 0) {
				cout << "There is no " << origDest << "\n" << endl;
				continue;
			}
			
			else {
				bool found = false;
				for (int i = 0; i < items.size(); i++) {
					string name = items.at(i)->getName();
					transform(name.begin(), name.end(), name.begin(), ::toupper);
					if (dest == "KEY") {
						if (items.at(i)->isKey()) {
							found = true;
							player->take(items.at(i));
							player->getRoom()->removeItem(i);
							cout << "You have picked up " << origDest << "\n" << endl;
							break;
						}
					}
					if (name == dest) {
						found = true;
						if (!items.at(i)->isFurniture()) {

							player->take(items.at(i));
							player->getRoom()->removeItem(i);

							cout << "You have picked up " << origDest << "\n" << endl;
							if (name == "SYRINGE" || name == "LETTER" || name == "HAMMER") {
								clues++;
							}
							break;
						}
						else {
							cout << "You cannot pick that up\n" << endl;
							break;
						}
					}
				}
				if (found == false) {
					cout << "There is no " << origDest << "\n" << endl;
				}
			}
		}
		else if (command == "DROP") {
			vector<Item*> inventory = player->getInventory();
			bool dropped = false;
			if (dest == "") {
				cout << "You dropped nothing in particular\n" << endl;
				continue;
			}
			if (inventory.size() == 0) {
				cout << "You do not have " << origDest << "\n" << endl;
				continue;
			}
			for (int i = 0; i < inventory.size(); i++) {
				string name = inventory.at(i)->getName();
				transform(name.begin(), name.end(), name.begin(), ::toupper);
				if (name == dest) {
					player->drop(i);
					player->getRoom()->addItem(inventory.at(i));
					cout << "You have dropped " << origDest << "\n" << endl;

					if (name == "SYRINGE" || name == "LETTER" || name == "HAMMER") {
						clues--;
						cout << "Clues found " << clues << "/5" << "\n" << endl;
					}
					dropped = true;
					break;
				}
			}
			if (!dropped) {
				cout << "You do not have " << origDest << "\n" << endl;
			}
		}
		else if (command == "INVENTORY") {
			vector<Item*> inventory = player->getInventory();
			if (inventory.size() == 0) {
				cout << "You do not have anything" << "\n" << endl;
				continue;
			}

			for (int i = 0; i < inventory.size(); i++) {
				cout << inventory.at(i)->getName() << endl;
			}
			cout << "\n";
		}
		else if (command == "DOORS") {
			for (int i = 0; i < 8; i++) {
				Room* door = player->getRoom()->getDoor(static_cast<Direction>(i));
				if (door != nullptr) {
					switch (i) {
					case 0:
						cout << "N: ";
						break;
					case 1:
						cout << "NE: ";
						break;
					case 2:
						cout << "E: ";
						break;
					case 3:
						cout << "SE: ";
						break;
					case 4:
						cout << "S: ";
						break;
					case 5:
						cout << "SW: ";
						break;
					case 6:
						cout << "W: ";
						break;
					case 7:
						cout << "NW: ";
						break;
					} 
					cout << door->getName() << endl;
				}
			}
			cout << "\n";
		}
		else if (command == "MOVE") {
			if (dest == "") {
				cout << "You moved nowhere in particular\n" << endl;
				continue;
			}
			if (!directions.count(dest)) {
				cout << "That is not a direction\n" << endl;
				continue;
			}
			switch (player->travel(directions.at(dest))) {
				case 0:
					cout << "There is no room that way\n" << endl;
					break;
				case 1:
					cout << "That room is locked\n" << endl;
					break;
				case 2:
					cout << player->getRoom()->getName() << "\n" << endl;
					break;
			}	
		}
		else if (command == "LOCK") {
			if (dest == "") {
				cout << "You lock nothing in particular\n" << endl;
				continue;
			}
			if (!directions.count(dest)) {
				cout << "That is not a direction\n" << endl;
				continue;
			}
			Room* room = player->getRoom()->getRoom(directions.at(dest));
			if (room == nullptr) {
				cout << "There is no room that way\n" << endl;
				continue;
			}
			vector<Item*> items = player->getRoom()->getItems();
			if (items.size() == 0) {
				cout << "You do not have the key to the " + room->getName() + "\n" << endl;
				continue;
			}
			if (!keys.count(room->getName())) {
				cout << "You do not have the key to lock the " + room->getName() + "\n" << endl;
				continue;
			}
			if (room->isLocked()) {
				cout << "That door is already locked\n" << endl;
				continue;
			}
			room->lock();
			cout << "You have locked the door to the " + room->getName() + "\n" << endl;

		} 
		else if (command == "UNLOCK") {
			if (dest == "") {
				cout << "You unlock nothing in particular\n" << endl;
				continue;
			}
			if (!directions.count(dest)) {
				cout << "That is not a direction\n" << endl;
				continue;
			}
			Room* room = player->getRoom()->getRoom(directions.at(dest));
			if (room == nullptr) {
				cout << "There is no room that way\n" << endl;
				continue;
			}
			if (!keys.count(room->getName())) {
				cout << "You do not have the key to unlock the " + room->getName() + "\n" << endl;
				continue;
			}
			if (!room->isLocked()) {
				cout << "That door is already unlocked\n" << endl;
				continue;
			}
			room->unlock();
			cout << "You have unlocked the door to the " + room->getName() + "\n" << endl;

		}
		else if (command == "CLUES") {
		cout << "Clues found " << clues << "/5\n" << endl;
		}
		else if (command == "HELP") {
			cout << "Commands: " << endl;
			cout << "MOVE - Travels in a specified direction" << endl;
			cout << "EXAMINE - Prints the description of an item in the room" << endl;
			cout << "TAKE - Takes an item and puts it in your inventory" << endl;
			cout << "DROP - Takes an item out of your inventory and puts it in the room" << endl;
			cout << "INVENTORY - Prints out the items in your inventory" << endl;
			cout << "LOOK - Prints the description of the room" << endl;
			cout << "DOORS - Lists all the directions out of the room" << endl;
			cout << "ROOM - Prints the name of the room you are in" << endl;
			cout << "LOCK/UNLOCK - Locks or unlocks a room if you have the key to the room in that particular direction" << endl;
			cout << "CLUES - Tells you how many clues you have found and how many you have left\n" << endl;
		}
	}

}