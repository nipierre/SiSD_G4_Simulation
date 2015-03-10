#include "G4DigiManager.hh"
#include "SiDigitizer.hh"
#include "SiDigi.hh"
#include "NoiseGenerator.hh"
#include "CrosstalkGenerator.hh"
#include "SiHit.hh"
#include <assert.h>
#include <list>
#include <map>
#include "CLHEP/Units/SystemOfUnits.h"

using namespace CLHEP;

SiDigitizer::SiDigitizer(G4String aName) :
  G4VDigitizerModule(aName),
  digiCollectionName("SiDigitCollection"),
  hitsCollName("SiHitCollection"),
  noise(50.,10.),
  crosstalk(0.,16),
  messenger(this)
{
  collectionName.push_back( digiCollectionName );
}

void SiDigitizer::Digitize()
{

  SiDigiCollection * digiCollection = new SiDigiCollection("SiDigitizer",digiCollectionName);

  const G4int numPlanes = 1;  //Number of Si detectors
  const G4int numStrips = 16; //Number of strip per plane

  std::vector< std::vector<SiDigi*> > digitsMap(numPlanes);
  for ( G4int i = 0 ; i < numPlanes ; ++i )
  {
          digitsMap[i].resize(numStrips,static_cast<SiDigi*>(0));
  }

  for ( G4int plane = 0 ; plane < numPlanes ; ++plane ) {
    for ( G4int strip = 0 ; strip < numStrips ; ++strip )
      {
        SiDigi* newDigi = new SiDigi(plane,strip);
        digitsMap[plane][strip] = newDigi;
        digiCollection->insert(newDigi);
      }
  }

  // Transformation from hits to electronic signal
  G4DigiManager* digMan = G4DigiManager::GetDMpointer();
  G4int SiHitCollID = digMan->GetHitsCollectionID( hitsCollName );//Number associated to hits collection names hitsCollName
  const SiHitCollection* hitCollection = static_cast<const SiHitCollection*>(digMan->GetHitsCollection(SiHitCollID));

  if ( hitCollection )
    {
          for ( G4int i = 0 ; i < hitCollection->entries() ; ++i )
        {

          SiHit* aHit = (*hitCollection)[i];
          G4int hitPlane = aHit->GetPlaneNumber();
          G4int hitStrip = aHit->GetStripNumber();
          G4double edep = aHit->GetEdep();
          G4double charge = edep/(3.6*eV*MeV);

          digitsMap[hitPlane][hitStrip]->Add(charge);
        }
    }
  else
  {
    G4cerr<<"Could not found SiHit collection with name:"<<hitsCollName<<G4endl;
  }

  //Crosstalk
  MakeCrosstalk( digitsMap );

  //Noise
  for ( size_t d = 0 ; d < digiCollection->GetSize(); ++d )
  {
          SiDigi* digi = static_cast< SiDigi* >( digiCollection->GetDigi(d) );

          //Noise
          digi->Add( noise() );

	  //digi->Print();
  }

  StoreDigiCollection(digiCollection);
}

void SiDigitizer::MakeCrosstalk(std::vector< std::vector< SiDigi* > >& digitsMap )
{
        int plane = 0;
        std::vector< SiDigi* >& thisPlane = digitsMap[plane];
        size_t numStrips = thisPlane.size();
        size_t strip;
        std::vector<double> in;
        in.assign(numStrips,0);

        for ( strip = 0; strip<numStrips;++strip )
        {
          in[strip] = thisPlane[strip]->GetCharge();
        }

        std::vector<double> out = crosstalk( in );

        for ( strip=0; strip < numStrips ; ++strip )
        {
          thisPlane[strip]->SetCharge( out[strip] );
        }
}
