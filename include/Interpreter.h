#pragma once

#include "includes.h"

#include "PrefixTree.h"
#include "Automat.h"
#include "Data.h"

struct Interpreter {

	PrefixTree<void, string, char> program_data;
	PrefixTree<void, string, char> names_information;
	vector<int> number_of_operands; // stack of the number of operands in the last visible area

	struct LexicalAnalyzer {

		Automat tokens;

		set<char> allowed_symbols; // a...z A...Z 0...9 _ ( )
		set<char> separating_characters; // SPACE `
		set<char> names_symbols; // a...z A...Z _ 
		set<char> digits_symbols; // 0...9

		LexicalAnalyzer();

		vector<Data> divisionIntoTokens(const std::string& line) const;
	};

	LexicalAnalyzer lexical_analyzer;

	Interpreter();
	Data execute(const std::string &line);
};
