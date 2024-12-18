#include "includes.h"

#include "functions.h"
#include "Data.h"
#include "ProgramMemory.h"

vector<Data> getValues(const vector<Data>& parameters, int start_pos = 0) {

    bool is_real = false;

    for (int i = start_pos; i < parameters.size(); i++) {
        if (parameters[i].getType() == REAL || parameters[i].getType() == REAL_VARIABLE) {
            is_real = true;
        }
        if (parameters[i].getType() == VARIABLE) {
            throw std::invalid_argument("ERROR: using an uninitialized variable!");
        }
    }

    vector<Data> values(std::max((int)parameters.size() - start_pos, 0));

    if (is_real) {
        for (int j = start_pos; j < parameters.size(); j++) {
            int i = j - start_pos;
            real_type temp;
            if (parameters[j].getType() == REAL || parameters[j].getType() == INTEGER) {
                temp = _stor(parameters[j].getData());
            }
            else {
                string name = parameters[j].getData();
                temp = _stor(global_memory->program_data.getData(name).getData());
            }
            values[i].data_type = REAL;
            values[i].data = _rtos(temp);
        }
    }
    else {
        for (int j = start_pos; j < parameters.size(); j++) {
            int i = j - start_pos;
            integer_type temp;
            if (parameters[j].getType() == INTEGER) {
                temp = _stoi(parameters[j].getData());
            }
            else {
                string name = parameters[j].getData();
                temp = _stoi(global_memory->program_data.getData(name).getData());
            }
            values[i].data_type = INTEGER;
            values[i].data = _itos(temp);
        }
    }
    return values;
}

Data __LEFT__BRACKET__OPERATOR__(const vector<Data>& parameters) {

	if (parameters.size() != 1) {
		throw std::invalid_argument("ERROR: invalid number of arguments!");
	}

    vector<Data> values = getValues(parameters);
    return values[0];
}

Data __PLUS__OPERATOR__(const vector<Data>& parameters) {
    if (parameters.size() == 0 || parameters.size() > 2) {
        throw std::invalid_argument("ERROR: invalid number of arguments!");
    }

    vector<Data> values = getValues(parameters);

    if (values[0].getType() == REAL) {
        if (parameters.size() == 1) {
            return values[0];
        }
        if (parameters.size() == 2) {
            Data result;
            result.data_type = REAL;
            result.data = _rtos(_stor(values[0].getData()) + _stor(values[1].getData()));
            return result;
        }
    }
    if (values[0].getType() == INTEGER) {
        if (parameters.size() == 1) {
            return values[0];
        }
        if (parameters.size() == 2) {
            Data result;
            result.data_type = INTEGER;
            result.data = _itos(_stoi(values[0].getData()) + _stoi(values[1].getData()));
            return result;
        }
    }
    throw std::invalid_argument("ERROR: something went wrong!");
}

Data __MINUS__OPERATOR__(const vector<Data>& parameters) {
    if (parameters.size() == 0 || parameters.size() > 2) {
        throw std::invalid_argument("ERROR: invalid number of arguments!");
    }

    vector<Data> values = getValues(parameters);

    if (values[0].getType() == REAL) {
        if (parameters.size() == 1) {
            Data result = values[0];
            result.data = _rtos(-_stor(result.data));
            return result;
        }
        if (parameters.size() == 2) {
            Data result;
            result.data_type = REAL;
            result.data = _rtos(_stor(values[0].getData()) - _stor(values[1].getData()));
            return result;
        }
    }
    if (values[0].getType() == INTEGER) {
        if (parameters.size() == 1) {
            Data result = values[0];
            result.data = _itos(-_stoi(result.data));
            return result;
        }
        if (parameters.size() == 2) {
            Data result;
            result.data_type = INTEGER;
            result.data = _itos(_stoi(values[0].getData()) - _stoi(values[1].getData()));
            return result;
        }
    }
    throw std::invalid_argument("ERROR: something went wrong!");
}

Data __MULTIPLY__OPERATOR__(const vector<Data>& parameters) {
    if (parameters.size() != 2) {
        throw std::invalid_argument("ERROR: invalid number of arguments!");
    }

    vector<Data> values = getValues(parameters);

    if (values[0].getType() == REAL) {
        Data result;
        result.data_type = REAL;
        result.data = _rtos(_stor(values[0].getData()) * _stor(values[1].getData()));
        return result;
    }
    if (values[0].getType() == INTEGER) {
        Data result;
        result.data_type = INTEGER;
        result.data = _itos(_stoi(values[0].getData()) * _stoi(values[1].getData()));
        return result;
    }
    throw std::invalid_argument("ERROR: something went wrong!");
}

Data __DIVISION__OPERATOR__(const vector<Data>& parameters) {
    if (parameters.size() != 2) {
        throw std::invalid_argument("ERROR: invalid number of arguments!");
    }

    vector<Data> values = getValues(parameters);
    values[0].makeReal();
    values[1].makeReal();

    Data result;
    result.data_type = REAL;
    result.data = _rtos(_stor(values[0].getData()) / _stor(values[1].getData()));
    return result;
}

Data __EQUAL__OPERATOR__(const vector<Data>& parameters) {
    if (parameters.size() != 2) {
        throw std::invalid_argument("ERROR: invalid number of arguments!");
    }

    vector<Data> values = getValues(parameters, 1);

    string name = parameters[0].getData();
    if (parameters[0].getType() != VARIABLE && parameters[0].getType() != REAL_VARIABLE && parameters[0].getType() != INTEGER_VARIABLE) {
        throw std::invalid_argument("ERROR: value can only be assigned to a number!");
    }

    global_memory->program_data.setWord(name, values[0]);

    return Data();
}

Data sum(const vector<Data>& parameters) {
    if (parameters.size() == 0) {
        throw std::invalid_argument("ERROR: invalid number of arguments!");
    }

    vector<Data> values = getValues(parameters);

    Data result;
    result.data_type = values[0].getType();

    if (result.getType() == REAL) {
        real_type temp = 0;
        for (int i = 0; i < values.size(); i++) {
            temp += _stor(values[i].getData());
        }
        result.data = _rtos(temp);
    }
    if (result.getType() == INTEGER) {
        integer_type temp = 0;
        for (int i = 0; i < values.size(); i++) {
            temp += _stoi(values[i].getData());
        }
        result.data = _itos(temp);
    }

    return result;
}
