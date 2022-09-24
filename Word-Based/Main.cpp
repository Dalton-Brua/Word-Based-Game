#include <iostream>
#include <algorithm>
#include <string>
#include <stdio.h>
#include "Room.h"
#include "Item.h"
#include "Key.h"
#include "Person.h"
#include "Player.h"
#include "Lore.h"

using namespace std;

int main() {

	bool gameover = false;
	string input = "";
	string command;
	string dest;
	
	Lore* lore = new Lore();
	
	Room* detRoom = new Room("Detective's Room", lore->detRoomDescription);
	Room* NHall = new Room("North Hallway", lore->NHallDescription);
	Room* northBath = new Room("North Bathrooms", lore->northBathDescription);
	Room* docRoom = new Room("Doctor's Room", lore->docRoomDescription);

	

	Person* Doctor = new Person("Doctor", lore->docDescription, lore->docConversation);
	Item* syringe = new Item("Syringe", lore->syringeDescription, false);
	Item* deadBody = new Item("Body", lore->northBathCorpse, true);
	
	Item* docWindow = new Item("Window", lore->docWindowDescription, true);

	detRoom->link(NHall, E);
	NHall->link(northBath, NE);
	NHall->link(docRoom, SW);


	docRoom->addItem(docWindow);
	
	northBath->addPerson(Doctor);
	northBath->addItem(syringe);
	northBath->addItem(deadBody);

	Player* player = new Player(detRoom);

	cout << lore->introduction;
	cout << lore->detRoomDescription;

	while (!gameover) {

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
			if (items.size() == 0) cout << "There is no " << origDest << endl;
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
				cout << "There is no " << origDest << endl;
			}
		}
		else if (command == "TALK") {
			vector<Person*> people = player->getRoom()->getPeople();
			bool found = false;
			int foundAt = 0;
			if (people.size() == 0) cout << "There is no one to talk to" << endl;
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
				cout << "There is no " << origDest << " to talk to" << endl;
			}
			
		}
		else if (command == "TAKE") {
			vector<Item*> items = player->getRoom()->getItems();
			bool found = false;
			if (items.size() == 0) {
				cout << "There is no " << origDest << endl;
				continue;
			}
			for (int i = 0; i < items.size(); i++) {
				string name = items.at(i)->getName();
				transform(name.begin(), name.end(), name.begin(), ::toupper);
				if (name == dest) {
					found = true;
					if (!items.at(i)->isFurniture()) {
						player->take(items.at(i));
						player->getRoom()->removeItem(i);
						cout << "You have picked up " << origDest << endl;
						break;
					}
					else {
						cout << "You cannot pick that up" << endl;
						break;
					}
				}
				if (found == false) {
					cout << "There is no " << origDest << endl;
				}
			}
		}
		else if (command == "DROP") {
			vector<Item*> inventory = player->getInventory();
			bool dropped = false;
			if (inventory.size() == 0) {
				cout << "You do not have " << origDest << endl;
				continue;
			}
			for (int i = 0; i < inventory.size(); i++) {
				string name = inventory.at(i)->getName();
				transform(name.begin(), name.end(), name.begin(), ::toupper);
				if (name == dest) {
					player->drop(i);
					player->getRoom()->addItem(inventory.at(i));
					cout << "You have dropped " << origDest << endl;
					dropped = true;
					break;
				}
			}
			if (!dropped) {
				cout << "You do not have " << origDest << endl;
			}
		}
		else if (command == "INVENTORY") {
			vector<Item*> inventory = player->getInventory();
			if (inventory.size() == 0) {
				cout << "You do not have anything" << endl;
				continue;
			}

			for (int i = 0; i < inventory.size(); i++) {
				cout << inventory.at(i)->getName() << endl;
			}
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
		}
		else if (command == "MOVE") {
			if (dest == "N") {
				if (!player->travel(N)) {
					cout << "There is no room that way" << endl;
					continue;
				}
			}
			if (dest == "NE") {
				if (!player->travel(NE)) {
					cout << "There is no room that way" << endl;
					continue;
				}
			}
			if (dest == "E") {
				if (!player->travel(E)) {
					cout << "There is no room that way" << endl;
					continue;
				}
			}
			if (dest == "SE") {
				if (!player->travel(SE)) {
					cout << "There is no room that way" << endl;
					continue;
				}
			}
			if (dest == "S") {
				if (!player->travel(S)) {
					cout << "There is no room that way" << endl;
					continue;
				}
			}
			if (dest == "SW") {
				if (!player->travel(SW)) {
					cout << "There is no room that way" << endl;
					continue;
				}
			}
			if (dest == "W") {
				if (!player->travel(W)) {
					cout << "There is no room that way" << endl;
					continue;
				}
			}
			if (dest == "NW") {
				if (!player->travel(NW)) {
					cout << "There is no room that way" << endl;
					continue;
				}
			}
			cout << player->getRoom()->getName() << endl;
		}
		else if (command == "HELP") {
			cout << "Commands: " << endl;
			cout << "MOVE - Travels in a specified direction" << endl;
			cout << "EXAMINE - Prints the description of an item in the room" << endl;
			cout << "TAKE - Takes an item and puts it in your inventory" << endl;
			cout << "DROP - Takes an item out of your inventory and puts it in the room" << endl;
			cout << "Inventory - Prints out the items in your inventory" << endl;
			cout << "LOOK - Prints the description of the room" << endl;
			cout << "DOORS - Lists all the directions out of the room" << endl;
			cout << "ROOM - Prints the name of the room you are in" << endl;
		}



		if (command == "STOP") {
			gameover = true;
		}
	}

}