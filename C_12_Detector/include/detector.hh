#ifndef DETECTOR_HH
#define DETECTOR_HH


#include "G4VSensitiveDetector.hh"
#include "g4root.hh"
#include "G4RunManager.hh"
class MySensitiveDetector : public G4VSensitiveDetector
{
public:
    MySensitiveDetector(G4String);
    ~MySensitiveDetector();
    
private:
    virtual G4bool ProcessHits(G4Step *, G4TouchableHistory *);

};
// class G4HCofThisEvent;

// class B2TrackerSD : public G4VSensitiveDetector
// {
//   public:
//    B2TrackerSD(const G4String& name, 
//                 const G4String& hitsCollectionName);
//     virtual ~B2TrackerSD();
  
//     // methods from base class
//     virtual void   Initialize(G4HCofThisEvent* hitCollection);
//     // virtual G4bool ProcessHits(G4Step* step, G4TouchableHistory* history);
//     // virtual void   EndOfEvent(G4HCofThisEvent* hitCollection);

//   private:
//     B2TrackerHitsCollection* fHitsCollection;
// };

#endif