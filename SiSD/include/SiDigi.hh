/*
  \file     SiDigi.hh
  \brief    Store the digits obtained from the hits
*/
#ifndef SIDIGI_HH_
#define SIDIGI_HH_

#include "G4VDigi.hh"
#include "G4TDigiCollection.hh"
#include "G4Allocator.hh"

/*!
* \class SiDigi
* \brief Store the digits obtained from the hits
*/
class SiDigi : public G4VDigi
{
  public:
    /*!
    * \brief Constructor
    * \param planeNum : Id of the sensor
    * \param stripNum : Id of the strip
    */
    SiDigi(const int& planeNum , const int& stripNum);
    /*!
    * \brief Destructor
    */
    virtual ~SiDigi() {}
    /*!
    * \brief Add a charge
    */
    inline void Add( const G4double& aValue ) { charge+= aValue; }
    /*!
    * \brief Print info of the current Digit
    */
    void Print();

    inline void     SetPlaneNumber( const G4int& aPlane ) { planeNumber = aPlane; }
    inline G4int    GetPlaneNumber( ) const { return planeNumber; }
    inline void     SetStripNumber( const G4int& aStrip) { stripNumber = aStrip; }
    inline G4int    GetStripNumber( ) const { return stripNumber; }
    inline void     SetCharge( const double& aCharge ) { charge = aCharge; }
    inline G4double GetCharge( ) const { return charge; }

    inline G4int operator==(const SiDigi& aDigi) const
    { return ( ( planeNumber == aDigi.GetPlaneNumber() ) && ( stripNumber == aDigi.GetStripNumber() ) ); }

    inline void* operator new(size_t);
    inline void  operator delete(void* aDigi);


  private:
    G4double charge;
    G4int stripNumber;
    G4int planeNumber;
};

typedef G4TDigiCollection<SiDigi> SiDigiCollection;

extern G4Allocator<SiDigi> SiDigiAllocator;

// Allocation to avoid any compilation hazards
void* SiDigi::operator new(size_t)
{
  return static_cast<void*>( SiDigiAllocator.MallocSingle() );
}

void SiDigi::operator delete(void* aDigi)
{
  SiDigiAllocator.FreeSingle( static_cast<SiDigi*>(aDigi) );
}

#endif
