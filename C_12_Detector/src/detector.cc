#include "detector.hh"
MySensitiveDetector::MySensitiveDetector(G4String name):G4VSensitiveDetector(name)
{}
MySensitiveDetector::~MySensitiveDetector()
{}
G4bool MySensitiveDetector::ProcessHits(G4Step *aStep , G4TouchableHistory *ROhist)
{
    G4Track *track = aStep->GetTrack();  
    // track->SetTrackStatus(fStopAndKill); 
    // kills entire ray 
    G4StepPoint *preStepPoint = aStep -> GetPreStepPoint();
    G4StepPoint *postStepPoint = aStep -> GetPostStepPoint();
    G4ThreeVector posPhoton = preStepPoint -> GetPosition();
    G4cout << "Particle_position: " << posPhoton << G4endl;

    G4int evt = G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();

    G4AnalysisManager *man = G4AnalysisManager::Instance();
    man->FillNtupleIColumn(0,evt);
    man->FillNtupleDColumn(1,posPhoton[0]);
    man->FillNtupleDColumn(2,posPhoton[1]);
    man->FillNtupleDColumn(3,posPhoton[2]);
    man->AddNtupleRow(0);
    return true;
}









// B2TrackerSD::B2TrackerSD(const G4String& name,
//                          const G4String& hitsCollectionName) 
//  : G4VSensitiveDetector(name),
//    HitsCollection(NULL)
// {
//   collectionName.insert(hitsCollectionName);
// }

// B2TrackerSD::~B2TrackerSD() 
// {}

// void B2TrackerSD::Initialize(G4HCofThisEvent* hce)
// {
//   // Create hits collection

//   G4VHitsCollection *HitsCollection 
//     = new B2TrackerHitsCollection(SensitiveDetectorName, collectionName[0]); 

//   // Add this collection in hce

//   G4int hcID 
//     = G4SDManager::GetSDMpointer()->GetCollectionID(collectionName[0]);
//   hce->AddHitsCollection( hcID, HitsCollection ); 

// G4int nofHits = HitsCollection->entries();
// G4cout << G4endl
//         << "-------->Hits Collection: in this event they are " << nofHits 
//         << " hits in the tracker chambers: " << G4endl;
// }




