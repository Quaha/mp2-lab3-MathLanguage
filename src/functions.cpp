#include "includes.h"

#include "functions.h"
#include "Interpreter.h"
#include "Data.h"

vector<type> getParametersTypes(const vector<shared_ptr<Data>>& parameters, Interpreter& program) {

    int N = parameters.size();
    vector<type> parameters_types(N, NONE);

    for (int i = 0; i < N; ++i) {
        type current_type = parameters[i]->getType();

        if (current_type == INTEGER) {
            parameters_types[i] = INTEGER;
        }

        else if (current_type == REAL) {
            parameters_types[i] = REAL;
        }

        else if (current_type == VARIABLE) {
            VariableData* variable_ptr = dynamic_cast<VariableData*>(parameters[i].get());
            if (!program.program_data.exists(variable_ptr->name)) {
                throw std::invalid_argument("ERROR: using an uninitialized variable!");
            }

            
            parameters_types[i] = var_ptr->varType;
        }
        else {
            throw std::invalid_argument("ERROR: invalid type!");
        }
    }

    return parameters_types;
}

Data __LEFT__BRACKET__OPERATOR__(const vector<Data>& parameters, Interpreter& program) {

	vector<type> parameters_types = getParametersTypes(parameters, program);

	Data result;

	if (parameters.size() != 1) {
		throw std::invalid_argument("Error in __LEFT__BRACKET__OPERATOR__: invalid number of arguments!");
	}

	type current_type = parameters_types[0];

	if (current_type == INTEGER) {
		result = parameters[0];
	}

	else if (current_type == REAL) {
		result = parameters[0];
	}

	else if (current_type == VARIABLE) {
		VariableData* var_ptr = toVariableDataPtr(parameters[0]);
		
		type type = var_ptr->type;
		void* ptr = copyVoidPtr(program.program_data.getData(var_ptr->name), type);

		result.data_type = type;
		result.data_ptr = ptr;

	}

	return result;
}
