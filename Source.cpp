#include <iostream>
#include <random>
#include <string>
#include "Room.h"
#include "Player.h"
#include "Cave.h"
#include "LL.h"

void startPrompt() {
	std::cout << "Welcome to Hunt the Wompus!!\n";
	std::cout << "Please choose your name: ";
}
void welcome(Player p) {
	std::cout << "Hello " << p.getName() << "!\n";
	//more here
}
int playerChoice() { //returns the choice the player wants 
	/* 0 for observe
	*  1 for attack
	*  2 for move
	*  3 for stats
	*/
	std::cout << "\n*****Option Menu*****\n";
	std::cout << "Press 0 to Observe Neighboring Rooms.\n";
	std::cout << "Press 1 to Attack Into a Neighboring Room\n";
	std::cout << "Press 2 to Move Into a Neighboring Room.\n";
	std::cout << "Press 3 to look at your stats.";
	std::cout << "\n*****Option Menu*****\n";
	int res;
	std::cin >> res;
	return res;
}
void inform(Player p, Cave c) {
	std::cout << std::endl <<  p.getName() << " you are currently in " << p.getRoom() << ".\n";
	c.ShowEdges(p.getRoom());
}
int main() {
	Cave cave;
	//Welcome user and tell rules
	startPrompt();
	std::string name;
	std::getline(std::cin, name);
	Player player(name); //instantiate player
	welcome(player);
	bool cont = true;
	bool win = false;
	//Start game
	while (cont) {
		inform(player, cave);
		int choice = playerChoice();
		if (choice >= 0 && choice < 4) {
			switch (choice) {
			case 0: {//Observe
				cave.Observe(player.getRoom());
				break;
			}
			case 1: { //Attack
				if (player.getArrows() == 0) {
					std::cout << "You do not have any arrows to fire.\n";
				}
				else {
					bool res = cave.FireArrow(player);
					if (res) {
						win = true;
						cont = false;
					}
				}
				break;
			}
			case 2: { //Move
				std::string newR = cave.MoveRooms(player.getRoom(), true);
				player.setRoom(newR);
				std::cout << "You have now moved into " << newR << ".\n";
				cont = cave.RespondtoMove(player);
				break;
			}
			case 3: {//view stats
				std::cout << "\n****Player " << player.getName() << "****\n";
				std::cout << "\tArrows: " << player.getArrows() << ".\n";
				std::cout << "****Player " << player.getName() << "****\n";
			}
			}
		}
	}
	if (win) {
		std::cout << "Congrats " << player.getName() << "! You won the game!!\n";
	}
	else {
		std::cout << "You lost.\n";
	}
	return 0;
}