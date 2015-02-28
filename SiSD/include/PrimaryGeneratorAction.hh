/*
  \file     PrimaryGeneratorAction.hh
  \brief    Generator of particle
*/
#ifndef PRIMARYGENERATORACTION_HH_
#define PRIMARYGENERATORACTION_HH_

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
#include "globals.hh"

class G4ParticleGun;
class G4Event;

/*!
* \class PrimaryGeneratorAction
* \brief Generator of particle
*/
class PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
  public:
    /*!
    * \brief Constructor
    */
    PrimaryGeneratorAction();
    /*!
    * \brief Destructor
    */
    virtual ~PrimaryGeneratorAction();
    /*!
    * \brief Generate primary particles
    */
    virtual void GeneratePrimaries(G4Event*);
    /*!
    * \brief Get the current particle gun
    * \return Current particle gun
    */
    const G4ParticleGun* GetParticleGun() const { return fParticleGun; }

  private:
    G4ParticleGun*  fParticleGun;
};


#endif
