#include "RunAction.hh"
#include "PrimaryGeneratorAction.hh"
#include "Run.hh"

#include "G4Run.hh"
#include "G4RunManager.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"

RunAction::RunAction(EventAction* theEventAction ) :
        eventAction(theEventAction)
{
    eventAction->SetRootSaver( &saver );
}


RunAction::~RunAction()
{ }


G4Run* RunAction::GenerateRun()
{ return new Run; }


void RunAction::BeginOfRunAction(const G4Run* run)
{
  G4cout << "### Run " << run->GetRunID() << " start." << G4endl;

  G4RunManager::GetRunManager()->SetRandomNumberStore(false);

  //For each run a new TTree is created, with default names
  saver.CreateTree();
}


void RunAction::EndOfRunAction(const G4Run* run)
{
  G4int nofEvents = run->GetNumberOfEvent();
  if (nofEvents == 0) return;

  const PrimaryGeneratorAction* generatorAction = static_cast<const PrimaryGeneratorAction*>(

      G4RunManager::GetRunManager()->GetUserPrimaryGeneratorAction()
  );

  G4String partName;
  if (generatorAction) {

    G4ParticleDefinition* particle = generatorAction->GetParticleGun()->GetParticleDefinition();
    partName = particle->GetParticleName();
  }

  G4cout<<"Ending Run: "<<run->GetRunID()<<G4endl;
  G4cout<<"Number of events: "<<run->GetNumberOfEvent()<<G4endl;
  saver.CloseTree();
}
