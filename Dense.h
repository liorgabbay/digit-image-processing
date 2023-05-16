#ifndef DENSE_H
#define DENSE_H

#include "Activation.h"

/**
 * @class Dense
 * @brief contain weight,bias matrix and activation func,
 * include functions and operators for Dense.
 */

class Dense
{
 private:
  /***** private members ****/
  Matrix _weights; //the weight matrix for the layer
  Matrix _bias; //the bias matrix for the layer
  Activation_function _activate_func; //activation func for the layer

 public:
  /************ constructors ************/

  /**
   * constructor to dense
   * @param weights - weights matrix
   * @param bias - bias matrix
   * @param func - activation func
   */
  Dense (const Matrix &weights, const Matrix &bias, Activation_function func);

  /********** getter and setter *********/

  /**
   *get the bias matrix
   * @return bias matrix
   */
  Matrix get_bias () const{ return _bias; }

  /**
   *get the weights matrix
   * @return weights matrix
   */
  Matrix get_weights () const{ return _weights; }

  /**
   *get activation func
   * @return activation function
   */
  Activation_function get_activation () const{ return _activate_func; }

  /************* operators ************/

  /**
   *apply the input activation func on the equation
   * @param x the matrix input for the equation
   * @return result matrix
   */
  Matrix operator() (const Matrix &x) const;
};
#endif //DENSE_H
