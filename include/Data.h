#pragma once

#include "includes.h"

class Data {
public:
    virtual ~Data() = default;
    virtual type getType() const = 0;
};

struct IntegerData : public Data {
    integer value;

    IntegerData(integer value) : value(value) {}

    type getType() const override {
        return INTEGER;
    }
};

struct RealData : public Data {
    real value;

    RealData(real value) : value(value) {}

    type getType() const override {
        return REAL;
    }
};

struct VariableData : public Data {
    string name;
    type variable_type = NONE;
    bool is_const;

    VariableData(const string& name, type variable_type, bool is_const)
        : name(name), variable_type(variable_type), is_const(is_const) {}

    type getType() const override {
        return VARIABLE;
    }
};

struct FunctionData : public Data {
    string name;

    FunctionData(const string& name) : name(name) {}

    type getType() const override {
        return FUNCTION;
    }
};