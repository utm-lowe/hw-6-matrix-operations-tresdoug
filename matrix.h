/**
 * @file matrix.h
 * @author your name (you@domain.com)
 * @brief Class definition and operator prototypes of the Matrix class. 
 * @version 0.1
 * @date 2024-10-08
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef MATRIX_H
#define MATRIX_H
#include <iostream>
#include <iomanip>
#include <stdexcept>

class Matrix 
{
public:
    /**
     * @brief Construct a new Matrix object
     * 
     * @param rows The number of rows in the matrix.
     * @param cols The number of columns in the matrix.
     */
    Matrix(unsigned int rows, unsigned int cols){
        m = rows;
        n = cols;

        ar = new double*[m];

        for(int i = 0; i < m; i++){
            ar[i] = new double[n];
        }
    }

    /**
     * @brief Copy constructor
     * 
     * @param m The matrix to copy.
     */
    Matrix(const Matrix& rhs){
        m = rhs.m;
        n = rhs.n;

        ar = new double*[m];

        for(int i = 0; i < m; i++){
            ar[i] = new double[n];
        }

        for(int i = 0; i < m; i++){
            for(int j = 0; j < n; j++){
                ar[i][j] = rhs.ar[i][j];
            }
        }
    }

    /**
     * @brief Destroy the Matrix object
     * 
     */
    virtual ~Matrix(){
        for(int i = 0; i < m; i++){
            delete[] ar[i];
        }
        delete[] ar;
    }

    /**
     * @brief Get the number of rows in the matrix.
     * 
     * @return int The number of rows in the matrix.
     */
    virtual int getRows() const{
        return m;
    }

    /**
     * @brief Get the number of columns in the matrix.
     * 
     * @return int The number of columns in the matrix.
     */
    virtual int getCols() const{
        return n;
    }

    /**
     * @brief Return a reference to the element at the specified row and column.
     *
     * @param row The row of the element.
     * @param col The column of the element.
     * @return double& A reference to the element at the specified row and column. 
     */
    virtual double& at(unsigned int row, unsigned int col){
        return ar[row][col];
    }

    /**
     * @brief Return a const reference to the element at the specified row and column.
     *
     * @param row The row of the element.
     * @param col The column of the element.
     * @return double& A reference to the element at the specified row and column. 
     */
    virtual const double& at(unsigned int row, unsigned int col) const{
        return ar[row][col];
    }

    /**
     * @brief Overloaded assignment operator.
     * 
     * @param rhs The matrix to assign.
     */
    virtual Matrix& operator=(const Matrix& rhs){
        if (this == &rhs) return *this;  // self-assignment check
        
        // delete old data
        for(int i = 0; i < m; i++){
            delete[] ar[i];
        }
        delete[] ar;
        
        // copy dimensions
        m = rhs.m;
        n = rhs.n;
        
        // allocate new memory
        ar = new double*[m];
        for(int i = 0; i < m; i++){
            ar[i] = new double[n];
        }
        
        // copy data
        for(int i = 0; i < m; i++){
            for(int j = 0; j < n; j++){
                ar[i][j] = rhs.ar[i][j];
            }
        }
        
        return *this;
    }

private:
    double **ar;
    int m;
    int n;
};


/**
 * @brief Overloaded operator for the addition of two matrices.
 * 
 * @param m1 The first matrix.
 * @param m2 The second matrix.
 * @return Matrix The sum of the two matrices.
 */
Matrix operator+(const Matrix& m1, const Matrix& m2){

    Matrix AdditionMartix(m1.getRows(), m1.getCols());

    for(int i = 0; i < m1.getRows(); i++){
        for (int k = 0; k < m1.getCols(); k++){
            AdditionMartix.at(i,k) = m1.at(i,k) + m2.at(i,k);
        }
    }
    return AdditionMartix;
}

/**
 * @brief Overloaded operator for the subtraction of two matrices.
 * 
 * @param m1 The first matrix.
 * @param m2 The second matrix.
 * @return Matrix The difference of the two matrices.
 */
Matrix operator-(const Matrix& m1, const Matrix& m2){

    Matrix SubtractionMatrix(m1.getRows(), m1.getCols());

    for(int i = 0; i < m1.getRows(); i++){
        for(int k = 0; k < m1.getCols(); k++){
            SubtractionMatrix.at(i,k) = m1.at(i,k) - m2.at(i,k);
        }
    }
    return SubtractionMatrix;
}

/**
 * @brief Overloaded operator for the multiplication of two matrices.
 * 
 * @param m1 The first matrix.
 * @param m2 The second matrix.
 * @return Matrix The product of the two matrices.
 */
Matrix operator*(const Matrix& m1, const Matrix& m2){

    int r1 = m1.getRows();
    int c1 = m1.getCols();
    int r2 = m2.getRows();
    int c2 = m2.getCols();

    Matrix result(r1, c2);

    for (int i = 0; i < r1; i++) {
        for (int j = 0; j < c2; j++) {
            result.at(i,j) = 0.0;
            for (int k = 0; k < c1; k++) {
                result.at(i,j) += m1.at(i,k) * m2.at(k,j);
            }
        }
    }

    return result;
}

/**
 * @brief Overloaded operator for the multiplication of a matrix by a scalar.
 * @param scalar The scalar value.
 * @param m The matrix.
 * @return Matrix The product of the matrix and the scalar.
 */
Matrix operator*(double scalar, const Matrix& m){
    
    Matrix ScalarMultiplicationMatrix(m.getRows(), m.getCols());

    for(int i = 0; i < m.getRows(); i++){
        for(int k = 0; k < m.getCols(); k++){
            ScalarMultiplicationMatrix.at(i,k) = scalar * m.at(i,k);
        }
    }
    return ScalarMultiplicationMatrix;
}

/* @brief Overloaded operator for the multiplication of a matrix by a scalar.
 * @param m The matrix.
 * @param scalar The scalar value.
 * @return Matrix The product of the matrix and the scalar.
 */
Matrix operator*(const Matrix& m, double scalar){

    Matrix ScalarMultiplicationMatrix(m.getRows(), m.getCols());

    for(int i = 0; i < m.getRows(); i++){
        for(int k = 0; k < m.getCols(); k++){
            ScalarMultiplicationMatrix.at(i,k) = m.at(i,k) * scalar;
        }
    }
    return ScalarMultiplicationMatrix;
}

/**
 * @brief Overloaded operator for the output of a matrix.
 * 
 * @param os The output stream.
 * @param m The matrix.
 * @return std::ostream& The output stream.
 */
std::ostream& operator<<(std::ostream& os, const Matrix& m){
    for(int i = 0; i < m.getRows(); i++){
        for(int k = 0; k < m.getCols(); k++){
            os << std::setw(10) << m.at(i,k) << " ";
        }
        os << std::endl;
    }
    return os;
}

/**
 * @brief Overloaded operator for the input of a matrix.
 * 
 * @param is The input stream.
 * @param m The matrix.
 * @return std::istream& The input stream.
 */
std::istream& operator>>(std::istream& is, Matrix& m){
    for(int i = 0; i < m.getRows(); i++){
        for (int k = 0; k < m.getCols(); k++){
            is >> m.at(i,k);
        }
    }
    return is;
}

#endif