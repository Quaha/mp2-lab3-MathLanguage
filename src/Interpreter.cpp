#include "includes.h"

#include "PrefixTree.h"
#include "Automat.h"
#include "Interpreter.h"
#include "functions.h"
#include "Data.h"
#include "ProgramMemory.h"

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
	analyzer.allowed_symbols.insert(';');
	analyzer.allowed_symbols.insert(',');

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

	// Separating symbols (They are not counted among the allowed ones)
	analyzer.separating_characters.insert(' ');
	analyzer.separating_characters.insert('`');
}

void buildLexicalAnalyzerAutomat(Interpreter::LexicalAnalyzer& analyzer) {
	//Automat states

	analyzer.tokens_aut.setStateStatus(0, NONE); // start state

	analyzer.tokens_aut.setStateStatus(1, INTEGER); // zero integer

	analyzer.tokens_aut.setStateStatus(2, INTEGER); // other integer

	analyzer.tokens_aut.setStateStatus(10, VARIABLE); // variable
	analyzer.tokens_aut.setStateStatus(11, FUNCTION); // function
	analyzer.tokens_aut.setStateStatus(12, SPECIAL_SYMBOL); // special_symbol

	analyzer.tokens_aut.setStateStatus(99, ERROR); // global error


	// Start state
	analyzer.tokens_aut.addTransition(0, 1, '0');
	for (char C = '1'; C <= '9'; ++C) {
		analyzer.tokens_aut.addTransition(0, 2, C);
	}
	for (char C : analyzer.names_symbols) {
		analyzer.tokens_aut.addTransition(0, 10, C);
	}
	analyzer.tokens_aut.addTransition(0, 11, '(');
	analyzer.tokens_aut.addTransition(0, 12, ')');
	analyzer.tokens_aut.addTransition(0, 12, ';');
	analyzer.tokens_aut.addTransition(0, 12, ',');

	// Zero integer
	for (char C : analyzer.allowed_symbols) {
		analyzer.tokens_aut.addTransition(1, 99, C);
	}


	// Other integer
	for (char C : analyzer.allowed_symbols) {
		if (analyzer.digits_symbols.count(C)) {
			analyzer.tokens_aut.addTransition(2, 2, C);
		}
		else {
			analyzer.tokens_aut.addTransition(2, 99, C);
		}
	}


	// Variable
	for (char C : analyzer.allowed_symbols) {
		if (analyzer.names_symbols.find(C) != analyzer.names_symbols.end()) {
			analyzer.tokens_aut.addTransition(10, 10, C);
		}
		else if (C == '(') {
			analyzer.tokens_aut.addTransition(10, 11, C);
		}
		else {
			analyzer.tokens_aut.addTransition(10, 99, C);
		}
	}


	// Function
	for (char C : analyzer.allowed_symbols) {
		analyzer.tokens_aut.addTransition(11, 99, C);
	}


	// Special_symbol
	for (char C : analyzer.allowed_symbols) {
		analyzer.tokens_aut.addTransition(12, 99, C);
	}


	// Global error
	for (char C : analyzer.allowed_symbols) {
		analyzer.tokens_aut.addTransition(99, 99, C);
	}
}

Interpreter::LexicalAnalyzer::LexicalAnalyzer(): tokens_aut(100) {
	processTypesOfSymbols(*this);
	buildLexicalAnalyzerAutomat(*this);
}

