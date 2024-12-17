#include <iostream>

#include "Interpreter.h"

int main() {
	
	Interpreter program;

	while (true) {
		std::string line;
		std::cin >> line;

		shared_ptr<Type> result = program.execute(line);
		if (result.get()->getType() == INTEGER) {
			shared_ptr<Integer> temp = std::dynamic_pointer_cast<Integer>(result);
			std::cout << temp.get()->getValue() << std::endl;
		}
		else if (result.get()->getType() == REAL) {
			shared_ptr<Real> temp = std::dynamic_pointer_cast<Real>(result);
			std::cout << temp.get()->getValue() << std::endl;
		}
		else if (result.get()->getType() != NONE) {
			throw std::logic_error("ERROR: something went wrong!");
		}
	}

	return 0;
}