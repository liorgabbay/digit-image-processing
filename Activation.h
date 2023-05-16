#include "Matrix.h"

#ifndef ACTIVATION_H
#define ACTIVATION_H

/***************************/
/*         typedef         */
/***************************/
typedef Matrix (*Activation_function) (const Matrix &);
/***************************/

/***************************/
/*         define          */
/***************************/
#define WAS_NEGATIVE 0
#define SOFTMAX_SCALAR ((1)/(multiply_var))
/***************************/

/***************************/
/*       declarations      */
/***************************/
/**
 * sum the exp of the number in the matrix
 * @param m - input matrix
 * @return float sum
 */
float soft_max_helper (const Matrix &m);
/***************************/


/**
 * @namespace activation
 * @brief contain Activation func relu and softmax
 */
namespace activation
{
    /**
     * apply relu equation on matrix
     * @param m -input matrix
     * @return matrix - that is the answer of the relu equation
     */
    Matrix relu (const Matrix &m);

    /**
     * apply softmax equation on matrix
     * @param m
     * @return  matrix - that is the answer of the relu equation
     */
    Matrix softmax (const Matrix &m);
}
#endif //ACTIVATION_H

