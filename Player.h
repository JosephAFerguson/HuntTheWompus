#pragma once
class Player {
private:
	int arrows;
	std::string name;
	std::string currRoom;
public:
	Player(std::string n) {
		arrows = 3;
		name = n;
		currRoom = "Start Room";
	}
	std::string getName() {
		return name;
	}
	std::string getRoom() {
		return currRoom;
	}
	void setRoom(std::string s) {
		currRoom = s;
	}
	int getArrows() {
		return arrows;
	}
	void fire() {
		arrows--;
	}
	void retrieveArrow() {
		arrows++;
	}
};