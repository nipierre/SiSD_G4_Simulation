#include "SiDigi.hh"

//Trick for new and delete operator overloading:
G4Allocator<SiDigi> SiDigiAllocator;

SiDigi::SiDigi(const int& pn,const int& sn) :
                charge(0) ,
                stripNumber(sn) ,
                planeNumber(pn)
{

}

void SiDigi::Print()
{
  if(charge)
    G4cout<<"Digit: Plane= "<<planeNumber<<" Strip= "<<stripNumber<<" with Charge= "<<charge<<G4endl;
}
