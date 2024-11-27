#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>

using real = long double;
using integer = long long;

inline real itor(integer value) { // integer to real
	return static_cast<real>(value);
}

inline integer rtoi(real value) { // real to integer
	return static_cast<integer>(value);
}

inline integer stoi(const std::string value) { // string to integer
	return static_cast<integer>(stoll(value));
}

inline real stor(const std::string value) { // string to real
	return static_cast<real>(stold(value));
}

using type = int;

enum STATUSES: type {
	NONE = 0,
	INTEGER = 1,
	REAL = 2,
	VARIABLE = 3,
	FUNCTION = 4,
	OPERAND = 5,
	SPECIAL_SYMBOL = 6,
	ERROR = 7
};

/* Special Symbols:
	Right bracket ")" is a special object, which performs the last function
	In fact, left bracket "(" is a function, which takes one number and return it

	The comma "," is a special object that separates the input into a function used
	to count the number of arguments
*/

struct Data {
	type type = NONE;
	void* data_ptr = nullptr;
};

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

inline IntegerData* toIntegerData(const Data& data) {
	if (data.type == INTEGER && data.data_ptr) {
		return static_cast<IntegerData*>(data.data_ptr);
	}
	return nullptr;
}

inline RealData* toRealData(const Data& data) {
	if (data.type == REAL && data.data_ptr) {
		return static_cast<RealData*>(data.data_ptr);
	}
	return nullptr;
}

inline VariableData* toVariableData(const Data& data) {
	if (data.type == VARIABLE && data.data_ptr) {
		return static_cast<VariableData*>(data.data_ptr);
	}
	return nullptr;
}

inline FunctionData* toFunctionData(const Data& data) {
	if (data.type == FUNCTION && data.data_ptr) {
		return static_cast<FunctionData*>(data.data_ptr);
	}
	return nullptr;
}
