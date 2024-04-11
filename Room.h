#pragma once
class Room {
private:
	std::string name;
	bool arrow;
	std::string danger;
	/* danger is a string
	* 0 represents no danger
	* bat represents the bats
	* hole represents the bottomless holes
	*/
	bool visited;
	bool wompus;
	
public:
	Room() {
		name = "";
		arrow = false;
		danger = "0";
		visited = false;
		wompus = false;
	}
	Room(std::string n) {
		name = n;
		arrow = false;
		danger = "0";
		visited = false;
		wompus = false;
	}
	std::string getName() {
		return name;
	}
	std::string getDanger() {
		return danger;
	}
	void setDanger(std::string d) {
		danger = d;
	}
	bool getVisited() {
		return visited;
	}
	bool getArrow() {
		return arrow;
	}
	void setArrow(bool in) {
		arrow = in;
	}
	void setVisited(bool b) {
		visited = b;
	}
	bool getWompus() {
		return wompus;
	}
	void setWompus(bool b) {
		wompus = b;
	}

	bool ArrowFire(int depth);
	bool Observe() {
		bool res = true;
		if (danger == "0") {
			res = false;
		}
		if (wompus) {
			std::cout << "You smell an animal smell!\n";
			res = true;
		}
		if (danger == "bat") {
			std::cout << "You hear screeching!\n";
			res = true;
		}
		if (danger == "hole") {
			std::cout << "You feel a breeze!\n";
			res = true;
		}
		return res;
	};

	bool operator==(std::string r) {
		return name == r;
	}
	bool operator!=(std::string r) {
		return name != r;
	}
	bool operator==(Room r) {
		return name == r.getName();
	}
	bool operator!=(Room r) {
		return name != r.getName();
	}
	operator std::string() {
		return name;
	}
};