/*
  \file     Run.hh
  \brief    Manage the run
*/
#ifndef RUN_HH_
#define RUN_HH_

#include "G4Run.hh"
#include "globals.hh"

/*!
* \class Run
* \brief Manage the run
*/
class Run : public G4Run
{
  public:
    /*!
    * \brief Constructor
    */
    Run();
    /*!
    * \brief Destructor
    */
    virtual ~Run();
    /*!
    * \brief Record non-empty events
    */
    virtual void RecordEvent(const G4Event*);
};

#endif
