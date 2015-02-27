#include "CrosstalkGenerator.hh"

CrosstalkGenerator::CrosstalkGenerator(const double& xtalknear , const int& dim) :
        firstNearXtalk(xtalknear),
        dimension(dim),
        xtalk(1)
{
        Init();
}

void CrosstalkGenerator::Init()
{
        if ( firstNearXtalk == 0 )
          return;

        SymMatrix diag(1);
        diag *= (-2*firstNearXtalk );
        xtalk += diag;

        SymMatrix ofdiag(0);
        for ( int i = 0;i<dimension-1;++i)
          ofdiag.mat[i][i+1] = firstNearXtalk;

        xtalk += ofdiag;
}
