#include "SiDigitizerMessenger.hh"
#include "SiDigitizer.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithADouble.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "CLHEP/Units/SystemOfUnits.h"

using namespace CLHEP;

SiDigitizerMessenger::SiDigitizerMessenger(SiDigitizer* digitizer) :
        digi(digitizer)
{
        digiDir = new G4UIdirectory("/det/digi/");
        digiDir->SetGuidance("commands related to the digitization process");

        pedestalCmd = new G4UIcmdWithADouble("/det/digi/pedestal",this);
        pedestalCmd->SetGuidance("Set pedestal value");
        pedestalCmd->SetDefaultValue(50.);
        pedestalCmd->AvailableForStates(G4State_Idle);

        noiseCmd = new G4UIcmdWithADouble("/det/digi/noise",this);
        noiseCmd->SetGuidance("Set the variation of noise around the pedestal");
        noiseCmd->SetDefaultValue(10.);
        noiseCmd->AvailableForStates(G4State_Idle);

        crosstalkCmd = new G4UIcmdWithADouble("/det/digi/crosstalk",this);
        crosstalkCmd->SetGuidance("Set the crosstalk fraction between strips");
        crosstalkCmd->SetDefaultValue(0.);
        crosstalkCmd->AvailableForStates(G4State_Idle);
}


SiDigitizerMessenger::~SiDigitizerMessenger()
{
        delete pedestalCmd;
        delete noiseCmd;
        delete crosstalkCmd;
        delete digiDir;
}

void SiDigitizerMessenger::SetNewValue(G4UIcommand* cmd,G4String newValue)
{
        if ( cmd == pedestalCmd )
                digi->SetPedestal( pedestalCmd->GetNewDoubleValue(newValue) );

        if ( cmd == noiseCmd )
                digi->SetNoise( noiseCmd->GetNewDoubleValue(newValue) );

        if ( cmd == crosstalkCmd )
                digi->SetCrosstalk( crosstalkCmd->GetNewDoubleValue(newValue) );
}
