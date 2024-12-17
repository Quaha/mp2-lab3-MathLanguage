#include "includes.h"

#include "functions.h"
#include "types.h"
#include "ProgramMemory.h"

vector<type> getParametersTypes(const vector<shared_ptr<Value>>& parameters) {

    int N = parameters.size();
    vector<type> parameters_types(N, NONE);

    for (int i = 0; i < N; ++i) {
        parameters_types[i] = parameters[i]->getValueType();
    }

    return parameters_types;
}

shared_ptr<Value> __LEFT__BRACKET__OPERATOR__(const vector<shared_ptr<Value>>& parameters) {

	vector<type> parameters_types = getParametersTypes(parameters);

	if (parameters.size() != 1) {
		throw std::invalid_argument("ERROR: invalid number of arguments!");
	}

	type current_type = parameters_types[0];
    shared_ptr<Value> curr_ptr = parameters[0];

    shared_ptr<Value> result = nullptr;

    if (curr_ptr.get()->getType() == INTEGER) {
        return curr_ptr;
    }
    if (curr_ptr.get()->getType() == REAL) {
        return curr_ptr;
    }
    if (curr_ptr.get()->getType() == INTEGER_VARIABLE) {
        shared_ptr<IntegerVariable> temp = std::dynamic_pointer_cast<IntegerVariable>(curr_ptr);
        string name = temp.get()->name;

        if (!global_memory->program_data.exists(name)) {
            throw std::logic_error("ERROR: an uninitialized variable was used!");
        }
        shared_ptr<Value> result = global_memory->program_data.getData(temp.get()->name);
        return result;
    }
    if (curr_ptr.get()->getType() == REAL_VARIABLE) {
        shared_ptr<RealVariable> temp = std::dynamic_pointer_cast<RealVariable>(curr_ptr);
        string name = temp.get()->name;

        if (!global_memory->program_data.exists(name)) {
            throw std::logic_error("ERROR: an uninitialized variable was used!");
        }
        shared_ptr<Value> result = global_memory->program_data.getData(temp.get()->name);
        return result;
    }
}
