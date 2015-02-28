/*
  \file     DetectorMessenger.hh
  \brief    UI commands wrapper for the detector construction
*/

#ifndef DETECTORMESSENGER_HH_
#define DETECTORMESSENGER_HH_

#include "globals.hh"
#include "G4UImessenger.hh"

class DetectorConstruction;
class G4UIdirectory;
class G4UIcmdWithAString;
class G4UIcmdWithADoubleAndUnit;
class G4UIcmdWith3VectorAndUnit;
class G4UIcmdWithoutParameter;
class G4UIcmdWithABool;

/*!
* \class DetectorMessenger
* \brief UI commands wrapper for the detector construction
*/
class DetectorMessenger: public G4UImessenger
{
public:
  /*!
  * \brief Constructor
  */
  DetectorMessenger(DetectorConstruction* );
  /*!
  * \brief Destructor
  */
  ~DetectorMessenger();
  /*!
  * \brief Enter a new value in a command
  */
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
};

#endif
