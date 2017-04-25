//////////////////////////////
// Programmer: Jace O'Brien //
// File: error.h            //
//////////////////////////////

#pragma once

namespace error {
	struct error
	{
		std::string err_msg;
		
		error(const char* msg): err_msg(msg) {}
	};
}
