//////////////////////////////
// Programmer: Jace O'Brien //
// File: zero_div.h         //
//////////////////////////////

#pragma once

#include "error.h"

namespace error {
	struct zero_div : public error
	{
		zero_div(const char* msg) : error(msg) {}
	};
}