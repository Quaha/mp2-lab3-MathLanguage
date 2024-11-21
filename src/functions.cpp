#include "includes.h"

void orderCorrectnessCheck(const std::vector<integer>& integer_parameters,
	const std::vector<real>& real_parameters,
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

Data max(const std::vector<integer>& integer_parameters,
		 const std::vector<real>&    real_parameters,
	     const std::vector<type>&    types_order         ) {
	
	if (integer_parameters.empty() && real_parameters.empty()) {
		throw std::invalid_argument("The max function must take at least 1 value!");
	}

	orderCorrectnessCheck(integer_parameters, real_parameters, types_order);

	Data result;

	if (real_parameters.empty()) {
		result.type = INTEGER;
		integer* max_value = new integer;
		*max_value = integer_parameters[0];
		for (int i = 1; i < integer_parameters.size(); ++i) {
			if (integer_parameters[i] > *max_value) {
				*max_value = integer_parameters[i];
			}
		}
		result.data_ptr = max_value;
	}
	else {
		result.type = REAL;
		real* max_value = new real;
		*max_value = real_parameters[0];
		for (int i = 1; i < real_parameters.size(); ++i) {
			if (real_parameters[i] > *max_value) {
				*max_value = real_parameters[i];
			}
		}
		for (int i = 0; i < integer_parameters.size(); ++i) {
			real current_real_value = itor(integer_parameters[i]);
			if (current_real_value > *max_value) {
				*max_value = current_real_value;
			}
		}
		result.data_ptr = max_value;
	}

	return result;
}