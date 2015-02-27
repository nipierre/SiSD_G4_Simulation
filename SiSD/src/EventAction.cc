#include "EventAction.hh"

#include "globals.hh"
#include "G4Event.hh"
#include "G4EventManager.hh"
#include "G4TrajectoryContainer.hh"
#include "G4Trajectory.hh"
#include "G4ios.hh"
#include "G4SDManager.hh"
#include "SiHit.hh"
#include "G4HCofThisEvent.hh"
#include "SiDigi.hh"
#include "SiDigitizer.hh"
#include "G4DigiManager.hh"

EventAction::EventAction() :
    rootSaver(0),
    hitsCollName("SiHitCollection"),
    digitsCollName("SiDigitCollection"),
    hitsCollID(-1)
{
  SiDigitizer* digitizer = new SiDigitizer("SiDigitizer");
  G4DigiManager * digiManager = G4DigiManager::GetDMpointer();
  digiManager->AddNewModule( digitizer );
}

EventAction::~EventAction(){}

void EventAction::BeginOfEventAction(const G4Event* anEvent)
{
  if ( anEvent->GetEventID() % 1000 == 0 )
         {
                 G4cout<<"Starting Event: "<<anEvent->GetEventID()<<G4endl;
         }
         if ( hitsCollID == -1 )
         {
                 G4SDManager * SDman = G4SDManager::GetSDMpointer();
                 hitsCollID = SDman->GetCollectionID(hitsCollName);
         }
}

void EventAction::EndOfEventAction(const G4Event* anEvent)
{
  //Digitizer
  G4DigiManager * digiManager = G4DigiManager::GetDMpointer();
  SiDigitizer* digiModule = static_cast<SiDigitizer*>( digiManager->FindDigitizerModule("SiDigitizer") );
  if ( digiModule )
  {
         digiModule->Digitize();
  }

  //Root Saver
  if ( rootSaver )
  {
         G4int digiCollID = digiManager->GetDigiCollectionID( digitsCollName );
         const SiDigiCollection* digits = static_cast<const SiDigiCollection*>( digiManager->GetDigiCollection(digiCollID) );

         G4HCofThisEvent* hitsCollections = anEvent->GetHCofThisEvent();
         SiHitCollection* hits = 0;
         if ( hitsCollections )
         {
                 hits = static_cast<SiHitCollection*>( hitsCollections->GetHC(hitsCollID) );
         }

         rootSaver->AddEvent(hits,digits);
  }
}
