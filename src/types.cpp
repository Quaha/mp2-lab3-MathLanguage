#include "includes.h"

#include "types.h"
#include "ProgramMemory.h"

type Integer::getType() const {
    return INTEGER;
}

type Integer::getValueType() const {
    return INTEGER;
}

integer_type Integer::getValue() const {
    return value;
}



type Real::getType() const {
    return REAL;
}

type Real::getValueType() const {
    return REAL;
}

real_type Real::getValue() const {
    return value;
}



type IntegerVariable::getType() const {
    return INTEGER_VARIABLE;
}

type IntegerVariable::getValueType() const {
    return INTEGER;
}

integer_type IntegerVariable::getValue() const {
    if (!global_memory->program_data.exists(name)) {
        throw std::logic_error("ERROR: an uninitialized variable was used!");
    }

    shared_ptr<Type> data_ptr = global_memory->program_data.getData(name);
    shared_ptr<Integer> result = std::dynamic_pointer_cast<Integer>(data_ptr);
    return result.get()->getValue();
}



type RealVariable::getType() const {
    return REAL_VARIABLE;
}

type RealVariable::getValueType() const {
    return REAL;
}

real_type RealVariable::getValue() const {
    if (!global_memory->program_data.exists(name)) {
        throw std::logic_error("ERROR: an uninitialized variable was used!");
    }

    shared_ptr<Type> data_ptr = global_memory->program_data.getData(name);
    shared_ptr<Real> result = std::dynamic_pointer_cast<Real> (data_ptr);
    return result.get()->getValue();
}