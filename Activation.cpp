#include "Activation.h"

// See full documentation in header file
Matrix activation::relu (const Matrix &m)
{
  Matrix result (m); //create result matrix by deep copy
  for (int i = 0; i < result.get_rows (); i++)
  {
    for (int j = 0; j < result.get_cols (); j++)
    {
      if (result (i, j) < 0) //if the mat[coord] < 0
      {
        result (i, j) = WAS_NEGATIVE;
      }
    }
  }
  return result;
}

// See full documentation in header file
float soft_max_helper (const Matrix &m)
{
  float sum = START;
  for (int i = 0; i < m.get_rows (); i++)
  {
    for (int j = 0; j < m.get_cols (); j++)
    {
      sum += std::exp (m (i, j)); //sum the exp of the matrix
    }
  }
  return sum;
}

// See full documentation in header file
Matrix activation::softmax (const Matrix &m)
{
  Matrix result (m.get_rows (), m.get_cols ()); //create the result mat
  float multiply_var = soft_max_helper (m); //get the sum for equation
  for (int i = 0; i < result.get_rows (); i++)
  {
    for (int j = 0; j < result.get_cols (); j++)
    {
      result (i, j) = std::exp (m (i, j)); // change every coord by exp
      result (i, j) *= SOFTMAX_SCALAR; //multiply every cord
    }
  }
  return result;
}



