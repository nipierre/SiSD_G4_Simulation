#include "RootSaver.hh"
#include "SiDigi.hh"
#include "SiHit.hh"
#include "TTree.h"
#include "TFile.h"
#include "TMath.h"
#include "CLHEP/Units/SystemOfUnits.h"
#include <sstream>
#include <iostream>
#include <cassert>

RootSaver::RootSaver() :
        rootTree(0),
        runCounter(0),
        nStrips(0),
        StripSignal(0),
        E(0),
        xPos(0),
        yPos(0)
{

}

RootSaver::~RootSaver()
{
        if ( rootTree )
        {
                CloseTree();
        }
}

void RootSaver::CreateTree( const std::string& treeName )
{
        if ( rootTree )
        {
                std::cerr<<"TTree already created, first call CloseTree"<<std::endl;
                return;
        }
        std::ostringstream fn;
        fn << "../run" << runCounter++ << ".root";

        TFile* rootFile = TFile::Open( fn.str().data() , "recreate" );
        if ( rootFile == 0 || rootFile->IsZombie() )
        {
                G4cerr<<"Error opening the file: "<<fn.str() <<" TTree will not be saved."<<G4endl;
                return;
        }
        rootTree = new TTree( treeName.data() , treeName.data() );

        nStrips = 16;
        StripSignal = new Float_t[nStrips];

        for ( Int_t strip = 0 ; strip < nStrips ; ++strip )
        {
                StripSignal[strip] = 0;
        }
        //Strip signal
        rootTree->Branch( "StripSignal", StripSignal , "StripSignal[16]/F");
        //Hits
        rootTree->Branch( "E" , &E );
        rootTree->Branch( "xPos" , &xPos );
        rootTree->Branch( "yPos" , &yPos );
}

void RootSaver::CloseTree()
{
        if ( rootTree )
        {
                G4cout<<"Writing ROOT TTree: "<<rootTree->GetName()<<G4endl;
                rootTree->Write();

                TFile* currentFile = rootTree->GetCurrentFile();
                if ( currentFile == 0 || currentFile->IsZombie() )
                {
                        G4cerr<<"Error closing TFile "<<G4endl;
                        return;
                }
                currentFile->Close();

                rootTree = 0;
                delete[] StripSignal;
        }
}

void RootSaver::AddEvent( const SiHitCollection* const hits, const SiDigiCollection* const digits)
{
        if ( rootTree == 0 )
        {
                return;
        }

        if ( digits )
        {
                G4int nDigits = digits->entries();
                for ( G4int d = 0 ; d<nDigits ; d++ )
                {
                        const SiDigi* digi = static_cast<const SiDigi*>( digits->GetDigi( d ) );
                        G4int stripNum = digi->GetStripNumber();
                        //Safety check
                        if ( stripNum >= nStrips )
                        {
                                G4cerr<<"Digi Error: Strip number "<<stripNum<<" expected max value:"<<nStrips<<G4endl;
                                continue;//Go to next digit
                        }
                        G4int planeNum = digi->GetPlaneNumber();
                        if ( planeNum == 0 )
                        {
                                StripSignal[ stripNum ] = static_cast<Float_t>(digi->GetCharge());
                        }
                        else
                        {
                                G4cerr<<"Digi Error: Plane number "<<planeNum<<" expected max value: 0"<<G4endl;
                        }
                }
        }
        else
        {
                G4cerr<<"Error: No digi collection passed to RootSaver"<<G4endl;
        }

        //Store Hits infromation
        G4bool real = false;

        if ( hits )
        {
                G4int nHits = hits->entries();

                if( !nHits )
                  return;

                //Set defaults
                E = 0;
                xPos = 0;
                yPos = 0;

                G4double sensorTheta = 55*CLHEP::deg;
                G4double zDefault = 60*(1+cos(sensorTheta));
                G4double xDefault = -60*sin(sensorTheta);

                for ( G4int h = 0 ; (h<nHits) ; ++h )
                {
                        const SiHit* hit = static_cast<const SiHit*>( hits->GetHit( h ) );

                        //If you want only primary, uncomment below
                        //if ( hit->GetIsPrimary() == false ) continue;

                        G4int planeNum = hit->GetPlaneNumber();
                        G4ThreeVector pos = hit->GetPosition();

                        G4double x = pos.x();
                        G4double y = pos.y();
                        G4double z = pos.z();

                        //Save position in mm
                        x /= 1.*CLHEP::mm;
                        y /= 1.*CLHEP::mm;
                        z /= 1.*CLHEP::mm;

                        Float_t edep = static_cast<Float_t>(hit->GetEdep());
                        edep /= 1.*CLHEP::MeV;
                        if ( planeNum == 0 )
                        {
                              if ( hit->GetIsPrimary() == true )
                              {
                                if(sensorTheta >= 0)
                                {
                                  if(z < zDefault)
                                    xPos = sqrt(pow(x-xDefault,2)+pow(z-zDefault,2));
                                  else
                                    xPos = -sqrt(pow(x-xDefault,2)+pow(z-zDefault,2));
                                }

                                else
                                {
                                  if(z < zDefault)
                                    xPos = sqrt(pow(x-xDefault,2)+pow(z-zDefault,2));
                                  else
                                    xPos = -sqrt(pow(x-xDefault,2)+pow(z-zDefault,2));
                                }
                                 yPos = 2*y;
                                 real = true;
                               }

                               E += edep;
                        }
                        else
                        {
                                G4cerr<<"Hit Error: Plane number "<<planeNum<<" expected max value: 0"<<G4endl;
                                continue;
                        }

                }
        }
        else
        {
                G4cerr<<"Error: No hits collection passed to RootSaver"<<G4endl;
        }

        if(real)
          rootTree->Fill();
}
