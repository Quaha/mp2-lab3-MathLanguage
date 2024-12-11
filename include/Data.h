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
	string name;
	type type = NONE;
	bool is_const;
};

struct FunctionData {
	string name;
};

struct Data {
	type data_type = NONE;
	void* data_ptr = nullptr;

	void destroy();
	void copy(type other_type, void* other_ptr);

	Data() {};
	Data(type other_type, void* other_ptr);
	~Data();

	Data(const Data& other);
	Data& operator=(const Data& other);

	Data(Data&& other);
	Data& operator=(Data&& other);

	type getType() const{
		return data_type;
	}

	void* getPtr() const{
		return data_ptr;
	}
};

void* copyVoidPtr(void* ptr, type t);

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

inline IntegerData stringToIntegerData(const std::string& S) {
	IntegerData result;
	result.value = stoll(S);
	return result;
}

inline RealData stringToRealData(const std::string& S) {
	RealData result;
	result.value = stol(S);
	return result;
}

inline VariableData stringToVariableData(const std::string& S) {
	VariableData result;
	//code
	return result;
}

inline FunctionData stringToFunctionData(const std::string& S) {
	FunctionData result;
	//code
	return result;
}

inline Data integerDataToData(const IntegerData& integerData) {
	Data result;
	result.data_type = INTEGER;
	result.data_ptr = new IntegerData(integerData);
	return result;
}

inline Data realDataToData(const RealData& realData) {
	Data result;
	result.data_type = REAL;
	result.data_ptr = new RealData(realData);
	return result;
}

inline Data variableDataToData(const VariableData& variableData) {
	Data result;
	result.data_type = VARIABLE;
	result.data_ptr = new VariableData(variableData);
	return result;
}

inline Data functionDataToData(const FunctionData& functionData) {
	Data result;
	result.data_type = FUNCTION;
	result.data_ptr = new FunctionData(functionData); 
	return result;
}

