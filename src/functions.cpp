#include "includes.h"

#include "functions.h"
#include "Interpreter.h"

std::vector<type> getParametersTypes(const std::vector<Data>& parameters, Interpreter& program) {

	int N = parameters.size();
	std::vector<type> parameters_types(N);

	for (int i = 0; i < N; ++i) {
		switch (parameters[i].type) {
		case INTEGER:
			parameters_types[i] = INTEGER;
			break;
		case REAL:
			parameters_types[i] = REAL;
			break;
		case VARIABLE: {
			VariableData* var_ptr = toVariableData(parameters[i]);
			if (!program.program_data.exists(var_ptr->name)) {
				std::invalid_argument("Error in __LEFT__BRACKET__OPERATOR__: using an uninitialized variable " + var_ptr->name + "!");
			}
		}
			break;
		default:
			throw std::invalid_argument("Error in __LEFT__BRACKET__OPERATOR__: invalid type!");
		}
	}

	return parameters_types;
}

Data __LEFT__BRACKET__OPERATOR__(const std::vector<Data>& parameters, Interpreter& program) {

	std::vector<type> parameters_types = getParametersTypes(parameters, program);
	


	return Data();
}
