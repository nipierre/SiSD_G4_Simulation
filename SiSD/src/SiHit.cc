#include "SiHit.hh"
#include "CLHEP/Units/SystemOfUnits.h"

using namespace CLHEP;

G4Allocator<SiHit> SiHitAllocator;

SiHit::SiHit(const G4int strip, const G4int plane, const G4bool primary ) :
    stripNumber(strip),
    planeNumber(plane),
    isPrimary(primary)
{
  eDep = 0.0;
}

SiHit::~SiHit()
{

}

void SiHit::Print()
{
  //Debug
  //G4cout<<"Hit: Plane= "<<planeNumber<<" Strip= "<<stripNumber<<" E= "<<eDep/keV<<" keV isPrimary="<<(isPrimary?"true":"false")<<G4endl;
}
