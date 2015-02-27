#ifndef EventAction_h
#define EventAction_h 1

#include "G4UserEventAction.hh"
#include "G4String.hh"
#include "SiDigi.hh"
#include "SiDigitizer.hh"
#include "RootSaver.hh"

class G4Event;

class EventAction : public G4UserEventAction
{
  public:
    EventAction();
   ~EventAction();

    void BeginOfEventAction(const G4Event*);
    void EndOfEventAction(const G4Event*);

    inline void SetRootSaver( RootSaver* saver ) { rootSaver = saver; }

  private:
    RootSaver* rootSaver;
    G4String hitsCollName;
    G4String digitsCollName;
    G4int hitsCollID;
};

#endif
