/*
  \file     PhysicsList.hh
  \brief    Implementation of the physic processes
*/
#ifndef PHYSICSLIST_HH_
#define PHYSICSLIST_HH_

#include "G4VUserPhysicsList.hh"
#include "globals.hh"

/*!
* \class PhysicsList
* \brief Implementation of the physic processes
*/
class PhysicsList : public G4VUserPhysicsList
{
  public:
    /*!
    * \brief Constructor
    */
    PhysicsList();
    /*!
    * \brief Destructor
    */
   ~PhysicsList();

  protected:
    /*!
    * \brief Construct particles
    */
    void ConstructParticle();
    /*!
    * \brief Construct processes associated to particles
    */
    void ConstructProcess();
    /*!
    * \brief Set cut for processes to happen
    */
    void SetCuts();

    void ConstructBosons();
    void ConstructLeptons();
    void ConstructMesons();
    void ConstructBaryons();

    void ConstructGeneral();
    void ConstructEM();
    void AddStepMax();
};

#endif
