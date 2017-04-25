//////////////////////////////
// Programmer: Jace O'Brien //
// File: vector.hpp         //
//////////////////////////////

#pragma once

#include <cmath>
#include "vector.h"
#include "err_zero_div.h"
#include "err_bad_subscr.h"

using namespace vector;

/*-----Constructors-----*/
template <typename T>
vector<T>::vector(T* ptr, const int size)
{
    if(size > 0)
    {
        m_data_size = size;
        m_data_ptr = ptr;
    } else {
        m_data_size = 0;
        m_data_ptr = nullptr;
    }

}

template <typename T>
vector<T>::vector(const int size)
{
    if(size > 0)
    {
        m_data_size = size;
        m_data_ptr = new T[size];
    } else {
        m_data_size = 0;
        m_data_ptr = nullptr;
    }
}

template <typename T>
vector<T>::vector(const vector<T>& rhs)
{
    m_data_size = rhs.m_data_size;
    m_data_ptr = new T[m_data_size];
    for(int i=0; i<m_data_size; ++i)
    {
        m_data_ptr[i] = rhs.m_data_ptr[i];
    }
}

template <typename T>
vector<T>::vector(vector<T>&& rhs)
{
    j_swap(rhs);
    rhs.m_data_ptr = nullptr;
    rhs.m_data_size = 0;
}
template <typename T>
vector<T>::~vector()
{
    if(m_data_ptr != nullptr)
    {
        delete[] m_data_ptr;
    }
    m_data_size = 0;
    m_data_ptr = nullptr;
}

/*-----Accessors-----*/
template <typename T>
T& vector<T>::get(const int index) const
{
    if(m_data_size > 0)
    {
        return m_data_ptr[index];
    } else {
        throw new error::bad_subscr("# Attempt to get vector improperly! (get)");
    }
}
/*-----Binary Operators-----*/
template <typename T>
T& vector<T>::operator[](const int index)
{
    if(index >= 0 && index < m_data_size)
    {
        return m_data_ptr[index];
    } else {
        throw new error::bad_subscr("# Attempt to index vector improperly!");
    }
}

template <typename T>
bool vector<T>::operator==(const vector<T>& rhs) const
{
    bool equivalent = (m_data_size == rhs.m_data_size);
    if(equivalent)
    {
        for(int i=0; (i<m_data_size)&&(equivalent); ++i)
        {
            equivalent = (m_data_ptr[i] == rhs.m_data_ptr[i]);
        }
    }
    
    return equivalent;
}

template <typename T>
bool vector<T>::operator!=(const vector& rhs) const
{
    return !(*this == rhs);
}

template <typename T>
vector<T>& vector<T>::operator=(const vector<T>& rhs)
{
    if(*this != rhs)
    {
        if(m_data_ptr && m_data_size > 0)
        {
            delete[] m_data_ptr;
        }
        m_data_size = rhs.m_data_size;
        m_data_ptr = new T[m_data_size];
        
        for(int i=0; i<m_data_size; ++i)
        {
            m_data_ptr[i] = rhs.m_data_ptr[i];
        }
    }
    
    return *this;
    
}

template <typename T>
vector<T>& vector<T>::operator+=(const vector<T>& rhs)
{
    int size = min(m_data_size, rhs.m_data_size);
    for(int i=0; i<size; ++i)
    {
        m_data_ptr[i] += rhs.m_data_ptr[i];
    }
    j_zero_check();
    return *this;
}

template <typename T>
vector<T>& vector<T>::operator+=(const T& rhs)
{
    for(int i=0; i<m_data_size; ++i)
    {
        m_data_ptr[i] += rhs;
    }
    j_zero_check();
    return *this;
}

template <typename T>
vector<T>& vector<T>::operator-=(const vector<T>& rhs)
{
    int size = min(m_data_size, rhs.m_data_size);
    for(int i=0; i<size; ++i)
    {
        m_data_ptr[i] -= rhs.m_data_ptr[i];
    }
    j_zero_check();
    return *this;
}

template <typename T>
vector<T>& vector<T>::operator-=(const T& rhs)
{
    for(int i=0; i<m_data_size; ++i)
    {
        m_data_ptr[i] -= rhs;
    }
    j_zero_check();
    return *this;
}

template <typename T>
vector<T>& vector<T>::operator*=(const T& scalar)
{
    if(m_data_size > 0)
    {
        for(int i=0; i<m_data_size; ++i)
        {
            m_data_ptr[i] *= scalar;
        }
    }
    j_zero_check();
    return *this;
}
        
template <typename T>        
vector<T> vector<T>::operator+(const vector<T>& rhs) const
{
    vector<T> vector_sum;
    if(m_data_size == rhs.m_data_size)
    {
        vector_sum.j_copy(*this);
        for(int i=0; i<m_data_size; ++i)
        {
            vector_sum.m_data_ptr[i] += rhs.m_data_ptr[i];
        }
    }    
    
    return vector_sum;
}

template <typename T>
vector<T> vector<T>::operator-(const vector<T>& rhs) const
{
    vector<T> vector_dif;
    if(m_data_size == rhs.m_data_size)
    {
        vector_dif.j_copy(*this);
        for(int i=0; i<m_data_size; ++i)
        {
            vector_dif.m_data_ptr[i] -= rhs.m_data_ptr[i];
        }
    }    
    
    return vector_dif;
}

