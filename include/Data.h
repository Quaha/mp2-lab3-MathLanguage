#pragma once

#include "includes.h"

// Basic types

struct IntegerData {
	integer value;
};

struct RealData {
	real value;
};

struct VariableData {
	std::string name;
	type type = NONE;
	bool is_const;
};

struct FunctionData {
	std::string name;
};

struct Data {
	type data_type = NONE;
	void* data_ptr = nullptr;

	void destroy();
	void copy(type other_type, void* other_ptr);

	Data() {};
	Data(type other_type, void* other_ptr){}
	~Data();

	Data(const Data& other);
	Data& operator=(const Data& other);

	Data(Data&&) = delete;
	Data& operator=(Data&&) = delete;

	type getType() const{
		return data_type;
	}

	void* getPtr() const{
		return data_ptr;
	}
};

// Basic conversions

inline IntegerData* toIntegerDataPtr(const Data& data) {
	if (data.getType() == INTEGER && data.getPtr()) {
		return static_cast<IntegerData*>(data.getPtr());
	}
	return nullptr;
}

inline RealData* toRealDataPtr(const Data& data) {
	if (data.getType() == REAL && data.getPtr()) {
		return static_cast<RealData*>(data.getPtr());
	}
	return nullptr;
}

inline VariableData* toVariableDataPtr(const Data& data) {
	if (data.getType() == VARIABLE && data.getPtr()) {
		return static_cast<VariableData*>(data.getPtr());
	}
	return nullptr;
}

inline FunctionData* toFunctionDataPtr(const Data& data) {
	if (data.getType() == FUNCTION && data.getPtr()) {
		return static_cast<FunctionData*>(data.getPtr());
	}
	return nullptr;
}