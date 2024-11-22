#include "includes.h"

Data __RETURN__IT__SELF__(const std::vector<Data>& parameters) { // ()

	if (parameters.size() != 1) {
                throw std::invalid_argument("Function __RETURN__IT__SELF__ error!");
	}
	
	Data result;

	switch (parameters[0].type) {
		case INTEGER:

		        break;
		case REAL:

		        break;
		case VARIABLE:

			break;
		default:

			break;
	}

	return result;
}
