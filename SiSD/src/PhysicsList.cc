#include "globals.hh"
#include "PhysicsList.hh"

#include "G4PhysicsListHelper.hh"
#include "G4ProcessManager.hh"
#include "G4ParticleTypes.hh"
#include "G4SystemOfUnits.hh"

#include "G4ComptonScattering.hh"
#include "G4GammaConversion.hh"
#include "G4PhotoElectricEffect.hh"

#include "G4eMultipleScattering.hh"
#include "G4eIonisation.hh"
#include "G4eBremsstrahlung.hh"
#include "G4eplusAnnihilation.hh"

#include "G4hMultipleScattering.hh"
#include "G4hIonisation.hh"
#include "G4hBremsstrahlung.hh"
#include "G4hPairProduction.hh"

#include "G4ionIonisation.hh"
#include "G4StepLimiter.hh"
#include "G4UserSpecialCuts.hh"

#include "G4CoulombScattering.hh"
#include "G4eCoulombScatteringModel.hh"
#include "G4WentzelVIModel.hh"

#include "G4EmProcessOptions.hh"
#include "G4NuclearStopping.hh"

PhysicsList::PhysicsList():  G4VUserPhysicsList()
{
  fCutsTable =  G4ProductionCutsTable::GetProductionCutsTable();
  //fCutsTable->SetEnergyRange(16*eV, 2*MeV);

  defaultCutValue = 100*nm;
}

PhysicsList::~PhysicsList() {}

void PhysicsList::ConstructParticle()
{
  G4Gamma::GammaDefinition();
  G4Electron::ElectronDefinition();
  G4Positron::PositronDefinition();
  G4Proton::ProtonDefinition();
  G4Alpha::AlphaDefinition();
  G4GenericIon::GenericIonDefinition();
}

void PhysicsList::ConstructProcess()
{
  AddTransportation();

  theParticleIterator->reset();

  while( (*theParticleIterator)() ){

    G4ParticleDefinition* particle = theParticleIterator->value();
    G4ProcessManager* pm = particle->GetProcessManager();
    G4String particleName = particle->GetParticleName();

    if (particleName == "gamma") {
      // gamma
      pm->AddDiscreteProcess(new G4PhotoElectricEffect);
      pm->AddDiscreteProcess(new G4ComptonScattering);
      pm->AddDiscreteProcess(new G4GammaConversion);

    } else if( particleName == "proton") {
      pm->AddProcess(new G4CoulombScattering,   -1,-1,4);
      pm->AddProcess(new G4hMultipleScattering, -1,1,1);
      pm->AddProcess(new G4NuclearStopping());
      pm->AddProcess(new G4hIonisation,         -1,2,2);
      pm->AddProcess(new G4hBremsstrahlung,     -1,3,3);
      pm->AddProcess(new G4hPairProduction,     -1,4,4);

    } else if (particleName == "e-") {
      //electron
      pm->AddDiscreteProcess(new G4CoulombScattering());
      pm->AddProcess(new G4eIonisation,         -1,2,2);
      pm->AddProcess(new G4eMultipleScattering, -1,1,1);
      pm->AddProcess(new G4eBremsstrahlung,     -1,3,3);

    } else if (particleName == "e+") {
      //positron
      pm->AddProcess(new G4eMultipleScattering, -1,1,1);
      pm->AddProcess(new G4eIonisation,         -1,2,2);
      pm->AddProcess(new G4eBremsstrahlung,     -1,3,3);
      pm->AddProcess(new G4eplusAnnihilation,   0,-1,4);

    } else if( particleName == "alpha")     {
      //alpha
      pm->AddProcess(new G4hMultipleScattering, -1,1,1);
      pm->AddProcess(new G4ionIonisation,       -1,2,2);

    } else if( particleName == "GenericIon" ) {
      //Ions
      pm->AddProcess(new G4hMultipleScattering, -1,1,1);
      pm->AddProcess(new G4ionIonisation,       -1,2,2);

    }
  }

  // scattering
  G4EmProcessOptions emOptions;

  // scattering
  emOptions.SetPolarAngleLimit(0.0);
}

void PhysicsList::SetCuts()
{

  SetCutsWithDefault();
  DumpCutValuesTable();

  SetCutValue(1*um, "e-");
  SetCutValue(1*um, "e+");
}
