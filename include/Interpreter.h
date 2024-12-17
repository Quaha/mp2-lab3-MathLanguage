#pragma once

#include "includes.h"

#include "PrefixTree.h"
#include "Automat.h"
#include "types.h"

struct Interpreter {

	PrefixTree<shared_ptr<Type>, string, char> program_data;
	PrefixTree<shared_ptr<Type>, string, char> names_information;

	struct LexicalAnalyzer {

		Automat tokens;

		set<char> allowed_symbols; // a...z A...Z 0...9 _ ( )
		set<char> separating_characters; // SPACE `
		set<char> names_symbols; // a...z A...Z _ 
		set<char> digits_symbols; // 0...9

		LexicalAnalyzer();

		vector<shared_ptr<Type>> divideIntoTokens(const string& line) const;
	};

	LexicalAnalyzer lexical_analyzer;

	Interpreter();
	shared_ptr<Type> execute(const string &line);
};
