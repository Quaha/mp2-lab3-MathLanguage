#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <memory>

using real = long double;
using integer = long long;

using std::vector;
using std::string;
using std::map;
using std::set;

using std::unique_ptr;
using std::shared_ptr;
using std::weak_ptr;

using function_ptr = Data(*)(const vector<shared_ptr<Data>>&);

// Basic conversions

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

enum STATUSES : type {
	NONE = 0,
	INTEGER = 1,
	REAL = 2,
	VARIABLE = 3,
	FUNCTION = 4,
	OPERAND = 5,
	SPECIAL_SYMBOL = 6,
	ERROR = 7,
};

/* Special Symbols:
	The right bracket ")" is a special object, which performs the last function
	In fact, left bracket "(" is a function, which takes one number and return it

	The space " " and "`" is a special characters which serves as a visual text separator.
	When processing data, it is deleted.
*/