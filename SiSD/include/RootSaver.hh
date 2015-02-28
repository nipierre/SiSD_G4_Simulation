/*
  \file     RootSaver.hh
  \brief    Save data to Root files
*/
#ifndef ROOTSAVER_HH_
#define ROOTSAVER_HH_

#include <string>
#include <TTree.h>
#include "SiDigi.hh"
#include "SiHit.hh"

class TFile;

/*!
* \class RootSaver
* \brief Save data to Root files
*/
class RootSaver
{
  public:
    /*!
    * \brief Constructor
    */
    RootSaver();
    /*!
    * \brief Destructor
    */
    virtual ~RootSaver();
    /*!
    * \brief Create a tree
    * \param treename : name of the created tree
    */
    virtual void CreateTree( const std::string& treeName = "SiSD" );
    /*!
    * \brief Close the current tree
    */
    virtual void CloseTree();
    /*!
    * \brief Add event data to the current tree
    * \param hits : hit collection to save
    * \param digits : digit collection to save
    */
    virtual void AddEvent( const SiHitCollection* const hits , const SiDigiCollection* const digits);

  private:
    TTree* rootTree;
    unsigned int runCounter;

    Int_t nStrips;
    Float_t* StripSignal;
    Float_t E;
    Float_t xPos;
    Float_t yPos;
};

#endif
