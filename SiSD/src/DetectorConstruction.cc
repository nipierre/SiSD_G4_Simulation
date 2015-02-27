#include "DetectorConstruction.hh"
#include "DetectorMessenger.hh"

#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4RotationMatrix.hh"
#include "G4Transform3D.hh"
#include "G4SDManager.hh"
#include "G4MultiFunctionalDetector.hh"
#include "G4VPrimitiveScorer.hh"
#include "G4PSEnergyDeposit.hh"
#include "G4PSDoseDeposit.hh"
#include "G4VisAttributes.hh"
#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"

#include "G4GeometryManager.hh"
#include "G4PhysicalVolumeStore.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4SolidStore.hh"

#include "G4PVReplica.hh"

#include "G4UniformElectricField.hh"
#include "G4FieldManager.hh"
#include "G4TransportationManager.hh"

#include "G4EqMagElectricField.hh"
#include "G4UniformElectricField.hh"
#include "G4ClassicalRK4.hh"

#include "SensitiveDetector.hh"

#include "G4RunManager.hh"

#include <string>

DetectorConstruction::DetectorConstruction()
: G4VUserDetectorConstruction(),
  fCheckOverlaps(true)
{
  //Create a messanger (defines custom UI commands)
  messenger = new DetectorMessenger(this);

  DefineMaterials();
  ComputeParameters();
  DefineGlobalField(G4ThreeVector(), 1*um);

  // Print materials
  G4cout << G4endl << "The materials defined are : " << G4endl << G4endl;
  G4cout << *(G4Material::GetMaterialTable()) << G4endl;
}

DetectorConstruction::~DetectorConstruction()
{
  delete messenger;
}

void DetectorConstruction::DefineMaterials()
{
 //Get Materials from NIST database
 G4NistManager* man = G4NistManager::Instance();
 man->SetVerbose(0);

 // define NIST materials
 // Density multiplied by 100 from the experiment to collect more data / faster
 G4double density = 10.*g/cm3; //223*ug/cm2 * 100

 silicon = man->FindOrBuildMaterial("G4_Si");
 gold = man->BuildMaterialWithNewDensity("Au_223","G4_Au",density);
 carbon = man->FindOrBuildMaterial("G4_C");
 aluminium = man->FindOrBuildMaterial("G4_Al");
 vacuum  = man->FindOrBuildMaterial("G4_Galactic");
}

void DetectorConstruction::DefineGlobalField(G4ThreeVector fieldValue, G4double minStepValue)
{
  G4UniformElectricField* electricField = new G4UniformElectricField(fieldValue);
  G4EqMagElectricField* equation        = new G4EqMagElectricField(electricField);
  G4ClassicalRK4* stepper               = new G4ClassicalRK4(equation, 8);

  G4MagInt_Driver* intgrDriver = new G4MagInt_Driver(minStepValue, stepper, stepper->GetNumberOfVariables());
  G4ChordFinder* chordFinder   = new G4ChordFinder(intgrDriver);

  G4FieldManager* fieldMgr = G4TransportationManager::GetTransportationManager()->GetFieldManager();
                  fieldMgr->SetDetectorField(electricField);
                  fieldMgr->SetChordFinder(chordFinder);
}

G4FieldManager* DetectorConstruction::DefineLocalField(G4ThreeVector fieldValue, G4double minStepValue)
{
  G4UniformElectricField* electricField = new G4UniformElectricField(fieldValue);
  G4EqMagElectricField* equation        = new G4EqMagElectricField(electricField);
  G4ClassicalRK4* stepper               = new G4ClassicalRK4(equation, 8);

  G4MagInt_Driver* intgrDriver = new G4MagInt_Driver(minStepValue, stepper, stepper->GetNumberOfVariables());
  G4ChordFinder* chordFinder   = new G4ChordFinder(intgrDriver);

  G4FieldManager* fieldMgr = new G4FieldManager(electricField);
                  fieldMgr->SetChordFinder(chordFinder);

  return fieldMgr;
}

