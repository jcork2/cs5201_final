//////////////////////////////
// Programmer: Jace O'Brien //
// File: file_input.h       //
//////////////////////////////

#pragma once

#include "error.h"

namespace error {
	struct file_input : public error
	{
		file_input(const char* msg) : error(msg) {}
	};
}