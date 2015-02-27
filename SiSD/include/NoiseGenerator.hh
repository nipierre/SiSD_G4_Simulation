
#ifndef NOISEGENERATOR_HH_
#define NOISEGENERATOR_HH_


#include "G4Types.hh"
#include "Randomize.hh"

class NoiseGenerator
{
public:
  NoiseGenerator(const G4double& ppedestal, const G4double& psigma);
  virtual ~NoiseGenerator() {};
  virtual G4double operator() ();

  inline NoiseGenerator& operator= (const NoiseGenerator& rhs)
  {
        pedestal = rhs.pedestal;
        sigma = rhs.sigma;
        return *this;
  }

  NoiseGenerator(const NoiseGenerator& rhs);

  G4double GetPedestal() {return pedestal;}
  G4double GetSigma() {return sigma;}

private:
  G4double pedestal;
  G4double sigma;
  G4RandGauss randomGauss;
};

#endif
