/*
  \file     ActionInitialization.hh
  \brief    Reimplementation of G4VUserActionInitialization
*/

#ifndef ACTIONINITIALIZATION_HH_
#define ACTIONINITIALIZATION_HH_

#include "G4VUserActionInitialization.hh"

/*!
* \class ActionInitialization
* \brief Reimplementation of G4VUserActionInitialization
*/
class ActionInitialization : public G4VUserActionInitialization
{
  public:
    /*!
    * \brief Constructor
    */
    ActionInitialization();
    /*!
    * \brief Destructor
    */
    virtual ~ActionInitialization();

    /*!
    * \brief Build for Master
    */
    virtual void BuildForMaster() const;
    /*!
    * \brief Initialize the Run
    */
    virtual void Build() const;
};

#endif
