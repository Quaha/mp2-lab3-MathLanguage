#include "includes.h"

#include "functions.h"
#include "Data.h"
#include "ProgramMemory.h"

Data __LEFT__BRACKET__OPERATOR__(const vector<Data>& parameters) {

	if (parameters.size() != 1) {
		throw std::invalid_argument("ERROR: invalid number of arguments!");
	}

    Data current_obj = parameters[0];
    Data result;

    if (current_obj.getType() == INTEGER || current_obj.getType() == REAL) {
        result = current_obj;
    }
    else if (current_obj.getType() == INTEGER_VARIABLE || current_obj.getType() == REAL_VARIABLE) {
        string name = current_obj.getData();
        if (!global_memory->program_data.exists(name)) {
            throw std::invalid_argument("ERROR: using an uninitialized variable!");
        }
        result = global_memory->program_data.getData(name);
    }
    else {
        throw std::invalid_argument("ERROR: invalid argument!");
    }

    return result;
}

Data sum(const vector<Data>& parameters) {
    if (parameters.size() == 0) {
        throw std::invalid_argument("ERROR: invalid number of arguments!");
    }

    Data result;
    bool is_real = false;

    for (int i = 0; i < parameters.size(); i++) {
        if (parameters[i].getType() == REAL || parameters[i].getType() == REAL_VARIABLE) {
            is_real = true;
        }
        if (parameters[i].getType() == VARIABLE) {
            throw std::invalid_argument("ERROR: using an uninitialized variable!");
        }
    }

    if (is_real) {
        result.data_type = REAL;
        real_type value = 0;

        for (int i = 0; i < parameters.size(); i++) {
            if (parameters[i].getType() == REAL || parameters[i].getType() == INTEGER) {
                value += _stor(parameters[i].getData());
            }
            else {
                string name = parameters[i].getData();
                value += _stor(global_memory->program_data.getData(name).getData());
            }
        }

        result.data = _itor(value);
    }
    else {
        result.data_type = INTEGER;
        integer_type value = 0;

        for (int i = 0; i < parameters.size(); i++) {
            if (parameters[i].getType() == INTEGER) {
                value += _stoi(parameters[i].getData());
            }
            else {
                string name = parameters[i].getData();
                value += _stoi(global_memory->program_data.getData(name).getData());
            }
        }

        result.data = _itos(value);
    }
    return result;
}
