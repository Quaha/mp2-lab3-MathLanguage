#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <map>

using real = long double;
using integer = long long;

inline real itor(integer value) { // integer to real
	return static_cast<real>(value);
}

inline integer rtoi(real value) { // real to integer
	return static_cast<integer>(value);
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
