#pragma once

#include "includes.h"

struct Data {
    type data_type = NONE;
    string data;

    Data() {};
    Data(type data_type, string data): data_type(data_type), data(data) {}

    type getType() const {
        return data_type;
    }

    string getData() const {
        return data;
    }

    void makeInteger() {
        if (data_type == INTEGER || data_type == REAL) {
            data = _itos(_stoi(data));
        }
        else {
            throw std::logic_error("ERROR: this type is not a number!");
        }
    }

    void makeReal() {
        if (data_type == INTEGER || data_type == REAL) {
            data = _rtos(_stor(data));
        }
        else {
            throw std::logic_error("ERROR: this type is not a number!");
        }
    }
};

Data convertToValue(Data data);
Data convertToInteger(Data data);
Data convertToReal(Data data);