#include "Matrix.h"

/**
 * delete the matrix arrays
 */
void Matrix::delete_matrix ()
{
  for (int i = 0; i < _dims.rows; i++)
  {
    delete[]_matrix[i]; //delete each col
  }
  delete[] _matrix; //delete the matrix
}

/**
 * create the cols arrays
 */
void Matrix::create_inside_arrays ()
{
  for (int i = 0; i < _dims.rows; i++)
  {
    _matrix[i] = new float[_dims.cols];
  }
}

/**
 * construct matrix object
 * @param rows - num of rows
 * @param cols - num of cols
 */
Matrix::Matrix (int rows, int cols) :
    _matrix (nullptr) //initialization row
{
  if (rows < ONE_VECTOR || cols < ONE_VECTOR)
  {
    throw (std::length_error (LENGTH_ERROR));
  }
  _matrix = new float *[rows];
  _dims.rows = rows;
  _dims.cols = cols;
  create_inside_arrays (); //initialize the cols
  for (int i = 0; i < _dims.rows; i++)
  {
    for (int j = 0; j < _dims.cols; j++)
    {
      _matrix[i][j] = START; //by default is zero
    }
  }
}
/**
 * copy constructor
 * @param m - matrix that we coping
 */
Matrix::Matrix (const Matrix &m) :
    Matrix (m._dims.rows, m._dims.cols) //initialization row
{
  for (int i = 0; i < _dims.rows; i++)
  {
    for (int j = 0; j < _dims.cols; j++)
    {
      _matrix[i][j] = m._matrix[i][j]; //deep copy
    }
  }
}

/**
 * destructor for matrix object
 */
Matrix::~Matrix ()
{
  delete_matrix (); //delete the matrix
}

/**
 * transpose the matrix
 * @return - reference for matrix - that was transpose
 */
Matrix &Matrix::transpose ()
{
  Matrix temp = *this; //save the original matrix - by deep copy
  delete_matrix (); //delete the matrix
  int cur_rows = _dims.rows;
  _dims.rows = _dims.cols;
  _dims.cols = cur_rows; //changing dimensions
  _matrix = new float *[_dims.rows]; //create new_matrix
  create_inside_arrays ();
  for (int i = 0; i < _dims.rows; i++)
  {
    for (int j = 0; j < _dims.cols; j++)
    {
      _matrix[i][j] = (temp._matrix)[j][i];
    }
  }
  return *this;
}

/**
 * converting a matrix to a vector
 * @return - reference for matrix - that was convert to vector
 */
Matrix &Matrix::vectorize ()
{
  Matrix temp = *this;
  delete_matrix ();
  int cur_cols = _dims.cols;
  _dims.cols = ONE_VECTOR;
  _dims.rows *= cur_cols;
  _matrix = new float *[_dims.rows]; //create new matrix with the new dims
  create_inside_arrays ();
  int row_size = temp._dims.cols;
  for (int i = 0; i < temp._dims.rows; i++)
  {
    for (int j = 0; j < temp._dims.cols; j++)
    {
      _matrix[i * row_size + j][FIRST] = (temp._matrix)[i][j]; //move coords
    }
  }
  return *this;
}

/**
 * print the matrix
 */
void Matrix::plain_print () const
{
  for (int i = 0; i < _dims.rows; i++)
  {
    for (int j = 0; j < _dims.cols; j++)
    {
      if (j == LAST_ONE)
      {
        std::cout << _matrix[i][j] << std::endl; //print the last one
      }
      else
      {
        std::cout << _matrix[i][j] << SPACE;
      }
    }
  }
}

/**
 * multiply the matrix with anther one by coordinates
 * @param m - right matrix
 * @return the result of the multiply
 */
Matrix Matrix::dot (const Matrix &m) const
{
  if ((this->_dims.rows != m._dims.rows) ||
      this->_dims.cols != m._dims.cols) // in case the two matrix dims diff
  {
    throw (std::length_error (LENGTH_ERROR));
  }

  Matrix result (m._dims.rows, m._dims.cols); //create the result
  for (int i = 0; i < m._dims.rows; i++)
  {
    for (int j = 0; j < m._dims.cols; j++)
    {//multiply matrix by coords
      result._matrix[i][j] = (this->_matrix)[i][j] * (m._matrix)[i][j];
    }
  }
  return result;
}

/**
 * get the norm of the matrix
 * @return the norm of the vector
 */
float Matrix::norm () const
{
  float sum = START;
  for (int i = 0; i < _dims.rows; i++)
  {
    for (int j = 0; j < _dims.cols; j++)
    {//sum the power by 2 for every coord
      sum += (float) std::pow (this->_matrix[i][j], POW_BASE);
    }
  }
  return (float) std::sqrt (sum); //return the sqrt of the sum
}

/**
 * add one matrix to anther one matrix
 * @param m -  matrix to sum with
 * @return result matrix
 */
Matrix Matrix::operator+ (const Matrix &m) const
{
  if ((this->_dims.rows != m._dims.rows) ||
      this->_dims.cols != m._dims.cols)
  {
    throw (std::length_error (LENGTH_ERROR));
  }
  Matrix result (_dims.rows, _dims.cols);
  for (int i = 0; i < _dims.rows; i++)
  {
    for (int j = 0; j < _dims.cols; j++)
    { // create the result matrix by connect every two coords
      result._matrix[i][j] = (this->_matrix)[i][j] + (m._matrix)[i][j];
    }
  }
  return result;
}

//swap func - use in assigment func
/**
 * swap between two datas of matrix
 * @param lhs - left matrix
 * @param rhs - right matrix
 */
