#include <iostream>

#include "Interpreter.h"

int main() {
	
	Interpreter program;

	while (true) {
		std::string line;
		std::cin >> line;

		Data result = program.execute(line);
		if (result.data_type == INTEGER || result.data_type == REAL) {
			std::cout << result.data << std::endl;
		}
		else if (result.data_type != NONE) {
			throw std::logic_error("ERROR: something went wrong!");
		}
	}

	return 0;
}