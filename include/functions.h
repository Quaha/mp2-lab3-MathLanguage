#pragma once

#include "includes.h"

Data __RETURN__IT__SELF__( // ()
	const std::vector<IntegerData>& integer_parameters,
	const std::vector<RealData>& real_parameters,
	const std::vector<type>& types_order);

Data max( // max(value1, value2, ... )
	const std::vector<IntegerData>& integer_parameters,
	const std::vector<RealData>& real_parameters,
	const std::vector<type>& types_order);