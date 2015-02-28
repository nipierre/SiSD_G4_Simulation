/*
  \file     SymMatrix.hh
  \brief    Construct symmetric matrices
*/
#ifndef _SYMMATRIX_HH_
#define _SYMMATRIX_HH_

#include <vector>

/*!
* \class SymMatrix
* \brief Construct symmetric matrices
*/
class SymMatrix
{
  public:
    /*!
    * \brief Constructor
    */
    SymMatrix();
    /*!
    * \brief Constructor
    * \param init : if 1, diagonal matrix
    */
    SymMatrix(int init);
    /*!
    * \brief Destructor
    */
    virtual ~SymMatrix();

    SymMatrix(const SymMatrix &sm1);

    SymMatrix & operator=(const SymMatrix &sm1);

    SymMatrix & operator*=(double t);

    SymMatrix & operator+=( const SymMatrix &sm2);

    double mat[16][16]; /*!< In public to avoid hazard of const [] operators
                             that cause a mess with tables */
};

std::vector<double> operator*(const SymMatrix &sm1, const std::vector<double> &sm2);

#endif
