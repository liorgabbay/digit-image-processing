#include "MlpNetwork.h"

// See full documentation in header file
MlpNetwork::MlpNetwork (Matrix *weights, Matrix *biases) //init row
    : _dense_1 (weights[FIRST_PLACE], biases[FIRST_PLACE], relu),
      _dense_2 (weights[SEC_PLACE], biases[SEC_PLACE], relu),
      _dense_3 (weights[THIRD_PLACE], biases[THIRD_PLACE], relu),
      _dense_4 (weights[FOURTH_PLACE], biases[FOURTH_PLACE], softmax)
{
}

// See full documentation in header file
float MlpNetwork::find_prob_and_value (Matrix &m, unsigned int *num)
{
  float max_prob = FIRST;
  for (int i = 0; i < m.get_rows (); i++)
  {
    for (int j = 0; j < m.get_cols (); j++)
    {
      if (m (i, j) > max_prob)
      {
        max_prob = m (i, j);
        *num = ((i * m.get_cols ()) + j); //the number that has the max prob
      }
    }
  }
  return max_prob;
}

// See full documentation in header file
digit MlpNetwork::operator() (const Matrix &x)
{
  Matrix r1 = _dense_1 (x); //apply activation func on x
  Matrix r2 = _dense_2 (r1);//apply activation func on r1
  Matrix r3 = _dense_3 (r2);//apply activation func on r2
  Matrix r4 = _dense_4 (r3);//apply activation func on r3
  unsigned int num = START;
  float prob = find_prob_and_value (r4, &num); //find the num and prob
  digit final = {num, prob}; //save the number and prob
  return final;
}






