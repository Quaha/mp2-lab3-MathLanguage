#pragma once

#include "includes.h"

#include "PrefixTree.h"
#include "Automat.h"

struct Interpreter {

	PrefixTree<void, std::string, char> program_data;
	std::vector<int> number_of_operands; // stack of the number of operands in the last visible area

	struct LexicalAnalyzer {

		Automat tokens;

		std::set<char> allowed_symbols; // a...z A...Z 0...9 _ ( )
		std::set<char> names_symbols; // a...z A...Z _ 
		std::set<char> digits_symbols; // 0...9

		LexicalAnalyzer();

		std::vector<Data> divisionIntoTokens(const std::string& line) const;
	};

	LexicalAnalyzer lexical_analyzer;

	Interpreter();
	Data execute(const std::string &line);
};
