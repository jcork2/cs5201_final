//////////////////////////////
// Programmer: Jace O'Brien //
// File: convergence.h      //
//////////////////////////////

#pragma once

#include "error.h"

namespace error {
	struct convergence : public error
	{
		convergence(const char* msg) : error(msg) {}
	};
}