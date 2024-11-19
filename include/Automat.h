#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <map>

enum STATUSES {
	NONE     = 0,
	INTEGER  = 1,
	REAL     = 2,
	VARIABLE = 3,
	FUNCTION = 4,
	OPERAND  = 5,
	RIGHT_BRACKET = 6
};

// Right bracket ")" is a special object, which performs the last function
// In fact, left bracket "(" is a function, which takes one number and return it

struct Automat {
	struct Node {
		std::map<char, int> next;
		int status = NONE;
		Node(int status) : status(status) {};
	};

	std::vector<Node> nodes;

	Automat() {
		nodes.push_back(Node(NONE));
	}

	bool nextStateExist(int curr_state, char C) {
		return (nodes[curr_state].next.find(C) != nodes[curr_state].next.end());
	}

	void createNextState(int curr_state, char C, int status) {
		nodes[curr_state].next[C] = nodes.size();
		nodes.push_back(Node(status));
	}

	void createNewState(int status) {
		nodes.push_back(Node(status));
	}

	void addTransition(int curr_state, int next_state, char C) {
		if (curr_state < 0 || curr_state >= nodes.size()) {
			throw std::out_of_range("The requested state is not in the automat!");
		}
		if (next_state < 0 || next_state >= nodes.size()) {
			throw std::out_of_range("The requested state is not in the automat!");
		}
		if (nextStateExist(curr_state, C)) {
			throw std::out_of_range("Such a transition already exists in the automat!");
		}
		nodes[curr_state].next[C] = next_state;
	}

	int getNextState(int curr_state, char C) {
		if (!nextStateExist(curr_state, C)) {
			throw std::out_of_range("The requested state is not in the automat!");
		}
		return nodes[curr_state].next[C];
	}

	int getStatus(int curr_state) {
		return nodes[curr_state].status;
	}
};