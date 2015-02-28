/*
  \file     CrosstalkGenerator.hh
  \brief    Simulation of crosstalk between strips
*/

#ifndef CROSSTALKGENERATOR_HH_
#define CROSSTALKGENERATOR_HH_

#include <vector>
#include "SymMatrix.hh"

/*!
* \class CrosstalkGenerator
* \brief Simulates the crosstalk between neighbour strips.
* For a strip i the charge Q is modified to be:
* Q'(i) = (1-2*f)*Q(i) + f*Q(i+1) + f*Q(i-1),
* where f is the crosstalk factor
*/
class CrosstalkGenerator
{
  public:
    /*!
    * \brief Constructor
    */
    CrosstalkGenerator(const double& xtalknear , const int& dimension);

    /*!
    * \brief Destructor
    */
    virtual ~CrosstalkGenerator() {};

    /*!
    * \brief Operator ()
    * \param input : vector of strips to apply crosstalk on
    * \return crosstalked vector of strips
    */
    virtual std::vector<double> operator()(const std::vector<double>& input ) { return xtalk*input; }

  private:
    /*!
    * \brief Initialize the crosstalk matrix
    */
    virtual void Init();

  private:
    double firstNearXtalk; /*!< Crosstalk factor*/
    int dimension; /*!< Dimension of the crosstalk matrix (n is the dimension of nxn matrix)*/
    SymMatrix xtalk; /*!< Crosstalk matrix*/
};

 #endif
