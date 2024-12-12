#pragma once

#include "includes.h"

struct Data {
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

    VariableData(const string& name, type var_type): name(name), variable_type(var_type){}

    type getType() const override {
        return VARIABLE;
    }
};

struct FunctionData : public Data {
    string name;
    function_ptr function;

    FunctionData(const string& name, function_ptr func) : name(name), function(func) {}

    type getType() const override {
        return FUNCTION;
    }

    shared_ptr<Data> call(const vector<shared_ptr<Data>>& parameters, Interpreter& program) const {
        return function(parameters, program);
    }
};