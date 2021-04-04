/******************************************************************************

Zuul by Neevan Abedin

*******************************************************************************/
#include <iostream>
#include <cstring>
#include <vector>
#include <iomanip>
#include <map>
#include <algorithm>

#include "room.h"
#include "item.h"

using namespace std;

//function prototypes
//initiliazers
void initializeRooms(vector<Room*>* rooms);
void initializeItems(vector<Item*>* items);

//printers
void printRoom(vector<Room*>* rooms, vector<Item*>* items, int currentRoom);
void printInventory(vector<Item*>* items, vector<int> inventory);

//commands
int move(vector<Room*>* rooms, int currentRoom, char direction[]);
void store(vector<Room*>* rooms, vector<Item*>* items, vector<int>* inventory, int currentRoom, char name[]);
void drop(vector<Room*>* rooms, vector<Item*>* items, vector<int>* inventory, int currentRoom, char name[]);

int main()
{
    bool running = true;
    
    vector<Room*> roomList;
    vector<Item*> itemList;
    vector<int> inventory;
    
    char input[80];
    int currentRoom = 1;
    int moves = 0;
    
    initializeRooms(&roomList);
    initializeItems(&itemList);
    
    //starting prompt
    cout << "Your spaceship is going down! As the technician, the crew is depending on you to go through the rooms and gather items for repair." << endl;
    cout << "Your commands are: 'store', 'drop', 'inventory', 'move', 'quit', and 'help'" << endl;
    cout << "Good luck. Your crewmates are counting on you." << endl;
    
    while(running){
        if (moves < 20) { //lose condition
            cout << "You are currently ";
            printRoom(&roomList, &itemList, currentRoom);
            cout << "What would you like to do? ('store', 'drop', 'inventory', 'move', 'quit', 'help'). Moves: " << moves << endl;
            cin >> input;
            cin.clear();
            cin.ignore(1000, '\n');
            if (strcmp(input, "quit") == 0) {
                cout << "Goodbye." << endl;
                running = false;
            } else if (strcmp(input, "move") == 0) {
                cout << "Which direction?" << endl;
                cin >> input;
                cin.clear();
                cin.ignore(1000, '\n');
                if (move(&roomList, currentRoom, input) == 0) {
                    cout << "No exits in that direction.";
                } else {
                    currentRoom = move(&roomList, currentRoom, input);
                }
                moves++;
            } else if (strcmp(input, "inventory") == 0) {
                //print inventory
                if (inventory.size() != 0) {
                    printInventory(&itemList, inventory);
                } else {
                    cout << endl << "Your inventory is empty." << endl;
                }
            } else if (strcmp(input, "store") == 0) {
                //pick up item
                cout << "What item would you like to store?" << endl;
                cin >> input;
                cin.clear();
                cin.ignore(1000, '\n');
                store(&roomList, &itemList, &inventory, currentRoom, input);
            } else if (strcmp(input, "drop") == 0) {
                cout << "What would you like to drop?" << endl;
                cin >> input;
                cin.clear();
                cin.ignore(1000, '\n');
                drop(&roomList, &itemList, &inventory, currentRoom, input);
            } else if (strcmp(input, "help") == 0) {
                cout << "You have to find your items within 20 moves before the ship blows up!" << endl;
                cout << "Remember, your commands are: 'store', 'drop', 'inventory', 'move', and 'quit'" << endl;
            } else {
                cout << "Invalid input." << endl;
            }
            
            if (inventory.size() == 5) {
                cout << "You gathered all the items and fixed the ship! You win!";
                running = false;
                return 0;
            }
        } else {
            cout << "You lose :(";
            running = false;
            return 0;
        }
    }
    return 0;
}

