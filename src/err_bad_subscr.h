//////////////////////////////
// Programmer: Jace O'Brien //
// File: bad_subscr.h       //
//////////////////////////////

#pragma once

#include "error.h"

namespace error {
	struct bad_subscr : public error
	{
		bad_subscr(const char* msg) : error(msg) {}
	};
}