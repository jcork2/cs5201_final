//////////////////////////////
// Programmer: Jace O'Brien //
// File: size_mismatch.h    //
//////////////////////////////

#pragma once

#include "error.h"

namespace error {
	struct size_mismatch : public error
	{
		size_mismatch(const char* msg) : error(msg) {}
	};
}