void swap (Matrix &lhs, Matrix &rhs)
{
  std::swap (lhs._dims, rhs._dims);
  std::swap (lhs._matrix, rhs._matrix);
}
//assigment func by swap func
/**
 * copy assigment func by swap
 * @param m - matrix to copy
 * @return matrix - the copy of the matrix
 */
Matrix &Matrix::operator= (Matrix m)
{
  swap (*this, m);
  return *this;
}

/**
 * find the coords of multiply matrix by matrix
 * @param rhs - right matrix in multiply
 * @param i - coord
 * @param j  - coord
 * @return the result for coord i,j
 */
float Matrix::find_index_sum (const Matrix &rhs, int i, int j) const
{
  float sum = START;
  for (int k = 0; k < rhs._dims.rows; k++)
  {
    sum += this->_matrix[i][k] * rhs._matrix[k][j];
  }
  return sum;
}

/**
 * multiply between two matrix
 * @param m - right matrix
 * @return result of the multiply
 */
Matrix Matrix::operator* (const Matrix &m) const
{
  if (_dims.cols != m._dims.rows) //in case the length of the matrix invalid
  {
    throw (std::length_error (LENGTH_ERROR));
  }
  Matrix result (_dims.rows, m._dims.cols);
  for (int i = 0; i < result._dims.rows; i++)
  {
    for (int j = 0; j < result._dims.cols; j++)
    {
      result._matrix[i][j] = find_index_sum (m, i, j);
    }
  }
  return result;
}

/**
 * multiply matrix by scalar from the right
 * @param c - scalar for multiply
 * @return result matrix
 */
Matrix Matrix::operator* (float c) const
{
  Matrix result = *this; //create the result matrix
  for (int i = 0; i < result._dims.rows; i++)
  {
    for (int j = 0; j < result._dims.cols; j++)
    {
      result._matrix[i][j] *= c; //multiply every coords by the scalar
    }
  }
  return result;
}

/**
 * multiply matrix by scalar from the left
 * @param c - scalar for multiply
 * @return result matrix
 */
Matrix operator* (float c, const Matrix &m)
{
  Matrix result = m * c; //using the right multiply
  return result;
}

/**
 * add matrix to anther one
 * @param m - matrix to add
 * @return matrix reference to the added one
 */
Matrix &Matrix::operator+= (const Matrix &m)
{
  if ((this->_dims.rows != m._dims.rows) ||
      this->_dims.cols != m._dims.cols) //check if the dims are valid
  {
    throw (std::length_error (LENGTH_ERROR));
  }
  for (int i = 0; i < this->_dims.rows; i++)
  {
    for (int j = 0; j < this->_dims.cols; j++)
    {
      this->_matrix[i][j] += m._matrix[i][j];
    }
  }
  return *this;
}

/**
 * operator() - get the value in (i,j) coord , non const func
 * @param i - row num
 * @param j -col num
 * @return - return the value in i,j coord
 */
float &Matrix::operator() (int i, int j)
{
  if (i >= _dims.rows || i < START || j >= _dims.cols || j < START)
  {
    throw (std::out_of_range (OUT_OF_RANGE_ERROR));
  }
  return (this->_matrix)[i][j];
}

/** operator[] non const
 * @param i - coord
 * @return the matrix in the i coord
 */
float &Matrix::operator[] (int i)
{
  if (i >= (this->_dims.cols * this->_dims.rows) || i < START)
  {
    throw (std::out_of_range (OUT_OF_RANGE_ERROR));
  }
  int col = (i % (this->_dims.cols)); //find the col
  int row = (i - col) / (this->_dims.cols); //find the row
  return this->_matrix[row][col];
}

/**
 * operator() - get the value in (i,j) coord , const func
 * @param i - row num
 * @param j -col num
 * @return - return the value in i,j coord
 */
const float &Matrix::operator() (int i, int j) const
{
  if (i >= _dims.rows || i < START || j >= _dims.cols || j < START)
  {
    throw (std::out_of_range (OUT_OF_RANGE_ERROR));
  }
  return (this->_matrix)[i][j];
}

/** operator[] const
 * @param i - coord
 * @return the matrix in the i coord
 */
const float &Matrix::operator[] (int i) const
{
  if (i >= (this->_dims.cols * this->_dims.rows) || i < START)
  {
    throw (std::out_of_range (OUT_OF_RANGE_ERROR));
  }
  int col = (i % (this->_dims.cols)); //find the col
  int row = (i - col) / (this->_dims.cols); //find the row
  return this->_matrix[row][col];
}

/**
 * @param s - stream for output
 * @param m - matrix to print
 * @return output stream
 */
std::ostream &operator<< (ostream &s, const Matrix &m)
{
  for (int i = 0; i < m.get_rows (); i++)
  {
    for (int j = 0; j < m.get_cols (); j++)
    {
      if (m (i, j) > TWO_ASTERISKS)
      {
        s << "**";
      }
      else
      {
        s << "  ";
      }
    }
    s << "\n";
  }
  return s;
}

/**
 * fill the matrix with the value in the stream
 * @param s - input stream
 * @param m - matrix to fill
 * @return input stream
 */
std::istream &operator>> (istream &s, Matrix &m)
{
  auto mat_size_by_bytes = (long) (m.get_cols () * m.get_rows ()
                                   * sizeof (float));
  s.seekg (START, std::ios_base::end);
  long int stream_size_bytes = s.tellg (); //check stream range
  if (stream_size_bytes != mat_size_by_bytes)
  {
    throw (std::runtime_error (RUNTIME_ERROR));
  }
  s.seekg (START, std::ios_base::beg);
  for (int i = 0; i < m._dims.rows; i++)
  {
    if(!s.read ((char *) m._matrix[i],
            (m._dims.cols) * (int) sizeof (float)))
    {
      throw (std::runtime_error (RUNTIME_ERROR));
    }
  }
  return s;
}


