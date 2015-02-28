/*
  \file     EventAction.hh
  \brief    Manage the Event and the Rootsaver
*/
#ifndef EVENTACTION_HH_
#define EVENTACTION_HH_

#include "G4UserEventAction.hh"
#include "G4String.hh"
#include "SiDigi.hh"
#include "SiDigitizer.hh"
#include "RootSaver.hh"

class G4Event;

/*!
* \class EventAction
* \brief Manage the Event and the saving of data into the Root file
* created by the RootSaver
*/
class EventAction : public G4UserEventAction
{
  public:
    /*!
    * \brief Constructor
    */
    EventAction();
    /*!
    * \brief Destructor
    */
    ~EventAction();

    /*!
    * \brief Called at each beginning of an Event
    */
    void BeginOfEventAction(const G4Event*);
    /*!
    * \brief Called at each ending of an Event
    */
    void EndOfEventAction(const G4Event*);

    /*!
    * \brief Set the RootSaver
    */
    inline void SetRootSaver( RootSaver* saver ) { rootSaver = saver; }

  private:
    RootSaver* rootSaver;
    G4String hitsCollName;
    G4String digitsCollName;
    G4int hitsCollID;
};

#endif
