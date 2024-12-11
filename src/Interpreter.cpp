#include "includes.h"

#include "PrefixTree.h"
#include "Automat.h"
#include "Interpreter.h"
#include "functions.h"
#include "Data.h"

void processTypesOfSymbols(Interpreter::LexicalAnalyzer& analyzer) {

	// Allowed symbols
	for (char C = 'a'; C <= 'z'; ++C) {
		analyzer.allowed_symbols.insert(C);
	}
	for (char C = 'A'; C <= 'Z'; ++C) {
		analyzer.allowed_symbols.insert(C);
	}
	for (char C = '0'; C <= '9'; ++C) {
		analyzer.allowed_symbols.insert(C);
	}
	analyzer.allowed_symbols.insert('_');
	analyzer.allowed_symbols.insert('(');
	analyzer.allowed_symbols.insert(')');

	// Degits symbols
	for (char C = '0'; C <= '9'; ++C) {
		analyzer.digits_symbols.insert(C);
	}

	// Names symbols
	for (char C = 'a'; C <= 'z'; ++C) {
		analyzer.names_symbols.insert(C);
	}
	for (char C = 'A'; C <= 'Z'; ++C) {
		analyzer.names_symbols.insert(C);
	}
	analyzer.names_symbols.insert('_');

	// Separating symbols
	analyzer.separating_characters.insert(' ');
	analyzer.separating_characters.insert('`');
}

void buildLexicalAnalyzerAutomat(Interpreter::LexicalAnalyzer& analyzer) {
	//Automat states
	analyzer.tokens.setStateStatus(0, NONE); // start state

	analyzer.tokens.setStateStatus(1, INTEGER); // zero integer

	analyzer.tokens.setStateStatus(2, INTEGER); // other integer

	analyzer.tokens.setStateStatus(10, VARIABLE); // variable
	analyzer.tokens.setStateStatus(11, FUNCTION); // function
	analyzer.tokens.setStateStatus(12, SPECIAL_SYMBOL); // special_symbol

	analyzer.tokens.setStateStatus(99, ERROR); // global error


	// Start state
	analyzer.tokens.addTransition(0, 1, '0');
	for (char C = '1'; C <= '9'; ++C) {
		analyzer.tokens.addTransition(0, 2, C);
	}
	for (char C : analyzer.names_symbols) {
		analyzer.tokens.addTransition(0, 10, '0');
	}
	analyzer.tokens.addTransition(0, 11, '(');
	analyzer.tokens.addTransition(0, 12, ')');


	// Zero integer
	for (char C : analyzer.allowed_symbols) {
		analyzer.tokens.addTransition(1, 99, C);
	}


	// Other integer
	for (char C : analyzer.allowed_symbols) {
		if (analyzer.digits_symbols.find(C) != analyzer.digits_symbols.end()) {
			analyzer.tokens.addTransition(2, 2, C);
		}
		else {
			analyzer.tokens.addTransition(2, 99, C);
		}
	}


	// Variable
	for (char C : analyzer.allowed_symbols) {
		if (analyzer.names_symbols.find(C) != analyzer.names_symbols.end()) {
			analyzer.tokens.addTransition(10, 10, C);
		}
		else if (C == '(') {
			analyzer.tokens.addTransition(10, 11, C);
		}
		else {
			analyzer.tokens.addTransition(10, 99, C);
		}
	}


	// Function
	for (char C : analyzer.allowed_symbols) {
		analyzer.tokens.addTransition(11, 99, C);
	}


	// Special_symbol
	for (char C : analyzer.allowed_symbols) {
		analyzer.tokens.addTransition(12, 99, C);
	}


	// Global error
	for (char C : analyzer.allowed_symbols) {
		analyzer.tokens.addTransition(99, 99, C);
	}
}

Interpreter::LexicalAnalyzer::LexicalAnalyzer(): tokens(100) {

	processTypesOfSymbols(*this);
	buildLexicalAnalyzerAutomat(*this);

	
}

vector<unique_ptr<Data>> Interpreter::LexicalAnalyzer::divideIntoTokens(const string& line) const {
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

	vector<unique_ptr<Data>> result(0);

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
				
			}
			else if (tokens.getStatus(curr_state) == REAL) {
				
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

unique_ptr<Data> Interpreter::execute(const string& line) {

	return unique_ptr<Data>();
}
