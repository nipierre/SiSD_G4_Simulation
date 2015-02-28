/*
  \file     DetectorConstruction.hh
  \brief    Construction of the detector and the geometry
*/

#ifndef DETECTORCONSTRUCTION_HH_
#define DETECTORCONSTRUCTION_HH_

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

/*!
* \class DetectorConstruction
* \brief Construction of the detector and the geometry
*/
class DetectorConstruction : public G4VUserDetectorConstruction
{
  public:
    /*!
    * \brief Constructor
    */
    DetectorConstruction();
    /*!
    * \brief Destructor
    */
    virtual ~DetectorConstruction();

    /*!
    * \brief Construct the geometry and the detector
    */
    virtual G4VPhysicalVolume* Construct();

    /*!
    * \brief Update the geometry
    */
    void UpdateGeometry();


    G4double GetSensorOffset() const { return detectorOffset; }
    void SetSensorOffset(const G4double & offset) { detectorOffset=offset; }

    G4double GetTargetOffset() const { return targetOffset; }
    void SetTargetOffset(const G4double & offset) { targetOffset=offset; }

    G4double GetSensorAngle() const { return detectorTheta; }
    void SetSensorAngle(const G4double theta)  { detectorTheta=theta; }

    G4double GetTargetAngle() const { return targetTheta; }
    void SetTargetAngle(const G4double theta)  { targetTheta=theta; }

  private:
    /*!
    * \brief Define the used materials
    */
    void DefineMaterials();
    /*!
    * \brief Define the used global field
    * \param fieldValue : value of the global field
    * \param minStepValue : minimal step value
    */
    void DefineGlobalField(G4ThreeVector fieldValue, G4double minStepValue);
    /*!
    * \brief Define the used local field
    * \param fieldValue : value of the global field
    * \param minStepValue : minimal step value
    */
    G4FieldManager* DefineLocalField(G4ThreeVector fieldValue, G4double minStepValue);

    /*!
    * \brief Affects parameters to variables
    */
    void ComputeParameters();

    /*!
    * \brief Construct the target
    */
    G4VPhysicalVolume* ConstructTarget();
    /*!
    * \brief Construct the detector
    */
    G4VPhysicalVolume* ConstructSensor();

  private:

    G4bool  fCheckOverlaps;

    // ** Materials **
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
