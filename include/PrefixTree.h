#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <map>

template<typename PrefixTreeType> struct PrefixTree {
	struct Node {
		std::map<char, int> next;
		PrefixTreeType* data = nullptr;
		bool is_terminal = false;

		~Node() {
			delete data;
			data = nullptr;
		}
	};

	std::vector<Node> nodes;

	PrefixTree() {
		nodes.push_back(Node());
	}

	bool nextStateExist(int curr_state, char C) {
		return (nodes[curr_state].next.find(C) != nodes[curr_state].next.end());
	}

	void createNextState(int curr_state, char C) {
		nodes[curr_state].next[C] = nodes.size();
		nodes.push_back(Node());
	}

	int getNextState(int curr_state, char C) {
		return nodes[curr_state].next[C];
	}

	void addWord(const std::string& S, PrefixTreeType* data_ptr) {
		int curr_state = 0;
		for (char C : S) {
			if (!nextStateExist(curr_state, C)) {
				createNextState(curr_state, C);
			}
			curr_state = getNextState(curr_state, C);
		}
		nodes[curr_state].data = data_ptr;
		nodes[curr_state].is_terminal = true;
	}

	bool exists(const std::string& S) {
		int curr_state = 0;
		for (char C : S) {
			if (!nextStateExist(curr_state, C)) {
				return false;
			}
			curr_state = getNextState(curr_state, C);
		}
		return nodes[curr_state].is_terminal;
	}

	PrefixTreeType* getData(const std::string& S) {
		int curr_state = 0;
		for (char C : S) {
			if (!nextStateExist(curr_state, C)) {
				throw std::out_of_range("The requested word is not in the prefix tree!");
			}
			curr_state = getNextState(curr_state, C);
		}
		return nodes[curr_state].data;
	}
};