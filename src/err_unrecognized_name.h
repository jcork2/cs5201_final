//////////////////////////////
// Programmer: Jace O'Brien //
// File: bad_subscr.h       //
//////////////////////////////

#pragma once

#include "error.h"

namespace error {
	struct unrecognized_name : public error
	{
		unrecognized_name(const char* msg) : error(msg) {}
	};
}