void DetectorConstruction::ComputeParameters()
{
 //This function defines the defaults
 //of the geometry construction

 // ** world **
 halfWorldLength = 50*cm;

 // ** Target **
 targetRadius = 2.5*mm;
 targetThickness = 12*um;
 targetOffset = 6*cm;
 targetTheta = 0.*deg;
 targetMaterial = gold;

 // ** Si Detector **
 noOfSensorStrips = 16;
 bulkLength = 50.*mm;
 bulkThickness = 251.*um;
 sensorThickness = 60.*um;
 maskThickness = 0*mm;
 holesRadius = 0.5*mm;
 stripLength  = 3.025*mm;
 stripPitch = 100*um;
 detectorOffset = 6*cm;
 detectorTheta = 55.*deg;

 for(int i=0; i<8; i++)
   for(int j=0; j<9; j++)
   {
      if(j!=4 && j!=5)
        holesMask[i][j] = 0;
      else
        holesMask[i][j] = 1;
    }

 /*holesMask = {{0,0,0,0,1,1,0,0,0},
              {0,0,0,0,1,1,0,0,0},
              {0,0,0,0,1,1,0,0,0},
              {0,0,0,0,1,1,0,0,0},
              {0,0,0,0,1,1,0,0,0},
              {0,0,0,0,1,1,0,0,0},
              {0,0,0,0,1,1,0,0,0},
              {0,0,0,0,1,1,0,0,0}};*/

}

G4VPhysicalVolume* DetectorConstruction::Construct()
{

  // World
  G4Box* solidWorld            = new G4Box("World", halfWorldLength, halfWorldLength, halfWorldLength);
  logicWorld                   = new G4LogicalVolume(solidWorld, vacuum, "World");
  G4VPhysicalVolume* physWorld = new G4PVPlacement(0, G4ThreeVector(), logicWorld, "World", 0, false, 0, fCheckOverlaps);

  ConstructTarget();
  ConstructSensor();

  //--------- Visualization attributes -------------------------------

  G4Color white(1.0,1.0,1.0);

  logicWorld -> SetVisAttributes(new G4VisAttributes(white));
  logicWorld -> SetVisAttributes(G4VisAttributes::Invisible);

  return physWorld;
}

G4VPhysicalVolume* DetectorConstruction::ConstructTarget()
{
  // Target
  G4Tubs* solidTarget          = new G4Tubs("Target", 0, targetRadius, targetThickness/2, 0, 360);
  G4LogicalVolume* logicTarget = new G4LogicalVolume(solidTarget, targetMaterial, "Target");
  G4RotationMatrix* rm = new G4RotationMatrix;
                    rm->rotateY(targetTheta);

  posTarget = G4ThreeVector(0, 0, targetOffset);

  physiTarget = new G4PVPlacement(rm, posTarget, logicTarget, "Target", logicWorld, FALSE, 0, fCheckOverlaps);

  G4Color yellow(1.0,1.0,0.0);

  logicTarget -> SetVisAttributes(new G4VisAttributes(yellow));

  return physiTarget;
}

