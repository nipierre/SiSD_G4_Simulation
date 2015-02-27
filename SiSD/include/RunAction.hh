#ifndef RunAction_h
#define RunAction_h 1

#include "G4UserRunAction.hh"
#include "globals.hh"
#include "RootSaver.hh"
#include "EventAction.hh"

class G4Run;

class RunAction : public G4UserRunAction
{
  public:
    RunAction(EventAction* theEventAction);
    virtual ~RunAction();

    virtual G4Run* GenerateRun();
    virtual void BeginOfRunAction(const G4Run*);
    virtual void   EndOfRunAction(const G4Run*);

  private:
    RootSaver saver;
    EventAction* eventAction;
};

#endif