void initializeRooms(vector<Room*>* rooms) {
    //exits
    char* north = (char*)("north");
    char* south = (char*)("south");
    char* east = (char*)("east");
    char* west = (char*)("west");
    
    //initialize temporary map for exits
    map<int, char*> temp;
    
    //rooms
    
    //command center
    Room* command = new Room();
    command -> setDescription((char*)("in the command center."));
    command -> setId(1);
    temp.insert(pair<int, char*> (2, north));
    temp.insert(pair<int, char*> (3, east));
    temp.insert(pair<int, char*> (4, west));
    command -> setExits(temp);
    command -> setItem(0);
    rooms -> push_back(command);
    temp.clear();
    
    //android studio
    Room* android = new Room();
    android -> setDescription((char*)("in the android studio."));
    android -> setId(2);
    temp.insert(pair<int, char*> (11, north));
    temp.insert(pair<int, char*> (1, south));
    android -> setExits(temp);
    android -> setItem(1); //computer key
    rooms -> push_back(android);
    temp.clear();
    
    //aquarium
    Room* aquarium = new Room();
    aquarium -> setDescription((char*)("in the aquarium."));
    aquarium -> setId(3);
    temp.insert(pair<int, char*> (8, east));
    temp.insert(pair<int, char*> (1, west));
    aquarium -> setExits(temp);
    aquarium -> setItem(0);
    rooms -> push_back(aquarium);
    temp.clear();
    
    //armor room
    Room* armor = new Room();
    armor -> setDescription((char*)("in the armor room."));
    armor -> setId(4);
    temp.insert(pair<int, char*> (1, east));
    temp.insert(pair<int, char*> (5, west));
    armor -> setExits(temp);
    armor -> setItem(0);
    rooms -> push_back(armor);
    temp.clear();
    
    //living quarters
    Room* living = new Room();
    living -> setDescription((char*)("in the living quarters."));
    living -> setId(5);
    temp.insert(pair<int, char*> (4, east));
    temp.insert(pair<int, char*> (6, north));
    living -> setExits(temp);
    living -> setItem(0);
    rooms -> push_back(living);
    temp.clear();
   
    //captain's quarters
    Room* captain = new Room();
    captain -> setDescription((char*)("in the captain's quarters."));
    captain -> setId(6);
    temp.insert(pair<int, char*> (7, north));
    temp.insert(pair<int, char*> (5, south));
    captain -> setExits(temp);
    captain -> setItem(0);
    rooms -> push_back(captain);
    temp.clear();
    
    //computer room
    Room* computer = new Room();
    computer -> setDescription((char*)("in the computer room."));
    computer -> setId(7);
    temp.insert(pair<int, char*> (14, north));
    temp.insert(pair<int, char*> (6, south));
    computer -> setExits(temp);
    computer -> setItem(0);
    rooms -> push_back(computer);
    temp.clear();
    
    //cafeteria
    Room* cafeteria = new Room();
    cafeteria -> setDescription((char*)("in the cafeteria."));
    cafeteria -> setId(8);
    temp.insert(pair<int, char*> (3, west));
    temp.insert(pair<int, char*> (9, north));
    cafeteria -> setExits(temp);
    cafeteria -> setItem(0);
    rooms -> push_back(cafeteria);
    temp.clear();
    
    //engine room
    Room* engine = new Room();
    engine -> setDescription((char*)("in the engine room."));
    engine -> setId(9);
    temp.insert(pair<int, char*> (10, north));
    temp.insert(pair<int, char*> (8, south));
    engine -> setExits(temp);
    engine -> setItem(2); //backup generator
    rooms -> push_back(engine);
    temp.clear();
    
    //fusion reactor
    Room* fusion = new Room();
    fusion -> setDescription((char*)("in the fusion reactor."));
    fusion -> setId(10);
    temp.insert(pair<int, char*> (13, north));
    temp.insert(pair<int, char*> (9, south));
    fusion -> setExits(temp);
    fusion -> setItem(4); //fuel tank
    rooms -> push_back(fusion);
    temp.clear();
    
    //gym
    Room* gym = new Room();
    gym -> setDescription((char*)("in the gym."));
    gym -> setId(11);
    temp.insert(pair<int, char*> (2, south));
    temp.insert(pair<int, char*> (12, north));
    gym -> setExits(temp);
    gym -> setItem(0);
    rooms -> push_back(gym);
    temp.clear();
    
    //hangar
    Room* hangar = new Room();
    hangar -> setDescription((char*)("in the hangar."));
    hangar -> setId(12);
    temp.insert(pair<int, char*> (15, north));
    temp.insert(pair<int, char*> (13, east));
    temp.insert(pair<int, char*> (11, south));
    temp.insert(pair<int, char*> (14, west));
    hangar -> setExits(temp);
    hangar -> setItem(0);
    rooms -> push_back(hangar);
    temp.clear();
    
    //laboratory
    Room* lab = new Room();
    lab -> setDescription((char*)("in the laboratory."));
    lab -> setId(13);
    temp.insert(pair<int, char*> (12, west));
    temp.insert(pair<int, char*> (10, south));
    lab -> setExits(temp);
    lab -> setItem(3); //hazmat suit
    rooms -> push_back(lab);
    temp.clear();
    
    //lounge
    Room* lounge = new Room();
    lounge -> setDescription((char*)("in the lounge."));
    lounge -> setId(14);
    temp.insert(pair<int, char*> (12, east));
    temp.insert(pair<int, char*> (7, south));
    lounge -> setExits(temp);
    lounge -> setItem(0);
    rooms -> push_back(lounge);
    temp.clear();
    
    //med bay
    Room* med = new Room();
    med -> setDescription((char*)("in the med bay."));
    med -> setId(15);
    temp.insert(pair<int, char*> (16, north));
    temp.insert(pair<int, char*> (12, south));
    med -> setExits(temp);
    med -> setItem(0);
    rooms -> push_back(med);
    temp.clear();
    
    //warehouse
    Room* warehouse = new Room();
    warehouse -> setDescription((char*)("in the warehouse."));
    warehouse -> setId(16);
    temp.insert(pair<int, char*> (15, south));
    warehouse -> setExits(temp);
    warehouse -> setItem(5); //sealant
    rooms -> push_back(warehouse);
    temp.clear();
}

