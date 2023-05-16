#include "Dense.h"

// See full documentation in header file
Dense::Dense
    (const Matrix &weights, const Matrix &bias, Activation_function func)
    : _weights (weights), _bias (bias), _activate_func (func) //init row
{
}
// See full documentation in header file
Matrix Dense::operator() (const Matrix &x) const
{
  return _activate_func ((_weights * x) + _bias); //using the equation
}

