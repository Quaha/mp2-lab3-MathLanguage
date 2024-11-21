#pragma once

#include "includes.h"

#include "PrefixTree.h"
#include "Automat.h"

struct Interpreter {

	PrefixTree<void> program_data;

	Interpreter();

};
