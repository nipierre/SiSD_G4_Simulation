#ifndef CROSSTALKGENERATOR_HH_
#define CROSSTALKGENERATOR_HH_

 #include <vector>
 #include "SymMatrix.hh"

 /*! \brief Crosstalk generator
  *
  * This class simulates the crosstalk between strips.
  * In the default implementation the crosstalks is applied in first neighbour
  * apporximation.
  * For a strip i the charge is modified to be:
  * Q'(i) = (1-2*f)*Q(i) + f*Q(i+1) + f*Q(i-1)
  */
class CrosstalkGenerator
{
  public:
    CrosstalkGenerator(const double& xtalknear , const int& dimension);

    virtual ~CrosstalkGenerator() {};

    virtual std::vector<double> operator()(const std::vector<double>& input ) { return xtalk*input; }

  private:
    virtual void Init();

  private:
    double firstNearXtalk;
    int dimension;
    SymMatrix xtalk;
};

 #endif
