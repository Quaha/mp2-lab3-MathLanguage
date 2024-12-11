#pragma once

#include "includes.h"

#include "PrefixTree.h"
#include "Automat.h"
#include "Data.h"

struct Interpreter {

	PrefixTree<unique_ptr<Data>, string, char> program_data;
	PrefixTree<unique_ptr<Data>, string, char> names_information;

	struct LexicalAnalyzer {

		Automat tokens;

		set<char> allowed_symbols; // a...z A...Z 0...9 _ ( )
		set<char> separating_characters; // SPACE `
		set<char> names_symbols; // a...z A...Z _ 
		set<char> digits_symbols; // 0...9

		LexicalAnalyzer();

		vector<unique_ptr<Data>> divideIntoTokens(const std::string& line) const;
	};

	LexicalAnalyzer lexical_analyzer;

	Interpreter();
	unique_ptr<Data> execute(const std::string &line);
};
