#pragma once

#include "includes.h"

template<typename DataType, typename ContainerType, typename TransitionType>
struct PrefixTree {
	struct Node {
		std::map<TransitionType, int> next;
		DataType* data = nullptr;
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

	bool nextStateExist(int curr_state, TransitionType C) const {
		return (nodes[curr_state].next.find(C) != nodes[curr_state].next.end());
	}

	void createNextState(int curr_state, TransitionType C) {
		nodes[curr_state].next[C] = nodes.size();
		nodes.push_back(Node());
	}

	int getNextState(int curr_state, TransitionType C) const {
		if (!nextStateExist(curr_state, C)) {
			throw std::out_of_range("The requested state is not in the prefix tree!");
		}
		return (*nodes[curr_state].next.find(C)).second;
	}

	void addWord(const ContainerType& S, DataType* data_ptr) {
		int curr_state = 0;
		for (TransitionType C : S) {
			if (!nextStateExist(curr_state, C)) {
				createNextState(curr_state, C);
			}
			curr_state = getNextState(curr_state, C);
		}
		nodes[curr_state].data = data_ptr;
		nodes[curr_state].is_terminal = true;
	}

	bool exists(const ContainerType& S) const {
		int curr_state = 0;
		for (TransitionType C : S) {
			if (!nextStateExist(curr_state, C)) {
				return false;
			}
			curr_state = getNextState(curr_state, C);
		}
		return nodes[curr_state].is_terminal;
	}

	DataType* getData(const ContainerType& S) const {
		int curr_state = 0;
		for (TransitionType C : S) {
			if (!nextStateExist(curr_state, C)) {
				throw std::out_of_range("The requested word is not in the prefix tree!");
			}
			curr_state = getNextState(curr_state, C);
		}
		return nodes[curr_state].data;
	}
};