#pragma once

#include "includes.h"

struct Automat {
	struct Node {
		std::map<char, int> next;
		type status;
		Node(type status) : status(status) {};
	};

	std::vector<Node> nodes;

	Automat() {
		nodes.push_back(Node(NONE));
	}

	Automat(size_t size) {
		for (size_t i = 0; i < size; ++i) {
			nodes.push_back(Node(NONE));
		}
	}

	bool nextStateExist(int curr_state, char C) const {
		return (nodes[curr_state].next.find(C) != nodes[curr_state].next.end());
	}

	void createNextState(int curr_state, char C, type status) {
		nodes[curr_state].next[C] = nodes.size();
		nodes.push_back(Node(status));
	}

	void createNewState(type status) {
		nodes.push_back(Node(status));
	}

	void setStateStatus(int curr_state, type status) {
		if (curr_state < 0 || curr_state >= nodes.size()) {
			throw std::out_of_range("The requested state is not in the automat!");
		}
		nodes[curr_state].status = status;
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

	int getNextState(int curr_state, char C) const {
		if (!nextStateExist(curr_state, C)) {
			throw std::out_of_range("The requested state is not in the automat!");
		}
		return (*nodes[curr_state].next.find(C)).second;
	}

	int getStatus(int curr_state) const {
		return nodes[curr_state].status;
	}
};