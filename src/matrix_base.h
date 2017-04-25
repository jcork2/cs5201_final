///////////////////////////////////
// Programmer: Jace O'Brien      //
// File: matrix_base.h           //
// Purpose: base interface class //
//   for matrix data structure   //
///////////////////////////////////

#pragma once

using namespace matrix;

class matrix_base
{
    public:
        virtual int get_size() const =0;
};