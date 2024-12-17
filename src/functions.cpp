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
