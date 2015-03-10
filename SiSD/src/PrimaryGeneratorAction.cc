#include "PrimaryGeneratorAction.hh"
#include "G4RunManager.hh"
#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"
#include "time.h"


#include <fstream>
using namespace std;

PrimaryGeneratorAction::PrimaryGeneratorAction()
 : G4VUserPrimaryGeneratorAction(),
   fParticleGun(0)
{
  G4int n_particle = 1;
  fParticleGun  = new G4ParticleGun(n_particle);

  G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();

  G4String particleName;
  G4ParticleDefinition* particle = particleTable->FindParticle(particleName="proton");
  fParticleGun->SetParticleDefinition(particle);

  fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0, 0, 1));


  /*  ofstream  inputParticles("../input.txt", ios::out);
              inputParticles  << "Particle"
                              << "\t" << "Time"
                              << "\tX (mm)"
                              << "\tY (mm)"
                              << "\tZ (mm)"
                              << "\tE (keV)"
                              << endl;

              inputParticles.close();*/

}

PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
  delete fParticleGun;
}

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{

  G4double x = CLHEP::RandGauss::shoot(new CLHEP::RanecuEngine(), 0, 400*um);
  G4double y = CLHEP::RandGauss::shoot(new CLHEP::RanecuEngine(), 0, 400*um);
  G4double E = 2*MeV+CLHEP::RandGauss::shoot(new CLHEP::RanecuEngine(), 0, 6*keV);
  /*ofstream  inputParticles("../input.txt", ios::out | ios::app);
            inputParticles  << fParticleGun->GetParticleDefinition()->GetParticleName()
                            << "\t" << fParticleGun->GetParticleTime()
                            << "\t" << x
                            << "\t" << y
                            << "\t" << 0
                            << "\t" << E
                            << endl;

            inputParticles.close();*/

  fParticleGun->SetParticleEnergy(E);
  fParticleGun->SetParticlePosition(G4ThreeVector(x,y,0));
  fParticleGun->GeneratePrimaryVertex(anEvent);
}
