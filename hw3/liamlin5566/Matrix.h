#include <cstddef>
#include <vector>
#include <string>
#include <iostream>

#ifndef MATRIX_H
#define MATRIX_H

class Matrix {

public:

    Matrix(std::size_t nrow, std::size_t ncol)
      : m_nrow(nrow), m_ncol(ncol)
    {
        reset_buffer(nrow, ncol);
    }

    Matrix(Matrix const & other);

    Matrix & operator=(Matrix const & other);

    
    bool operator==(Matrix const &other) const;

    // TODO: move constructors and assignment operators.
   

    double   operator() (std::size_t row, std::size_t col) const
    {
        return m_buffer[index(row, col)];
    }
    double & operator() (std::size_t row, std::size_t col)
    {
        return m_buffer[index(row, col)];
    }

    

    std::size_t nrow() const { return m_nrow; }
    std::size_t ncol() const { return m_ncol; }
    std::size_t size() const { return m_nrow * m_ncol; }


    double buffer(std::size_t i) const { return m_buffer[i]; }
    double * data() const { return m_buffer; }
    
    std::vector<double> buffer_vector() const
    {
        return std::vector<double>(m_buffer, m_buffer+size());
    }

    bool is_transposed() const { return m_transpose; }

    Matrix & transpose()
    {
        m_transpose = !m_transpose;
        std::swap(m_nrow, m_ncol);
        return *this;
    }

    ~Matrix()
    {
        reset_buffer(0, 0);
    }

    std::string toString() const;

private:

    std::size_t index(std::size_t row, std::size_t col) const
    {
        if (m_transpose) { return row          + col * m_nrow; }
        else             { return row * m_ncol + col         ; }
    }

    void reset_buffer(std::size_t nrow, std::size_t ncol);
    

    std::size_t m_nrow = 0;
    std::size_t m_ncol = 0;
    bool m_transpose = false;
    double * m_buffer = nullptr;

};


#endif