template <typename T>
T vector<T>::operator*(const vector<T>& rhs) const
{
    T inner_prod = 0;
    if((m_data_size > 0)&&(m_data_size == rhs.m_data_size))
    {
        inner_prod = m_data_ptr[0]*rhs.m_data_ptr[0];
        for(int i=1; i<m_data_size; ++i)
        {
            inner_prod += m_data_ptr[i]*rhs.m_data_ptr[i];
        }
    }
    
    return ((inner_prod>INNER_TOL_MIN && inner_prod<INNER_TOL_MAX) ?
            0 : inner_prod);
}

template <typename T>
vector<T> vector<T>::operator*(const T& scalar) const
{    
    vector<T> scaled;
    if(m_data_size > 0)
    {
        scaled.j_copy(*this);
        for(int i=0; i<m_data_size; ++i)
        {
            scaled.m_data_ptr[i] *= scalar;
        }
    }
    
    return scaled;
}

template <typename T>
vector<T> vector<T>::operator/(const T& scalar) const
{    
    if(scalar != 0)
    {
        vector<T> scaled;
        if(m_data_size > 0)
        {
            scaled.j_copy(*this);
            for(int i=0; i<m_data_size; ++i)
            {
                scaled.m_data_ptr[i] *= (1/scalar);
            }
        }
        return scaled;
        
    } else {
        throw new error::zero_div("# Attempt to divide vector by zero scalar!");
    }
    
}

template <typename T>
vector<T> vector<T>::operator^(const vector<T>& rhs) const
{
    vector<T> lhs;
    if((m_data_size > 0) && (m_data_size == rhs.m_data_size))
    {
        lhs.j_copy(*this);
        lhs *= ((rhs*lhs)/(lhs*lhs));
    }
    return lhs;
}

/*-----Unary Operators-----*/
template <typename T>
vector<T> vector<T>::operator-()
{
    vector<T> negation = *this;
    for(int i=0; i<m_data_size; ++i)
    {
        negation[i] = -m_data_ptr[i];
    }
    return negation;
}

template <typename T>
T vector<T>::operator~() const
{
    return sqrt((*this)*(*this));
}

/*-----Auxiliary Functions-----*/
template <typename T>
vector<T>& vector<T>::j_remove(const int pos)
{
    if(pos > 0 && pos < m_data_size)
    {
        T* new_data = new T[m_data_size-1];
        
        // Copy up to position
        for(int i=0; i<pos; ++i)
        {
          new_data[i] = m_data_ptr[i];
        }
        
        // Copy past position
        for(int i=pos+1; i<m_data_size; ++i)
        {
          new_data[i] = m_data_ptr[i];
        }
        
        // Update self
        --m_data_size;
        delete[] m_data_ptr;
        m_data_ptr = new_data;
    } else {
        throw new error::bad_subscr("# Attempt to remove element at invalid index!");
    }
    
    
    return *this;
}

template <typename T>
vector<T>& vector<T>::j_insert(const int pos, const T& elem)
{
    T* new_data = new T[m_data_size+1];
    
    // Copy up to position
    for(int i=0; i<pos; ++i)
    {
      new_data[i] = m_data_ptr[i];
    }
    
    // Add at position
    new_data[pos] = elem;
    
    // Copy past position
    for(int i=pos+1; i<m_data_size+1; ++i)
    {
      new_data[i] = m_data_ptr[i-1];
    }
    
    // Update self
    ++m_data_size;
    delete[] m_data_ptr;
    m_data_ptr = new_data;
    
    return *this;
}

template <typename T>
void vector<T>::j_init(const int size)
{
    if(!m_data_ptr)
    {
        if(size > 0)
        {
            m_data_size = size;
            m_data_ptr = new T[size];
        } else {
            cout << "J_VEC_INIT ERROR: size" << endl;
        }
        
    } else {
        cout << "J_VEC_INIT ERROR: ptr" << endl;
    }
}

template <typename T>
void vector<T>::j_copy(const vector<T>& src)
{
    if(*this != src)
    {
        m_data_size = src.m_data_size;
        if(m_data_ptr)
            delete m_data_ptr;
        m_data_ptr = new T[m_data_size];
        
        for(int i=0; i<m_data_size; ++i)
        {
            m_data_ptr[i] = src.m_data_ptr[i];
        }
    }
}

template <typename T>
void vector<T>::j_zero_check()
{
    for(int i=0; i<m_data_size; ++i)
    {
        if((m_data_ptr[i] > ZERO_TOL_MIN) && (m_data_ptr[i] < ZERO_TOL_MAX))
        {
            m_data_ptr[i] = 0;
        }
    }
}

template <typename T>
void vector<T>::j_swap(vector<T>& rhs)
{
    int data_size_tmp = m_data_size;
    T* data_ptr_tmp = m_data_ptr;
    
    m_data_size = rhs.m_data_size;
    m_data_ptr = rhs.m_data_ptr;
    
    rhs.m_data_size = data_size_tmp;
    rhs.m_data_ptr = data_ptr_tmp;
}