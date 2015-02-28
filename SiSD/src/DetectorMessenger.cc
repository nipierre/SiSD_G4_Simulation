#include "DetectorMessenger.hh"
#include "DetectorConstruction.hh"

#include "G4UIdirectory.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithoutParameter.hh"
#include "G4UIcmdWithABool.hh"

DetectorMessenger::DetectorMessenger(DetectorConstruction * det) :
  detector(det)
{
  detDir = new G4UIdirectory("/det/");
  detDir->SetGuidance("detector construction commands");

  SensorDir = new G4UIdirectory("/det/sensor/");
  SensorDir->SetGuidance("commands related to the sensor plane");

  TargetDir = new G4UIdirectory("/det/target/");
  TargetDir->SetGuidance("commands related to the target");

  detectorOffsetCmd = new G4UIcmdWithADoubleAndUnit("/det/sensor/offset",this);
  detectorOffsetCmd->SetGuidance("Define offset (z-shift) of sensor plane");
  detectorOffsetCmd->SetParameterName("detectorOffset",true);
  detectorOffsetCmd->SetDefaultValue(0.);
  detectorOffsetCmd->SetUnitCategory("Length");
  detectorOffsetCmd->SetDefaultUnit("cm");

  targetOffsetCmd = new G4UIcmdWithADoubleAndUnit("/det/target/offset",this);
  targetOffsetCmd->SetGuidance("Define offset (z-shift) of sensor plane");
  targetOffsetCmd->SetParameterName("targetOffset",true);
  targetOffsetCmd->SetDefaultValue(0.);
  targetOffsetCmd->SetUnitCategory("Length");
  targetOffsetCmd->SetDefaultUnit("cm");

  thetaSensorCmd = new G4UIcmdWithADoubleAndUnit ("/det/sensor/theta", this);
  thetaSensorCmd->SetGuidance("Select rotation angle of sensor plane around y axis");
  thetaSensorCmd->SetParameterName("thetaSensor",true);
  thetaSensorCmd->SetUnitCategory("Angle");
  thetaSensorCmd->SetDefaultUnit("deg");

  thetaTargetCmd = new G4UIcmdWithADoubleAndUnit ("/det/target/theta", this);
  thetaTargetCmd->SetGuidance("Select rotation angle of target around y axis");
  thetaTargetCmd->SetParameterName("thetaTarget",true);
  thetaTargetCmd->SetUnitCategory("Angle");
  thetaTargetCmd->SetDefaultUnit("deg");
}

DetectorMessenger::~DetectorMessenger()
{
  delete detectorOffsetCmd;
  delete targetOffsetCmd;
  delete thetaSensorCmd;
  delete thetaTargetCmd;

  delete SensorDir;
  delete TargetDir;

  delete detDir;
}

void DetectorMessenger::SetNewValue(G4UIcommand* command,G4String newValue)
{
  if ( command == detectorOffsetCmd )
    detector->SetSensorOffset(detectorOffsetCmd->GetNewDoubleValue(newValue));

  if ( command == targetOffsetCmd )
    detector->SetTargetOffset(targetOffsetCmd->GetNewDoubleValue(newValue));

  if ( command == thetaSensorCmd )
    detector->SetSensorAngle(thetaSensorCmd->GetNewDoubleValue(newValue));

  if ( command == thetaTargetCmd )
    detector->SetTargetAngle(thetaTargetCmd->GetNewDoubleValue(newValue));

  detector->UpdateGeometry();
}
