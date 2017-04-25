//////////////////////////////
// Programmer: Jace O'Brien //
// File: vector.h           //
//////////////////////////////

#pragma once

#include "err_file_input.h"

using namespace vector;

/*-----CONSTANTS-----*/
double ZERO_TOL_MIN = -0.00001;
double ZERO_TOL_MAX = 0.00001;
double INNER_TOL_MIN = -0.000000001;
double INNER_TOL_MAX = 0.000000001;

/*-----CLASSES-----*/
template <class T>
class vector
{
    private:
        T* m_data_ptr;
        int m_data_size;
    
    public:
//-----Structors-----//
        // Descr: Default constructor
        // Pre: None
        // Post: Object created and initialized
        vector(T* ptr=nullptr, const int size=0);
                                                
        // Descr: Empty constructor
        // Pre: None
        // Post: Object of size created with empty elements
        vector(const int size);
        
        // Descr: Copy constructor
        // Pre: Assignment operator defined for type T
        // Post: Object created as deep copy of rhs
        vector(const vector& rhs);
        
        // Descr: Move constructor
        // Pre: None
        // Post: Object created with rhs assets
        vector(vector&& rhs);
        
        // Descr: Destructor
        // Pre: None
        // Post: Calling object destroyed
        ~vector();
        
//-----Accessors-----//
        // Descr: Size accessor
        // Pre: None
        // Post: returns size of calling vector
        int size() const {return m_data_size;}
        
        // Descr: Gets a constant refernce to element at index
        // Pre: Bracket operator defined for type T
        // Post: Returns element at index
        T& get(const int index) const;
        
        // Descr: End index accessor
        // Pre: None
        // Post: returns index to end of calling vector
        int end() const {return m_data_size-1;}
        
//-----Binary Operators-----//
        // Descr: Indexing operator
        // Pre: Indexing operator defines for type T
        // Post: Returns a reference to the value at index in calling vector
        T& operator[](const int index);
        
        // Descr: Equivalence operator
        // Pre: Equivalence operator defined for type T
        // Post: Returns true if calling object equals rhs, false otherwise
        // Throws: bad_subscr_err
        bool operator==(const vector& rhs) const;
        
        // Descr: Non-equivalence operator
        // Pre: Equivalence operator defined for type T
        // Post: Returns false if calling object equals rhs, true otherwise
        bool operator!=(const vector& rhs) const;
        
        // Descr: Assignment operator for a vector
        // Pre: Assignment operator defined for type T
        // Post: Calling vector deep copies rhs;
        vector& operator=(const vector& rhs);
        
        // Descr: Additive assignment operator for a vector
        // Pre: Additive assignment operator defined for type T
        // Post: Calling object incremented by values in rhs
        vector& operator+=(const vector& rhs);
        
        // Descr: Additive assignment operator for a T
        // Pre: Additive assignment operator defined for type T
        // Post: Calling object incremented by rhs
        vector& operator+=(const T& rhs);
        
        // Descr: Subtractive assignment operator for a vector
        // Pre: Subtractive assignment operator defined for type T
        // Post: Calling object decremented by values in rhs
        vector& operator-=(const vector& rhs);
        
        // Descr: Subtractive assignment operator for a T
        // Pre: Subtractive assignment operator defined for type T
        // Post: Calling object decremented by rhs
        vector& operator-=(const T& rhs);
        
        // Descr: Scalar assignment operator for a T
        // Pre: Multiplication assignment operator defined for type T
        // Post: Calling object scaled by scalar
        vector& operator*=(const T& scalar);
        
        // Descr: Addition operator
        // Pre: Addition operator defined for type T
        // Post: Returns the sum of calling object and rhs
        vector operator+(const vector& rhs) const;
        
        // Descr: Subtraction operator
        // Pre: Subtraction operator defined for type T
        // Post: Returns difference of calling object and rhs
        vector operator-(const vector& rhs) const;
        
        // Descr: Dot product operator
        // Pre: Additive assignment and multiplication operators
        //      defined for a type T
        // Post: Returns the scalar result of calling object dot rhs
        T operator*(const vector& rhs) const;
        
        // Descr: Scalar multiplication operator
        // Pre: Multiplicative assignment operator defined for type T
        // Post: Returns copy of scaled calling vector
        vector operator*(const T& scalar) const;
        
        // Descr: Scalar division operator
        // Pre: Multiplicative assignment operator defined for type T
        // Post: Returns copy of scaled calling vector
        // Throws: zero_div_err
        vector operator/(const T& scalar) const;
        
        // Descr: Projection operator
        // Pre: Division operator defined for type T
        // Post: Returns the vector result of rhs projected on calling object
        // Note: reads "[rhs] projected onto [calling object]"
        vector operator^(const vector& rhs) const;
        
//-----Unary Operators-----//
        // Descr: Negation operator
        // Pre: Negation operator defined for type T
        // Post: Returns vector with elements negated
        vector operator-();
        
        // Descr: Magnitude operator
        // Pre: Assignment and additive assignment operators defined for type T
        // Post: Returns the scalar result of the magnitude of calling object
        T operator~() const;
        
//-----Friends-----//
        // Descr: Ostream insertion operator
        // Pre: Ostream insertion operator defined for type T
        // Post: Return ostream containing formatted output of rhs
        // Note: In-lined and non-templated upon grader feedback
        friend ostream& operator<<(ostream& os, const vector<T>& rhs)
        {
            for(int i=0; i<rhs.m_data_size; ++i)
            {
                os << rhs.m_data_ptr[i] << " ";
            }
            
            return os;
        }
        
        // Descr: Istream extraction operator
        // Pre: Istream extraction operator defined for type T
        // Post: vector rhs elements assigned values from is
        // Throws: file_input_err
        // Note: In-lined and non-templated upon grader feedback
        friend istream& operator>>(istream& is, vector<T>& rhs)
        {
            int size = rhs.m_data_size;
            T input;
            
            if(size>0)
            {
                for(int i=0; i<size; ++i)
                {
                    if(is.peek() != is.eof())
                    {
                        is >> input;
                        rhs.m_data_ptr[i] = input;
                    } else {
                        throw new error::file_input(
                        "Attempt to input a malformed vector!");
                    }
                }
            }
            
            return is;
        }

//-----Auxiliary Functions-----//
        // Descr: Deletes element at given position
        // Pre: Assignment operator defined for type T
        // Post: 
        vector& j_remove(const int pos);
        
        // Descr: Inserts element at given position
        // Pre: Assignment operator defined for type T
        // Post: 
        vector& j_insert(const int pos, const T& elem);
        
        // Descr: Empty vector initializer
        // Pre: None
        // Post: Calling vector can now contain size objects
        void j_init(const int size);
        
        // Descr: Deep copies a vector
        // Pre: Assignment operator defined for type T
        // Post: Src is deep copied into calling object
        void j_copy(const vector& src);
        
        // Descr: Checks values in vector against zero tolerances
        // Pre: Greater than and less than operators defined for type T
        // Post: Values in calling object within zero tolerances set to zero
        void j_zero_check();
        
        // Descr: Swaps data of rhs and calling vector
        // Pre: None
        // Post: Data of calling vector and rhs swapped
        void j_swap(vector<T>& rhs);
};