void initializeItems(vector<Item*>* items) {
    //items
    //computer key: pick up from android studio and drop in computer room
    Item* key = new Item();
    key -> setName((char*)"Key");
    key -> setId(1);
    items -> push_back(key);
    
    //back up generator: pick up from engine room and drop in fusion reactor
    Item* generator = new Item();
    generator -> setName((char*)"Generator");
    generator -> setId(2);
    items -> push_back(generator);
    
    //hazmat suit: pick up from laboratory and drop in med bay
    Item* hazmat = new Item();
    hazmat -> setName((char*)"Hazmat-Suit");
    hazmat -> setId(3);
    items -> push_back(hazmat);
    
    //fuel tank: pick up from fusion reactor and drop in engine room
    Item* fuel = new Item();
    fuel -> setName((char*)"Fuel-Tank");
    fuel -> setId(4);
    items -> push_back(fuel);
    
    //sealant: pick up from warehouse and drop in engine room
    Item* sealant = new Item();
    sealant -> setName((char*)"Sealant");
    sealant -> setId(5);
    items -> push_back(sealant);
}

void printRoom(vector<Room*>* rooms, vector<Item*>* items, int currentRoom) {
    vector<Room*>::iterator r;
    vector<Item*>::iterator i;
    for (r = rooms->begin(); r != rooms->end(); r++) {
        if (currentRoom == (*r) -> getId()) {
            //room name
            cout << (*r)->getDescription() << endl;
            //exits
            cout << " Exits: ";
            for (map<int, char*>::const_iterator j = (*r) -> getExits() -> begin(); j != (*r) -> getExits() -> end(); j++) {
                cout << j -> second << " ";
            }
            cout << endl;
            //items
            cout << " Items in this room: ";
            int itemCount = 0;
            for (i = items -> begin(); i != items -> end(); i++) {
                if ((*r)->getItem() == (*i)->getId()) {
                    cout << (*i)->getName();
                    itemCount++;
                }
            }
            if (itemCount == 0) {
                cout << "No items in this room." << endl;
            } else {
                cout << endl;
            }            
        }    
    }
}

int move(vector<Room*>* rooms, int currentRoom, char direction[]) {
    vector<Room*>::iterator i;
    for (i = rooms -> begin(); i != rooms -> end(); i++) {
        //get current room
        if (currentRoom == (*i)->getId()) {
            map<int, char*> exits;
            exits = *(*i) -> getExits();
            //get exits
            map<int, char*>::const_iterator m;
            for (m = exits.begin(); m != exits.end(); m++) {
                if (strcmp(m -> second, direction) == 0) {
                    return m -> first;
                }
            }
        }
    }
    return 0;
}

void printInventory(vector<Item*>* items, vector<int> inventory) { //iterate through list of items
    vector<Item*>::iterator i;
    for (i = items->begin(); i != items->end(); i++) {
        for (int j = 0; j < inventory.size(); j++) {
            if (inventory[j] == (*i) -> getId()) {
                cout << (*i) -> getName() << " " << endl; //print out list of items
            }
        }
    }
}

void store(vector<Room*>* rooms, vector<Item*>* items, vector<int>* inventory, int currentRoom, char name[]) {
  vector<Room*>::iterator r;
  vector<Item*>::iterator i;
  for (r = rooms->begin(); r != rooms->end(); r++) {
    if (currentRoom == (*r) -> getId()) {
      for (i = items->begin(); i != items->end(); i++) {
	//if item is in the room
	if (((*r) -> getItem() == (*i) -> getId()) && (strcmp((*i) -> getName(), name) == 0)) {
	  //add to inventory
	  inventory -> push_back((*i) -> getId());
	  //set no item in room
	  (*r) -> setItem(0);
	  cout << endl << "Picked up " << (*i) -> getName() << "." << endl;
	  return;
	}
      }
    } 
  }
  cout << "There is no such item in here." << endl;
}

void drop(vector<Room*>* rooms, vector<Item*>* items, vector<int>* inventory, int currentRoom, char name[]) {
  int counter;
  vector<Room*>::iterator r;
  vector<Item*>::iterator i;
  vector<int>::iterator j;
  for(r = rooms->begin(); r != rooms->end(); r++) { //iterate through rooms
    if(currentRoom == (*r) -> getId()) {
      //if no items in the room
      if ((*r) -> getItem() == 0) {
        for (i = items->begin(); i != items->end(); i++) { //go through items
            //if item exists 
            if (strcmp((*i) -> getName(), name) == 0) { 
                for (j= inventory -> begin(); j!= inventory -> end(); j++) { //go through inventory
                //if item is in inventory
                    if ((*j) == (*i) -> getId()) {
                        cout << endl << "Dropped " << (*i) -> getName() << "." << endl;
                        //set item in current room
                        (*r) -> setItem((*i) -> getId());
                        //remove item from inventory
                        j= inventory -> erase(j);
                        return;
                }
            }
        } else if (counter == items -> size() - 1) {
            cout << endl << "That item is not in your inventory." << endl;
        }
        counter++;
	}
      }
      else {
        cout << endl << "There is already an item in the room." << endl;
      }
    }
  }
}

