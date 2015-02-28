/*
  \file     RunAction.hh
  \brief    Lead the run
*/
#ifndef RUNACTION_HH_
#define RUNACTION_HH_

#include "G4UserRunAction.hh"
#include "globals.hh"
#include "RootSaver.hh"
#include "EventAction.hh"

class G4Run;

/*!
* \class RunAction
* \brief Lead the run
*/
class RunAction : public G4UserRunAction
{
  public:
    /*!
    * \brief Constructor
    * \param theEventAction : an event
    */
    RunAction(EventAction* theEventAction);
    /*!
    * \brief Destructor
    */
    virtual ~RunAction();
    /*!
    * \brief Generate the run
    */
    virtual G4Run* GenerateRun();
    /*!
    * \brief Manage the beginning of the run
    */
    virtual void BeginOfRunAction(const G4Run*);
    /*!
    * \brief Manage the ending of the run
    */
    virtual void   EndOfRunAction(const G4Run*);

  private:
    RootSaver saver;
    EventAction* eventAction;
};

#endif
