#ifndef SiHit_h
#define SiHit_h 1

#include "G4VHit.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"
#include "G4THitsCollection.hh"

class SiHit : public G4VHit {
public:

  SiHit(const G4int strip, const G4int plane, const G4bool isPrimary);

  ~SiHit();

  void Print();

public:

  inline void *operator    new(size_t);
  inline void  operator delete(void *aHit);

  void AddEdep(const double e)                { eDep += e; }
  void SetPosition(const G4ThreeVector & pos) { position = pos; }

  G4double      GetEdep()        const { return eDep;}
  G4ThreeVector GetPosition()    const { return position; }
  G4int         GetStripNumber() const { return stripNumber; }
  G4int         GetPlaneNumber() const { return planeNumber; }
  G4bool        GetIsPrimary()   const { return isPrimary; }


private:

  const G4int   stripNumber, planeNumber;
  G4double      eDep;
  G4ThreeVector position;
  const G4bool  isPrimary;
};

// Define the "hit collection" using the template class G4THitsCollection:
typedef G4THitsCollection<SiHit> SiHitCollection;


// new and delete overloaded
extern G4Allocator<SiHit> SiHitAllocator;

inline void* SiHit::operator new(size_t)
{
  void *aHit;
  aHit = (void *) SiHitAllocator.MallocSingle();
  return aHit;
}
inline void SiHit::operator delete(void *aHit)
{
  SiHitAllocator.FreeSingle((SiHit*) aHit);
}

#endif
