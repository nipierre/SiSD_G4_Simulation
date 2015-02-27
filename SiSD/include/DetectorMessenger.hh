#ifndef DetectorMessenger_h
#define DetectorMessenger_h 1

#include "globals.hh"
#include "G4UImessenger.hh"

class DetectorConstruction;
class G4UIdirectory;
class G4UIcmdWithAString;
class G4UIcmdWithADoubleAndUnit;
class G4UIcmdWith3VectorAndUnit;
class G4UIcmdWithoutParameter;
class G4UIcmdWithABool;


class DetectorMessenger: public G4UImessenger
{
public:
  DetectorMessenger(DetectorConstruction* );

  ~DetectorMessenger();

  void SetNewValue(G4UIcommand*, G4String);

private:

  DetectorConstruction*      detector;

  G4UIdirectory*             detDir;
  G4UIdirectory*             SensorDir;
  G4UIdirectory*             TargetDir;

  G4UIcmdWithADoubleAndUnit* detectorOffsetCmd;
  G4UIcmdWithADoubleAndUnit* targetOffsetCmd;
  G4UIcmdWithADoubleAndUnit* thetaSensorCmd;
  G4UIcmdWithADoubleAndUnit* thetaTargetCmd;

  G4UIcmdWithoutParameter*   updateCmd;
};

#endif
