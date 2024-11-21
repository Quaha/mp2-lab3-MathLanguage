#include "includes.h"

void orderCorrectnessCheck(
	const std::vector<IntegerData>& integer_parameters,
	const std::vector<RealData>& real_parameters,
	const std::vector<type>& types_order) {

	int integer_parametrs_count = integer_parameters.size();
	int real_parameters_count = real_parameters.size();

	for (int i = 0; i < types_order.size(); ++i) {
		if (types_order[i] == INTEGER) {
			--integer_parametrs_count;
		}
		else if (types_order[i] == REAL) {
			--real_parameters_count;
		}
		else {
			throw std::invalid_argument("Incorrect order of parameters!");
		}
	}

	bool correct = (integer_parametrs_count == 0) && (real_parameters_count == 0);
	if (!correct) {
		throw std::invalid_argument("Incorrect order of parameters!");
	}
}

Data __RETURN__IT__SELF__( // ()
	const std::vector<IntegerData>& integer_parameters,
	const std::vector<RealData>& real_parameters,
	const std::vector<type>& types_order) {

	orderCorrectnessCheck(integer_parameters, real_parameters, types_order);

	if (integer_parameters.size() + real_parameters.size() != 1) {
		throw std::invalid_argument("__RETURN__IT__SELF__ function error!");
	}

	Data result;

	if (integer_parameters.size() == 1) {
		result.type = INTEGER;
		IntegerData* data = new IntegerData;

		data->value = integer_parameters[0].value;
		result.data_ptr = data;
	}
	if (real_parameters.size() == 1) {
		result.type = REAL;
		RealData* data = new RealData;

		data->value = real_parameters[0].value;
		result.data_ptr = data;
	}

	return result;
}

Data max( // max(value1, value2, ... )
	const std::vector<IntegerData>& integer_parameters,
	const std::vector<RealData>&    real_parameters,
	const std::vector<type>&    types_order) {
	
	orderCorrectnessCheck(integer_parameters, real_parameters, types_order);

	if (integer_parameters.empty() && real_parameters.empty()) {
		throw std::invalid_argument("The max function must take at least 1 value!");
	}

	Data result;

	if (real_parameters.empty()) {
		result.type = INTEGER;
		IntegerData* data = new IntegerData;

		integer max_value = integer_parameters[0].value;
		for (int i = 1; i < integer_parameters.size(); ++i) {
			if (integer_parameters[i].value > max_value) {
				max_value = integer_parameters[i].value;
			}
		}

		data->value = max_value;
		result.data_ptr = data;
	}
	else {
		result.type = REAL;
		RealData* data = new RealData;

		real max_value = real_parameters[0].value;
		for (int i = 1; i < real_parameters.size(); ++i) {
			if (real_parameters[i].value > max_value) {
				max_value = real_parameters[i].value;
			}
		}
		for (int i = 0; i < integer_parameters.size(); ++i) {
			real current_real_value = itor(integer_parameters[i].value);
			if (current_real_value > max_value) {
				max_value = current_real_value;
			}
		}

		data->value = max_value;
		result.data_ptr = data;
	}

	return result;
}