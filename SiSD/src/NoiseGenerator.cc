#include "NoiseGenerator.hh"
#include <assert.h>
#include <algorithm>

NoiseGenerator::NoiseGenerator(const G4double& ppedestal, const G4double& psigma) :
  pedestal(ppedestal),
  sigma(psigma),
  randomGauss( *(CLHEP::HepRandom::getTheEngine()) , 0.0 , 1.0 )
{
}

NoiseGenerator::NoiseGenerator(const NoiseGenerator& rhs ) :
  pedestal(rhs.pedestal),
  sigma(rhs.sigma),
  randomGauss( *(CLHEP::HepRandom::getTheEngine()) , 0.0 , 1.0 )
{
}

G4double NoiseGenerator::operator()()
{
   if ( sigma > 0. )
     return (pedestal+randomGauss.fire( 0.0 , sigma ));
   else
     return 0.;
}
