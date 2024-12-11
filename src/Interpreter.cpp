#include "includes.h"

#include "PrefixTree.h"
#include "Automat.h"
#include "Interpreter.h"
#include "functions.h"
#include "Data.h"

Interpreter::LexicalAnalyzer::LexicalAnalyzer(): tokens(100) {
	for (char C = 'a'; C <= 'z'; ++C) {
		allowed_symbols.insert(C);
	}
	for (char C = 'A'; C <= 'Z'; ++C) {
		allowed_symbols.insert(C);
	}
	for (char C = '0'; C <= '9'; ++C) {
		allowed_symbols.insert(C);
	}
	allowed_symbols.insert('_');
	allowed_symbols.insert('(');
	allowed_symbols.insert(')');

	for (char C = 'a'; C <= 'z'; ++C) {
		names_symbols.insert(C);
	}

	for (char C = 'A'; C <= 'Z'; ++C) {
		names_symbols.insert(C);
	}
	names_symbols.insert('_');
	
	separating_characters.insert(' ');
	separating_characters.insert('`');

	//Automat states
	tokens.setStateStatus(0, NONE); // start state

	tokens.setStateStatus(1, INTEGER); // zero integer

	tokens.setStateStatus(2, INTEGER); // other integer

	tokens.setStateStatus(10, VARIABLE); // variable
	tokens.setStateStatus(11, FUNCTION); // function
	tokens.setStateStatus(12, SPECIAL_SYMBOL); // special_symbol

	tokens.setStateStatus(99, ERROR); // global error

	{ // start state
		tokens.addTransition(0, 1, '0');
		for (char C = '1'; C <= '9'; ++C) {
			tokens.addTransition(0, 2, C);
		}
		for (char C : names_symbols) {
			tokens.addTransition(0, 10, '0');
		}
		tokens.addTransition(0, 11, '(');
		tokens.addTransition(0, 12, ')');
	}

	{ // zero integer
		for (char C : allowed_symbols) {
			tokens.addTransition(1, 99, C);
		}
	}

	{ // other integer
		for (char C : allowed_symbols) {
			if (digits_symbols.find(C) != digits_symbols.end()) {
				tokens.addTransition(2, 2, C);
			}
			else {
				tokens.addTransition(2, 99, C);
			}
		}
	}

	{ // variable
		for (char C : allowed_symbols) {
			if (names_symbols.find(C) != names_symbols.end()) {
				tokens.addTransition(10, 10, C);
			}
			else if (C == '(') {
				tokens.addTransition(10, 11, C);
			}
			else {
				tokens.addTransition(10, 99, C);
			}
		}
	}

	{ // function
		for (char C : allowed_symbols) {
			tokens.addTransition(11, 99, C);
		}
	}

	{ // special_symbol
		for (char C : allowed_symbols) {
			tokens.addTransition(12, 99, C);
		}
	}

	{ // global error
		for (char C : allowed_symbols) {
			tokens.addTransition(99, 99, C);
		}
	}
}

vector<Data> Interpreter::LexicalAnalyzer::divisionIntoTokens(const string& line) const {
	string correct_line = "";
	for (char C : line) {
		if (separating_characters.count(C)) {
			continue;
		}
		else if (!allowed_symbols.count(C)) {
			throw std::runtime_error("ERROR: A forbidden symbol has been used: " + C);
		}
		else {
			correct_line.push_back(C);
		}
	}

	vector<Data> result(0);

	int curr_state = 0;
	string stack(0);
	
	for (int curr_position = 0; curr_position < correct_line.size(); ++curr_position) {
		char C = correct_line[curr_position];

		int next_state = tokens.getNextState(curr_state, C);

		int curr_status = tokens.getStatus(curr_state);
		int next_status = tokens.getStatus(next_state);


		if (next_status == ERROR) {
			if (tokens.getStatus(curr_state) == NONE) {
				throw std::runtime_error("ERROR: A lexical error in the following position: " + (char)curr_position);
			}
			else if (tokens.getStatus(curr_state) == INTEGER){
				result.push_back(integerDataToData(stringToIntegerData(stack)));
			}
			else if (tokens.getStatus(curr_state) == REAL) {
				result.push_back(realDataToData(stringToRealData(stack)));
			}
			else if (tokens.getStatus(curr_state) == VARIABLE) {
				
			}
			else if (tokens.getStatus(curr_state) == FUNCTION) {

			}
			else if (tokens.getStatus(curr_state) == OPERAND) {

			}
			else if (tokens.getStatus(curr_state) == SPECIAL_SYMBOL) {

			}
			else if (tokens.getStatus(curr_state) == ERROR) {

			}
			else {
				throw std::runtime_error("ERROR: unknown type in lexical analyzer!");
			}
		}
		else {
			curr_state = next_state;
		}
		stack.push_back(C);
	}

	return result;
}

Interpreter::Interpreter() {

}

Data Interpreter::execute(const string& line) {

	return Data();
}
