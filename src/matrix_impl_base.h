///////////////////////////////////
// Programmer: Jace O'Brien      //
// File: matrix_impl_base.h      //
// Purpose: base implementation  //
//   for matrix data structure   //
///////////////////////////////////

#pragma once

#include "matrix_base.h"
#include "vector.h"

using namespace matrix;

class matrix_impl_base : public virtual matrix_base
{
    private:
        int m_size;
        vector::vector<vector::vector<T> > m_matrix;
    public:
        virtual int get_size() const {return m_size;};
};