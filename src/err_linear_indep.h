//////////////////////////////
// Programmer: Jace O'Brien //
// File: linear_indep.h     //
//////////////////////////////

#pragma once

#include "error.h"

namespace error {
	struct linear_indep : public error
	{
		linear_indep(const char* msg) : error(msg) {}
	};
}