#include "Run.hh"

#include "G4RunManager.hh"
#include "G4Event.hh"

#include "G4SDManager.hh"
#include "G4HCofThisEvent.hh"
#include "G4THitsMap.hh"
#include "G4SystemOfUnits.hh"


Run::Run()
: G4Run()
{ }



Run::~Run()
{ }


void Run::RecordEvent(const G4Event* event)
{
  G4HCofThisEvent* HCEvent = event->GetHCofThisEvent();
  if(!HCEvent) return;

  G4Run::RecordEvent(event);
}
