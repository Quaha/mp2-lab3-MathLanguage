#include "includes.h"

Data __RETURN__IT__SELF__(const std::vector<Data>& parameters) { // ()

	if (parameters.empty()) {
                throw std::invalid_argument("");
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