G4VPhysicalVolume* DetectorConstruction::ConstructSensor()
{

  // ----------------------------------------------------------
  // -- Size definition
  // ----------------------------------------------------------

  G4double halfBulkSizeX = bulkLength/2.;
  G4double halfBulkSizeY = bulkLength/2.;
  G4double halfBulkSizeZ = bulkThickness/2.;

  G4double halfMaskSizeX = bulkLength/2.;
  G4double halfMaskSizeY = bulkLength/2.;
  G4double halfMaskSizeZ = maskThickness/2.;

  G4double halfSensorX = bulkLength/2.;
  G4double halfSensorY = bulkLength/2.;
  G4double halfSensorZ = sensorThickness/2.;

  G4double halfPseudoStripX = bulkLength/2.;
  G4double halfPseudoStripY = (stripLength+stripPitch)/2.;
  G4double halfPseudoStripZ = sensorThickness/2.;

  G4double halfStripX = bulkLength/2.;
  G4double halfStripY = stripLength/2.;
  G4double halfStripZ = sensorThickness/2.;


  // ----------------------------------------------------------
  // -- Detector
  // ----------------------------------------------------------

  G4Box* solidDetector           = new G4Box("Detector", halfBulkSizeX, halfBulkSizeY, halfBulkSizeZ+halfSensorZ+halfMaskSizeZ);
  G4LogicalVolume* logicDetector = new G4LogicalVolume(solidDetector, vacuum, "Detector");
                   logicDetector->SetFieldManager(DefineLocalField(G4ThreeVector(0, 0, -964.6*volt/cm), 1*um), true);

  G4RotationMatrix* rm = new G4RotationMatrix;
                    rm->rotateY(detectorTheta);

  posDetector = G4ThreeVector(-detectorOffset*sin(detectorTheta), 0,
                              detectorOffset*cos(detectorTheta) + targetOffset + halfBulkSizeZ + halfSensorZ + halfMaskSizeZ);

  physiDetector = new G4PVPlacement(rm, posDetector, logicDetector, "Detector", logicWorld, false, 0, fCheckOverlaps);

  // ----------------------------------------------------------
  // -- Mask
  // ----------------------------------------------------------

  if(maskThickness != 0)
  {

    G4Box* solidMask           = new G4Box("Mask", halfMaskSizeX, halfMaskSizeY, halfMaskSizeZ);
    G4LogicalVolume* logicMask = new G4LogicalVolume(solidMask, aluminium, "Mask");
    new G4PVPlacement(0, G4ThreeVector(0, 0, -halfStripZ-halfBulkSizeZ),logicMask,"Mask",logicDetector, false, 0, fCheckOverlaps);

    G4Tubs* hole          = new G4Tubs("Hole", 0, holesRadius, halfMaskSizeZ, 0, 360);
    G4LogicalVolume* logicHole = new G4LogicalVolume(hole, vacuum, "Hole");

    for(int i = 0; i < 9; i++) for(int j = 0; j < 8; j++) {

      G4double xHole =   (i - 4)*5*mm;
      G4double yHole = 2*(j - 3.25)*(stripLength+stripPitch) - ((i%2 == 0) ? 3.125*mm : 0);

      if(holesMask[j][i] == 1)
        new G4PVPlacement(0, G4ThreeVector(xHole, -yHole, 0),  logicHole, "Hole", logicMask, false, 0, FALSE);
     }
  }

  // ----------------------------------------------------------
  // -- Bulk
  // ----------------------------------------------------------

  G4Box* solidBulk           = new G4Box("Bulk", halfBulkSizeX, halfBulkSizeY, halfBulkSizeZ);
  G4LogicalVolume* logicBulk = new G4LogicalVolume(solidBulk, silicon, "Bulk");
  new G4PVPlacement(0, G4ThreeVector(0, 0, halfSensorZ+halfMaskSizeZ),  logicBulk, "Bulk", logicDetector, false, 0, fCheckOverlaps);

  // ----------------------------------------------------------
  // -- Sensitive Layer
  // ----------------------------------------------------------

  G4Box* solidSensitiveLayer          = new G4Box("SensitiveLayer", halfSensorX, halfSensorY, halfSensorZ);
  G4LogicalVolume* logicSensitiveLayer = new G4LogicalVolume(solidSensitiveLayer, silicon, "SensitiveLayer");
  new G4PVPlacement(0, G4ThreeVector(0, 0, -halfBulkSizeZ+halfMaskSizeZ), logicSensitiveLayer, "SensitiveLayer", logicDetector, false, 0, fCheckOverlaps);

  // ----------------------------------------------------------
  // -- Pseudo-Strips
  // ----------------------------------------------------------

  G4Box * solidPS = new G4Box("PseudoStrip", halfPseudoStripX, halfPseudoStripY, halfPseudoStripZ);

  G4LogicalVolume * logicPS = new G4LogicalVolume(solidPS, silicon, "PseudoStrip");

  // ----------------------------------------------------------
  // -- Strips
  // ----------------------------------------------------------

  G4Box * solidStrip = new G4Box("SensorStrip", halfStripX, halfStripY, halfStripZ);
  G4LogicalVolume * logicStrip = new G4LogicalVolume(solidStrip, silicon, "SensorStrip");
  new G4PVPlacement(0, G4ThreeVector(), logicStrip, "SensitiveLayer", logicPS, false, 0, fCheckOverlaps);

  //Replication of both PseudoStrips and Strips
  new G4PVReplica("PseudoStrip", logicPS, logicSensitiveLayer, kYAxis, noOfSensorStrips, 2*halfPseudoStripY);

  // ----------------------------------------------------------
  // -- SD
  // ----------------------------------------------------------

  static SensitiveDetector* sensitive = 0;
  if ( !sensitive )
  {
    sensitive = new SensitiveDetector("/myDet/SiStripSD");

    G4SDManager::GetSDMpointer()->AddNewDetector(sensitive);

    logicStrip->SetSensitiveDetector(sensitive);
  }

  G4Color red(1.0,0.0,0.0);

  logicStrip -> SetVisAttributes(new G4VisAttributes(red));

  return physiDetector;
}

void DetectorConstruction::UpdateGeometry()
{

  G4GeometryManager::GetInstance()->OpenGeometry();
  G4PhysicalVolumeStore::GetInstance()->Clean();
  G4LogicalVolumeStore::GetInstance()->Clean();
  G4SolidStore::GetInstance()->Clean();

  G4RunManager::GetRunManager()->DefineWorldVolume(Construct());

}
