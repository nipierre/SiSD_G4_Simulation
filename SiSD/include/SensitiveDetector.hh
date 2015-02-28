/*
  \file     SensitiveDetector.hh
  \brief    Give the possibility to record hits to logical volumes
*/
#ifndef SENSITIVEDETECTOR_HH_
#define SENSITIVEDETECTOR_HH_

#include "G4VSensitiveDetector.hh"
#include "SiHit.hh"

class DetectorConstruction;
class RunAction;
class G4HCofThisEvent;

/*!
* \class SensitiveDetector
* \brief Give the possibility to record hits to logical volumes
*/
class SensitiveDetector : public G4VSensitiveDetector
{
  public:
    /*!
    * \brief Constructor
    * \param SDname : name of the sensitive volume
    */
    SensitiveDetector(G4String SDname);
    /*!
    * \brief Destructor
    */
    ~SensitiveDetector();
    /*!
    * \brief Record hits, treat and store the infos
    */
    G4bool ProcessHits(G4Step *step, G4TouchableHistory *ROhist);
    
    void Initialize(G4HCofThisEvent* HCE);
    void EndOfEvent(G4HCofThisEvent* HCE);

  private:
      SiHitCollection* hitCollection;
};

#endif
