#ifndef DetectorConstruction_h
#define DetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"
#include "DetectorMessenger.hh"
#include "globals.hh"
#include "G4Box.hh"
#include "G4Polyhedra.hh"
#include "G4EqMagElectricField.hh"
#include "G4UniformElectricField.hh"

#include "G4MagIntegratorStepper.hh"
#include "G4ChordFinder.hh"
#include "G4FieldManager.hh"

class G4VPhysicalVolume;
class G4LogicalVolume;
class G4Material;
class DetectorMessenger;

/// Detector construction class to define materials and geometry.

class DetectorConstruction : public G4VUserDetectorConstruction
{
  public:
    DetectorConstruction();
    virtual ~DetectorConstruction();

    virtual G4VPhysicalVolume* Construct();

    void UpdateGeometry();

    G4double GetSensorOffset() const { return detectorOffset; }
    G4double SetSensorOffset(const G4double & offset) { return detectorOffset=offset; }

    G4double GetTargetOffset() const { return targetOffset; }
    G4double SetTargetOffset(const G4double & offset) { return targetOffset=offset; }

    G4double GetSensorAngle() const { return detectorTheta; }
    G4double SetSensorAngle(const G4double theta)  { return detectorTheta=theta; }

    G4double GetTargetAngle() const { return targetTheta; }
    G4double SetTargetAngle(const G4double theta)  { return targetTheta=theta; }

  private:
    void DefineMaterials();
    void DefineGlobalField(G4ThreeVector fieldValue, G4double minStepValue);
    G4FieldManager* DefineLocalField(G4ThreeVector fieldValue, G4double minStepValue);

    void ComputeParameters();

    G4VPhysicalVolume* ConstructTarget();
    G4VPhysicalVolume* ConstructSensor();

  private:

    G4bool  fCheckOverlaps;

    // Materials
    G4Material* silicon;
    G4Material* gold;
    G4Material* carbon;
    G4Material* vacuum;
    G4Material* aluminium;

    G4Material* targetMaterial;

    // ** World **

    G4double halfWorldLength;

    G4LogicalVolume * logicWorld;

    // ** Target **
    G4double targetRadius;
    G4double targetThickness;
    G4double targetOffset;
    G4double targetTheta;
    G4ThreeVector posTarget;

    G4VPhysicalVolume* physiTarget;

    // ** Si Detector **
    G4int noOfSensorStrips;
    G4double bulkLength;
    G4double bulkThickness;
    G4double sensorThickness;
    G4double maskThickness;
    G4double holesRadius;
    G4double stripLength;
    G4double stripPitch;
    G4double detectorOffset;
    G4double detectorTheta;
    G4ThreeVector posDetector;

    G4bool holesMask[8][9];

    G4VPhysicalVolume* physiDetector;

    // UI Messenger
    DetectorMessenger * messenger;

};

#endif
