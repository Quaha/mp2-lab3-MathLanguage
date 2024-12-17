#pragma once

#include "includes.h"

struct Type {
    virtual ~Type() = default;
    virtual type getType() const = 0;
};

struct Value : public Type {
    virtual type getValueType() const = 0;
};

struct Integer : public Value {
    integer_type value;

    Integer(integer_type value) : value(value) {}

    type getType() const override;
    type getValueType() const override;
    integer_type getValue() const;
};

struct Real : public Value {
    real_type value;

    Real(real_type value) : value(value) {}

    type getType() const override;
    type getValueType() const override;
    real_type getValue() const;
};

struct IntegerVariable : public Value {
    string name;

    IntegerVariable(const string& name): name(name){}

    type getType() const override;
    type getValueType() const override;
    integer_type getValue() const;
};

struct RealVariable : public Value {
    string name;

    RealVariable(const string& name) : name(name){}

    type getType() const override;
    type getValueType() const override;
    real_type getValue() const;
};

using function_ptr = std::function<shared_ptr<Value>(const vector<shared_ptr<Value>>&)>;

struct FunctionData : public Type {
    string name;
    function_ptr function;

    FunctionData(const string& name, function_ptr function) : name(name), function(function) {}

    type getType() const override {
        return FUNCTION;
    }

    shared_ptr<Type> call(const vector<shared_ptr<Value>>& parameters) const {
        return function(parameters);
    }
};