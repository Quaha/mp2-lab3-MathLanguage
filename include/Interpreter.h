#pragma once

#include "includes.h"

#include "PrefixTree.h"
#include "Automat.h"
#include "Data.h"

struct Interpreter {

	struct LexicalAnalyzer {

		Automat tokens_aut;

		set<char> allowed_symbols; // a...z A...Z 0...9 _ ( )
		set<char> separating_characters; // SPACE `
		set<char> names_symbols; // a...z A...Z _ 
		set<char> digits_symbols; // 0...9

		LexicalAnalyzer();

		vector<Data> divideIntoTokens(const string& line) const;
	};

	LexicalAnalyzer lexical_analyzer;

	Interpreter();
	Data execute(const string &line);
};
