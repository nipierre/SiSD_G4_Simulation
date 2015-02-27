#ifndef _SYMMatrix_HH_
#define _SYMMatrix_HH_

#include <vector>

class SymMatrix {

public:

  SymMatrix();
  SymMatrix(int init);

  virtual ~SymMatrix();

  SymMatrix(const SymMatrix &sm1);

  SymMatrix & operator=(const SymMatrix &sm1);

  SymMatrix & operator*=(double t);

  SymMatrix & operator+=( const SymMatrix &sm2);

  //In public to avoid hazard of const [] operators that cause a mess with tables
  double mat[16][16];
};

std::vector<double> operator*(const SymMatrix &sm1, const std::vector<double> &sm2);

#endif
