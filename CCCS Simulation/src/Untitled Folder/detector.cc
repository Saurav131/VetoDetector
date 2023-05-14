#include "detector.hh"
#include "G4GenericAnalysisManager.hh"
// #include "G4CsvAnalysisManager.hh"
#include "G4GenericAnalysisManager.hh"


MySensitiveDetector::MySensitiveDetector(G4String name):G4VSensitiveDetector(name)
{}
MySensitiveDetector::~MySensitiveDetector()
{}
G4bool MySensitiveDetector::ProcessHits(G4Step *aStep , G4TouchableHistory *ROhist)
{
    G4Track *track = aStep->GetTrack();  
    // track->SetTrackStatus(fStopAndKill); 
    // kills entire ray 
    G4ThreeVector direction = track-> GetVertexMomentumDirection();
    // G4StepPoint *preStepPoint = aStep -> GetPreStepPoint();
    // G4StepPoint *postStepPoint = aStep -> GetPostStepPoint();
    // G4ThreeVector posPhoton = preStepPoint -> GetPosition();
    // G4double energyDeposit = aStep ->GetTotalEnergyDeposit();

    G4int evt = G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();
    // G4cout << " event : " << evt << G4endl;
    G4cout << " Direction : " << acos(direction[2]) << G4endl;
    // track->SetTrackStatus(fStopAndKill);

    
    // G4GenericAnalysisManager *man = G4GenericAnalysisManager::Instance();
    // man->FillH1(0, acos(direction[2]));

    // G4CsvAnalysisManager *man = G4CsvAnalysisManager::Instance();
    // man->FillNtupleIColumn(0,evt);
    // man->FillNtupleDColumn(1,posPhoton[0]);
    // man->FillNtupleDColumn(2,posPhoton[1]);
    // man->FillNtupleDColumn(3,posPhoton[2]);
    // man->FillNtupleDColumn(4,energyDeposit);
    // man->AddNtupleRow(0);
 


    return true;

}