vector<Data> Interpreter::LexicalAnalyzer::divideIntoTokens(const string& line) const {
	string correct_line = "";
	for (char C : line) {
		if (separating_characters.count(C)) {
			continue;
		}
		else if (!allowed_symbols.count(C)) {
			throw std::runtime_error("ERROR: a forbidden symbol has been used!");
		}
		else {
			correct_line.push_back(C);
		}
	}
	correct_line.push_back(';');

	vector<Data> tokens(0);

	int curr_state = 0;
	string stack;
	
	for (int curr_position = 0; curr_position < correct_line.size(); ++curr_position) {
		char C = correct_line[curr_position];

		int next_state = tokens_aut.getNextState(curr_state, C);

		int curr_status = tokens_aut.getStatus(curr_state);
		int next_status = tokens_aut.getStatus(next_state);


		if (next_status == ERROR) {
			type curr_status = tokens_aut.getStatus(curr_state);
			if (curr_status == NONE) {
				throw std::runtime_error("ERROR: a lexical error!");
			}
			else if (curr_status == INTEGER ||
					 curr_status == REAL ||
					 curr_status == SPECIAL_SYMBOL){
				
				tokens.push_back(Data(curr_status, stack));
			}
			else if (curr_status == VARIABLE) {
				
				if (!global_memory->program_data.exists(stack)) {
					tokens.push_back(Data(VARIABLE, stack));
				}
				else {
					type variable_type = global_memory->program_data.getData(stack).getType();
					if (variable_type == INTEGER) {
						tokens.push_back(Data(INTEGER_VARIABLE, stack));
					}
					else if (variable_type == REAL) {
						tokens.push_back(Data(REAL_VARIABLE, stack));
					}
					else {
						throw std::runtime_error("ERROR: invalid variable type!");
					}
				}
			}
			else if (curr_status == FUNCTION) {
				if (!global_memory->function_data.exists(stack)) {
					throw std::runtime_error("ERROR: a nonexistent function was found!");
				}
				else {
					tokens.push_back(Data(FUNCTION, stack));
				}
			}
			else if (curr_status == ERROR) {
				throw std::runtime_error("ERROR: something went wrong!");
			}
			else {
				throw std::runtime_error("ERROR: unknown type in lexical analyzer!");
			}
			stack.clear();
			curr_state = 0;
			curr_position--;
		}
		else {
			curr_state = next_state;
			stack.push_back(C);
		}

		if (C == ';') break;

	}
	return tokens;
}

void processFunctionData() {
	global_memory->function_data.addWord("(", std::make_shared<function_type>(__LEFT__BRACKET__OPERATOR__));
	global_memory->function_data.addWord("sum(", std::make_shared<function_type>(sum));
}

Interpreter::Interpreter() {
	global_memory = std::make_unique<MemoryManager>();

	processFunctionData();

}

Data Interpreter::execute(const string& line) {

	vector<Data> tokens = lexical_analyzer.divideIntoTokens(line);

	//for (int i = 0; i < tokens.size(); i++) {
	//	std::cout << tokens[i].getType() << " " << tokens[i].getData() << '\n';
	//}

	vector<Data> values(0);
	vector<Data> actions(0);

	for (int i = 0; i < tokens.size(); i++) {
		Data curr_token = tokens[i];
		if (curr_token.getType() == INTEGER ||
			curr_token.getType() == REAL ||
			curr_token.getType() == VARIABLE ||
			curr_token.getType() == INTEGER_VARIABLE ||
			curr_token.getType() == REAL_VARIABLE) {
			values.push_back(curr_token);
		}
		else if (curr_token.getType() == SPECIAL_SYMBOL) {
			if (curr_token.getData() == ")") {
				vector<Data> parameters(0);
				parameters.push_back(values.back());
				values.pop_back();
				while (actions.back().getData() == ",") {
					actions.pop_back();
					parameters.push_back(values.back());
					values.pop_back();
				}
				reverse(values.begin(), values.end());
				shared_ptr<function_type> function = global_memory->function_data.getData(actions.back().getData());
				actions.pop_back();
				Data result = (*function)(parameters);
				values.push_back(result);
			}
			if (curr_token.getData() == ",") {
				actions.push_back(curr_token);
			}
		}
		else if (curr_token.getType() == FUNCTION) {
			actions.push_back(curr_token);
		}
		else {
			throw std::invalid_argument("ERROR: unknown token type!");
		}
	}

	if (!actions.empty() || values.size() > 1) {
		throw std::runtime_error("ERROR: something went wrong!");
	}

	Data result = values[0];

	if (result.getType() == INTEGER || result.getType() == REAL) {
		return result;
	}
	if (result.getType() == INTEGER_VARIABLE || result.getType() == REAL_VARIABLE) {
		Data result = global_memory->program_data.getData(result.getData());
		return result;
	}
	if (result.getType() == VARIABLE) {
		throw std::runtime_error("ERROR: as a result of the calculations, an uninitialized variable was obtained!");
	}

	return Data();
}
