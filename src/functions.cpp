#include "includes.h"

#include "functions.h"
#include "Interpreter.h"

std::vector<type> getParametersTypes(const std::vector<Data>& parameters, Interpreter& program) {

	int N = parameters.size();
	std::vector<type> parameters_types(N, NONE);

	for (int i = 0; i < N; ++i) {
		type current_type = parameters[i].type;

		if (current_type == INTEGER) {
			parameters_types[i] = INTEGER;
		}

		else if (current_type == REAL) {
			parameters_types[i] = REAL;
		}

		else if (current_type == VARIABLE) {
			VariableData* var_ptr = toVariableDataPtr(parameters[i]);
			if (!program.program_data.exists(var_ptr->name)) {
				std::invalid_argument("Error in function parameters: using an uninitialized variable " + var_ptr->name + "!");
			}
			parameters_types[i] = var_ptr->type;
		}

		else {
			throw std::invalid_argument("Error in function parameters: invalid type!");
		}
	}

	return parameters_types;
}

Data __LEFT__BRACKET__OPERATOR__(const std::vector<Data>& parameters, Interpreter& program) {

	std::vector<type> parameters_types = getParametersTypes(parameters, program);

	Data result;

	if (parameters.size() != 1) {
		throw std::invalid_argument("Error in __LEFT__BRACKET__OPERATOR__: invalid number of arguments!");
	}

	type current_type = parameters_types[0];

	if (current_type == INTEGER) {
		result = getDataCopy(parameters[0]);
	}

	else if (current_type == REAL) {
		result = getDataCopy(parameters[0]);
	}

	else if (current_type == VARIABLE) {
		VariableData* var_ptr = toVariableDataPtr(parameters[0]);
		
		type type = var_ptr->type;
		void *ptr = 

		//*result.data_ptr = program.program_data.getData(var_ptr->name);

	}

	return result;
}
