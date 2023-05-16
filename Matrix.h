// Matrix.h
#ifndef MATRIX_H
#define MATRIX_H


/***************************/
/*         include         */
/***************************/
#include "iostream"
#include <cmath>
#include <string>
/***************************/


/***************************/
/*         using           */
/***************************/
using std::ostream;
using std::istream;
/***************************/

/***************************/
/*         define          */
/***************************/
#define ONE_VECTOR 1
#define EMPTY 1
#define FIRST 0
#define START 0
#define POW_BASE 2
#define LAST_ONE ((_dims.cols) - (1))
#define SPACE " "
#define TWO_ASTERISKS 0.1
#define LENGTH_ERROR "the given matrix dimensions are invalid.\n"
#define OUT_OF_RANGE_ERROR "there is out of range error.\n"
#define RUNTIME_ERROR "the input is invalid"
/***************************/

/**
 * @struct matrix_dims
 * @brief Matrix dimensions container. Used in MlpNetwork.h and main.cpp
 */
typedef struct matrix_dims
{
    int rows, cols;
} matrix_dims;

/**
 * @class Matrix
 * @brief contain Matrix and her size,
 * include functions and operators for matrix.
 */
class Matrix
{

 private:

  /***** private members ****/
  matrix_dims _dims{}; //member for the dims of the matrix
  float **_matrix; //member for the data of the matrix

  /***** private functions ****/
  void delete_matrix (); //delete the data of the matrix
  void create_inside_arrays (); //create the inside arrays
  friend void swap (Matrix &lhs, Matrix &rhs); //swap the members of the obj
  float find_index_sum (const Matrix &lhs, int i, int j) const;

 public:

  /***** constructors ****/
  Matrix (int rows, int cols);
  Matrix () : Matrix (EMPTY, EMPTY){}
  Matrix (const Matrix &m);
  ~Matrix ();

  /***** getter and setter ****/
  int get_rows () const{ return _dims.rows; }
  int get_cols () const{ return _dims.cols; }

  /***** functions ****/
  Matrix &transpose ();
  Matrix &vectorize ();
  void plain_print () const;
  Matrix dot (const Matrix &m) const;
  float norm () const;

  /***** operators ****/
  Matrix operator+ (const Matrix &m) const;
  Matrix &operator= (Matrix m);
  Matrix operator* (const Matrix &m) const;
  Matrix operator* (float c) const;
  friend Matrix operator* (float c, const Matrix &m);
  Matrix &operator+= (const Matrix &m);
  float &operator() (int i, int j); //for non const object
  float &operator[] (int i); //for non const object
  const float &operator() (int i, int j) const; //for const object
  const float &operator[] (int i) const; //for const object
  friend std::ostream &operator<< (ostream &s, const Matrix &m);
  friend std::istream &operator>> (istream &s, Matrix &m);
};

#endif //MATRIX_H