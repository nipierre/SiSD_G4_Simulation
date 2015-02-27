#include "SensitiveDetector.hh"

#include "G4Step.hh"
#include "Randomize.hh"
#include "G4HCofThisEvent.hh"
#include "G4HCtable.hh"
#include "G4SDManager.hh"


SensitiveDetector::SensitiveDetector(G4String SDname) :
  G4VSensitiveDetector(SDname)
{
  collectionName.insert("SiHitCollection");
}

SensitiveDetector::~SensitiveDetector()
{

}

G4bool SensitiveDetector::ProcessHits(G4Step *step, G4TouchableHistory *)
{
  G4TouchableHandle touchable = step->GetPreStepPoint()->GetTouchableHandle();
  G4double edep = step->GetTotalEnergyDeposit();
  G4bool isPrimary = ( step->GetTrack()->GetTrackID() == 1 && step->GetTrack()->GetParentID() == 0 ) ? true : false;

  if (edep <= 0.) return false;

  //Coordinates
  G4ThreeVector point1 = step->GetPreStepPoint()->GetPosition();
  G4ThreeVector point2 = step->GetPostStepPoint()->GetPosition();

  //Tricking into having some 'random' point of interaction btwn the two
  G4ThreeVector pointE = point1 + G4UniformRand()*(point2 - point1);

  G4int stripCopyNo = touchable->GetReplicaNumber(1);
  G4int planeCopyNo = touchable->GetReplicaNumber();

  SiHit* hit = new SiHit(stripCopyNo,planeCopyNo,isPrimary);
  hitCollection->insert(hit);

  hit->AddEdep(edep);
  hit->SetPosition(pointE);

  return true;
}

void SensitiveDetector::Initialize(G4HCofThisEvent* HCEvent)
{
  hitCollection = new SiHitCollection(GetName(), collectionName[0]);

  static G4int HCID = -1;
  if (HCID<0) HCID = GetCollectionID(0);
  HCEvent->AddHitsCollection(HCID, hitCollection);
}

void SensitiveDetector::EndOfEvent(G4HCofThisEvent*)
{
  for (size_t i = 0; i < hitCollection->GetSize(); ++i )
  {
       (*hitCollection)[i]->Print();
  }
}
