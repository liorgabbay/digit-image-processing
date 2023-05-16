//MlpNetwork.h

#ifndef MLPNETWORK_H
#define MLPNETWORK_H
/***************************/
/*         include         */
/***************************/
#include "Dense.h"
/***************************/

/***************************/
/*         define          */
/***************************/
#define MLP_SIZE 4
#define FIRST_PLACE 0
#define SEC_PLACE 1
#define THIRD_PLACE 2
#define FOURTH_PLACE 3
/***************************/

/***************************/
/*         using          */
/***************************/
using activation::relu;
using activation::softmax;
/***************************/


/**
 * @struct digit
 * @brief Identified (by Mlp network) digit with
 *        the associated probability.
 * @var value - Identified digit value
 * @var probability - identification probability
 */
typedef struct digit
{
    unsigned int value;
    float probability;
} digit;

const matrix_dims img_dims = {28, 28};
const matrix_dims weights_dims[] = {{128, 784},
                                    {64,  128},
                                    {20,  64},
                                    {10,  20}};
const matrix_dims bias_dims[] = {{128, 1},
                                 {64,  1},
                                 {20,  1},
                                 {10,  1}};

/**
 * @class MlpNetwork
 * @brief contain 4 dense object for every layer,
 * include functions and operators for MlpNetwork.
 */

class MlpNetwork
{
 private:
  /***** private members ****/
  Dense _dense_1; //layer 1
  Dense _dense_2; //layer 2
  Dense _dense_3; //layer 3
  Dense _dense_4; //layer 4
  /***** private functions ****/
  /**
   * find the index that has the max probability
   * @param m -current matrix
   * @param num - the number of the index with the max probability
   * @return the probability of num
   */
  float find_prob_and_value (Matrix &m, unsigned int *num);

 public:

  /************** constructors ***************/
  /**
   * construct MlpNetwork
   * @param weights - array of weights matrix
   * @param biases  - array of bias matrix
   */
  MlpNetwork (Matrix weights[MLP_SIZE], Matrix biases[MLP_SIZE]);

  /*************** functions ****************/
  /**
   * find the number with the max probability
   * @param x - input matrix
   * @return digit with num and his probability
   */
  digit operator() (const Matrix &x);
};

#endif // MLPNETWORK_H