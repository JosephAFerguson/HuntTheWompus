#pragma once
#include "LL.h"
const int rooms = 20;
const std::string roomnames[rooms] = { "Start Room", "Germany", "England", "Australia"
, "United States", "Canada", "Mexico", "South America", "Hawaii", "Africa", "Antartica",
"Artic", "Nowhere", "Russia", "Japan", "Islands",
"Top of the World", "Where Am I??", "Somehow in University of Cincinnati", "Surely the End" };
class Cave {
private:
	Room places[rooms]; //stores the actual rooms themselves, these will hold the values we will be using
	LL<Room> tunnels[rooms]; //stores the connections as an adjacency matrix (directed), holding blank room classes with the names
	//helper functions
	int retrieve(std::string n) {//helper function, retrieves the index of the room we want
		for (int i = 0; i < rooms; i++) {
			if (roomnames[i] == n) {
				return i;
			}
		}
	}; 
	bool notIn(int r, int arr[5]) { // returs true if an array of ints does not have a given int in it , false otherwise
		for (int i = 0; i < 5; i++) {
			if (arr[i] == r) {
				return false;
			}
		}
		return true;
	}
	LL<Room>* OutEdges(std::string n) { //retreives the linked list of adjacent rooms to a given room
		int index = retrieve(n);
		return &tunnels[index];
	};
	int wheresWompus() { //searches all rooms for the wompus and returns the index of it
		for (int i = 0; i < rooms; i++) {
			if (places[i].getWompus()) {
				return i;
			}
		}
	}
public:
	Cave() {
		for (int i = 0; i < rooms; i++) { //generates names and rooms
			places[i] = Room(roomnames[i]);
		}
		for (int i = 0; i < rooms; i++) { //generates edges between vertices at random except that no vertice (besides the first one) connects to the start
			srand(time(NULL) ^ rand());
			int randAm = rand() % 3 + 2; //generates random num 2-4
			int adds[5] = { 0,0,0,0,0 }; //already added connections
			for (int j = 0; j < randAm;j++) {
				//need to add functionality that we don't add a connection thats already a connection to the room
				int r = rand() % 19 + 1; //generates random num 1-19
				if (r != i && notIn(r, adds)) { //guarentees no self loops
					tunnels[i].add(places[r]);
					adds[j] = r;
				}
				else {
					j--;
				}
			}
		}
		//put random dangers in 
		int rand1 = rand() % 19 + 1; //1-19
		int rand2 = rand() % 19 + 1;
		int rand3 = rand() % 19 + 1;
		while (rand1 == rand2 || rand2 == rand3 || rand1 == rand3) {
			//make sure the dangers do not overlap
			rand1 = rand() % 19 + 1; 
			rand2 = rand() % 19 + 1;
			rand3 = rand() % 19 + 1;
		}
		places[rand1].setDanger("bat");
		places[rand2].setDanger("hole");
		places[rand3].setWompus(true); //later on the wompus can be in the same place as the other dangers, but at the start it won't be
	};//initializer
	void ShowEdges(std::string rn) {//prints the neighboring rooms to the given room name
		LL<Room>* adjacents = OutEdges(rn);
		std::cout << "You see " << adjacents->getLen() << " neighboring rooms. They are called ";
		adjacents->printContents();
		std::cout << ".\n";
	}
	void Observe(std::string rn) { //oberserves neighboring rooms of a given room name
		LL<Room>* currEdges = OutEdges(rn); //gets neighboring rooms
		int size = currEdges->getLen(); //gets amount of adj rooms
		Room* adjNodes = currEdges->convToArr(); //gets an array of the adjacent rooms
		int s = 0;
		for (int i = 0; i < size; i++) {
			//goes through all the adjacent rooms and observes their dangers
			std::string n = adjNodes[i].getName();
			Room toObs = places[retrieve(n)];
			bool res = toObs.Observe();
			if (!res) {
				s++;//no dangers in ith room
			}
		}
		if (s==size) {//no dangers in any of the rooms
			std::cout << "You can't see or hear anything in the neighboring rooms!\n";
		}
	}
	/*bool HasEdge(std::string currRoom, std::string goToRoom) { //checks if the user's choice to go to a room was valid
		int index = retrieve(goToRoom);
		LL<Room>* rs = OutEdges(currRoom);
		if (rs->get(places[index]) == nullptr) {
			return false;
		}
		return true;
	};*/
	std::string MoveRooms(std::string currRoom, bool option) { //returns room to move to also considering the user has an option or not
		LL<Room>* adj = OutEdges(currRoom);
		int size = adj->getLen();
		Room* adjRooms = adj->convToArr(); //array of neighboring rooms
		int choice = 0;

		if (option) {
			while (choice <1 || choice >size) { //outputs choice to user
				for (int i = 0; i < size; i++) {
					std::cout << "Press " << i + 1 << " to move to " << adjRooms[i].getName() << ".\n";
				}
				std::cin >> choice;
			}
		}
		else {
			choice = rand() % size + 1; //random choice
		}
		return adjRooms[choice - 1].getName(); //returns room name chosen

	}
	bool RespondtoMove(Player& p) { //returns loss or not
		//gets dangers of room player is in
		int ind = retrieve(p.getRoom());
		Room rm = places[ind];
		std::string dang = rm.getDanger();
		bool arr = rm.getArrow();
		bool womp = rm.getWompus();
		if (dang == "0" && !womp) {
			std::cout << "No danger present!\n";
			if (arr) {
				std::cout << "You saw an arrow you fired and picked it up!\n";
				p.retrieveArrow();
				places[retrieve(rm.getName())].setArrow(false);
			}
			return true;
		}
		else if (dang == "0") {//wompus
			std::cout << "You were attacker by the wompus!\n";
			if (p.getArrows() == 0) {
				std::cout << "You had no arrows remaining and were beaten by the wompus";
				return false;
			}
			else {
				p.fire(); //wompus is present and we have arrows so fire at it
				std::cout << "You fired at the wompus at it ran away!.\n";
				//move wompus
				rm.setWompus(false);
				int randNew = rand() % 19 + 1; //give wompus new random room
				while (randNew != ind) {
					randNew = rand() % 19 + 1;
				}
				places[randNew].setWompus(true);
			}
		}
		if (dang == "hole") {
			std::cout << "You fell into a bottomless pit.\n";
			return false; //loss
		}
		else if (dang == "bat") {
			std::cout << "You ran into a colony of bats and became disoriented!.\n";
			p.setRoom(MoveRooms(p.getRoom(), false)); //moves player to a new random room, does not have option
			return RespondtoMove(p); //calls itself to respond to the new room the user was moved to
		}
		return true;
	}
	bool FireArrow(Player& p) {//returns hit or not
		p.fire(); //duh
		LL<Room>* adj = OutEdges(p.getRoom());
		int size = adj->getLen();
		Room* adjRooms = adj->convToArr();//array of adjacent rooms
		//gets users choice to fire into
		int choice = 0;
		while (choice <1 || choice >size) {
			for (int i = 0; i < size; i++) {
				std::cout << "Press " << i + 1 << " to fire into " << adjRooms[i].getName() << ".\n";
			}
			std::cin >> choice;
		}
		Room first = adjRooms[choice - 1]; // room chosen to fire into
		first = places[retrieve(first.getName())]; //because we will be altering values, get the room from the places array that actually will be modified
		//need to set visited, store in an array so when array is done firing, we can unset the visited
		int depth = rand() % 3 + 1;// 1-3, amount of extra rooms to traverse ( we already did one
		std::string* visits = new std::string[depth + 1]; //keep track of visited
		visits[0] = first.getName(); //store name of first visited area
		first.setVisited(true);
		int visit = 1;
		if (first.getWompus()) { //arrow in the same room of wompus = hit wompus
			std::cout << "You hit the wompus!!\n";
			return true;
		}
		bool cont = true;
		while (depth > 0 && cont) {
			//continue to do this procedure for random selected rooms until arrow has visited all rooms to chose, or we have visited max depth
			adj = OutEdges(first.getName());
			int size = adj->getLen();
			adjRooms = adj->convToArr();
			int visiteds = 0;
			for (int i = 0; i < size; i++) {
				if (adjRooms[i].getVisited()) {
					visiteds++;
				}
			}

			int whichone = rand() % size;
			first = adjRooms[whichone];
			first = places[retrieve(first.getName())];
			visits[visit] = first.getName();
			first.setVisited(true);
			visit++;
			if (first.getWompus()) {
				std::cout << "You hit the wompus!!\n";
				return true;
			}
			if (visiteds == size) {
				cont = false;
			}
			depth--;
		}

		//unvisit all spots the arrow visited except for the one it landed in
		for (int i = 0; i < depth+1; i++) {
			places[retrieve(visits[i])].setVisited(false);
		}
		first.setArrow(true); //there is an arrow in first now
		first.setVisited(false);
		int set = retrieve(first.getName());
		places[set] = first;
		
		std::cout << "You missed and the wompus ran away.\n"; //we havent returned yet so we missed

		//wherever wompus was we give him a new random home because we missed
		int wompNum = wheresWompus();
		places[wompNum].setWompus(false);
		int randNew = rand() % 19 + 1;
		while (randNew == wompNum) {
			randNew = rand() % 19 + 1;
		}
		places[randNew].setWompus(true);
		return false;
	}
};