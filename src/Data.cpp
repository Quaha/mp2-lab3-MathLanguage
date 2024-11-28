#include "includes.h"

#include "Data.h"

void Data::destroy() {
	if (data_type == INTEGER) {
		delete static_cast<IntegerData*>(data_ptr);
	}
	else if (data_type == REAL) {
		delete static_cast<RealData*>(data_ptr);
	}
	else if (data_type == VARIABLE) {
		delete static_cast<VariableData*>(data_ptr);
	}
	else if (data_type == FUNCTION) {
		delete static_cast<FunctionData*>(data_ptr);
	}

	data_type = NONE;
	data_ptr = nullptr;
}

void Data::copy(type other_type, void* other_ptr) {
	data_type = other_type;

	if (other_ptr == nullptr) return;

	if (other_type == INTEGER) {
		IntegerData* originalPtr = static_cast<IntegerData*>(other_ptr);
		data_ptr = new IntegerData{ originalPtr->value };
	}

	else if (other_type == REAL) {
		RealData* originalPtr = static_cast<RealData*>(other_ptr);
		data_ptr = new RealData{ originalPtr->value };
	}

	else if (other_type == VARIABLE) {
		VariableData* originalPtr = static_cast<VariableData*>(other_ptr);
		data_ptr = new VariableData{ originalPtr->name, originalPtr->type, originalPtr->is_const };
	}

	else if (other_type == FUNCTION) {
		FunctionData* originalPtr = static_cast<FunctionData*>(other_ptr);
		data_ptr = new FunctionData{ originalPtr->name };
	}

	else {
		throw std::runtime_error("Error in Data: unknown type!");
	}
}

Data::Data(type other_type, void* other_ptr) {
	copy(other_type, other_ptr);
}

Data::~Data() {
	destroy();
}

Data::Data(const Data& other){
	copy(other.data_type, other.data_ptr);
}

Data& Data::operator=(const Data& other) {
	if (this == &other) return *this;

	destroy();
	copy(other.data_type, other.data_ptr);

	return *this;
}

Data::Data(Data&& other){
	data_type = other.getType();
	data_ptr = other.getPtr();

	other.data_type = NONE;
	other.data_ptr = nullptr;
}

Data& Data::operator=(Data&& other){
	if (this != &other) {
		destroy();
		data_type = other.data_type;
		data_ptr = other.data_ptr;

		other.data_type = NONE;
		other.data_ptr = nullptr;
	}
	return *this;
}

void* copyVoidPtr(void* ptr, type t) {
	if (!ptr) return nullptr;

	if (t == INTEGER) {
		IntegerData* original = static_cast<IntegerData*>(ptr);
		IntegerData* copy = new IntegerData;
		copy->value = original->value;
		return copy;
	}

	else if (t == REAL) {
		RealData* original = static_cast<RealData*>(ptr);
		RealData* copy = new RealData;
		copy->value = original->value;
		return copy;
	}

	else if (t == VARIABLE) {
		VariableData* original = static_cast<VariableData*>(ptr);
		VariableData* copy = new VariableData;
		copy->name = original->name;
		copy->type = original->type;
		copy->is_const = original->is_const;
		return copy;
	}

	else if (t == FUNCTION) {
		FunctionData* original = static_cast<FunctionData*>(ptr);
		FunctionData* copy = new FunctionData;
		copy->name = original->name;
		return copy;
	}

	else {
		return nullptr;
	}
}