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
};
