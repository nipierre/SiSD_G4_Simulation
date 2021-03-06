/*
  \file     SiDigitizer.hh
  \brief    Convert hits to digits
*/
#ifndef SIDIGITIZER_HH_
#define SIDIGITIZER_HH_

#include "G4VDigitizerModule.hh"
#include "SiDigi.hh"
#include "NoiseGenerator.hh"
#include "CrosstalkGenerator.hh"
#include "SiDigitizerMessenger.hh"

/*!
* \class SiDigitizer
* \brief Convert hits to digits
*/
class SiDigitizer : public G4VDigitizerModule
{
  public:
    /*!
    * \brief Constructor
    * \param aName : name of the digitizer
    */
    SiDigitizer(G4String aName);
    /*!
    * \brief Destructor
    */
    virtual ~SiDigitizer() {};
    /*!
    * \brief Convert hits to digits
    */
    virtual void Digitize();

  protected:
    /*!
    * \brief Perform crosstalk over strip signals
    */
    virtual void MakeCrosstalk(std::vector< std::vector< SiDigi* > >& digitsMap);

  public:
    inline void SetPedestal( const G4double& aValue )          { noise = NoiseGenerator(aValue,noise.GetSigma()); }
    inline void SetNoise( const G4double& aValue )             { noise = NoiseGenerator(noise.GetPedestal(),aValue); }
    inline void SetCrosstalk( const G4double& aValue)          { crosstalk = CrosstalkGenerator(aValue,16); }
    inline void SetCollectionName( const G4String& aName )     { digiCollectionName = aName; }
    inline void SetHitsCollectionName( const G4String& aName ) { hitsCollName = aName; }

  private:
    G4String digiCollectionName;
    G4String hitsCollName;
    NoiseGenerator noise;
    CrosstalkGenerator crosstalk;
    SiDigitizerMessenger messenger;
};

#endif
