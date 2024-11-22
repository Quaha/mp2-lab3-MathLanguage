#pragma once

#include "includes.h"

#include "PrefixTree.h"
#include "Automat.h"

struct Interpreter {

	PrefixTree<void, std::string, char> program_data;
	std::vector<int> number_of_operands; // Stack of the number of operands in the last visible area

	Interpreter();
	void execute(const std::string &line);
};
