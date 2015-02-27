#ifndef ROOTSAVER_HH_
#define ROOTSAVER_HH_

#include <string>
#include <TTree.h>
#include "SiDigi.hh"
#include "SiHit.hh"
class TFile;

class RootSaver
{
public:

       RootSaver();

       virtual ~RootSaver();

       virtual void CreateTree( const std::string& treeName = "SiSD" );

       virtual void CloseTree();

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
