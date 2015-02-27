 #ifndef SensitiveDetector_h
 #define SensitiveDetector_h 1

 #include "G4VSensitiveDetector.hh"
 class DetectorConstruction;
 class RunAction;

 #include "SiHit.hh"
 class G4HCofThisEvent;

 class SensitiveDetector : public G4VSensitiveDetector
 {
 public:
   SensitiveDetector(G4String SDname);
   ~SensitiveDetector();

 public:
    G4bool ProcessHits(G4Step *step, G4TouchableHistory *ROhist);

   void Initialize(G4HCofThisEvent* HCE);
   void EndOfEvent(G4HCofThisEvent* HCE);
   //@}


 private:
   SiHitCollection*      hitCollection;
 };

 #endif
