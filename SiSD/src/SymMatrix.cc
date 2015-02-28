#include <string.h>
#include <vector>
#include <float.h>

#include "SymMatrix.hh"
#include "G4UImanager.hh"

// Constructors

SymMatrix::SymMatrix()
{
  for(int i=0; i<16; i++)
   for(int j=i; j<16; j++)
   {
     mat[i][j] = 0;
   }
}

SymMatrix::SymMatrix(int init)
{
  switch(init)
  {
  case 0:
  {
    for(int i=0; i<16; i++)
     for(int j=i; j<16; j++)
     {
       mat[i][j] = 0;
     }
  }
  break;

  case 1:
  {
    for(int i=0; i<16; i++)
     for(int j=i; j<16; j++)
     {
       if(i == j)
        mat[i][i] = 1;
       else
        mat[i][j] = 0;
     }
  break;
  }

  default:
    G4cout << "SymMatrix: initialization must be either 0 or 1." << G4endl;
  }
}

//
// Destructor
//
SymMatrix::~SymMatrix()
{

}

SymMatrix::SymMatrix(const SymMatrix &sm1)
{
  for(int i=0;i<16;i++)
  {
    for(int j=i;j<16;j++)
    {
      mat[i][j] += sm1.mat[i][j];
    }
  }
}

SymMatrix & SymMatrix::operator=(const SymMatrix &sm1)
{
  for(int i=0;i<16;i++)
  {
    for(int j=i;j<16;j++)
    {
      mat[i][j] += sm1.mat[i][j];
    }
  }
  return (*this);
}

SymMatrix & SymMatrix::operator+=(const SymMatrix &sm2)
{
  for(int i=0;i<16;i++)
  {
    for(int j=i;j<16;j++)
    {
      mat[i][j] += sm2.mat[i][j];
    }
  }
  return (*this);
}

SymMatrix & SymMatrix::operator*=(double t)
{
  for(int i=0;i<16;i++)
  {
    for(int j=i;j<16;j++)
    {
      mat[i][j] *= t;
    }
  }
  return (*this);
}

std::vector<double> operator*(const SymMatrix &sm1,const std::vector<double> &sm2)
{
  std::vector<double> mret;

  mret.assign(16,0);

  for(int i=0;i<16;i++)
  {
    for(int j=0;j<16;j++)
    {
      if(j<i)
      {
        mret[i] += sm1.mat[j][i]*sm2[j];
      }
      else
      {
        mret[i] += sm1.mat[i][j]*sm2[j];
      }
    }
  }

  return mret;
}
