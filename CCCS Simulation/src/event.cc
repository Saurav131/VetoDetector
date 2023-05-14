#include "EventAction.hh"
#include "RunAction.hh"

#include "G4GenericAnalysisManager.hh"
#include "G4RunManager.hh"
#include "G4Event.hh"
#include "G4UnitsTable.hh"

#include "Randomize.hh"
#include <iomanip>

namespace B4a
{

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void EventAction::BeginOfEventAction(const G4Event* /*event*/)
{
  // initialisation per event
  fEnergyIc = 0.;
  fEnergyVeto = 0.;
  fTrackLIc = 0.;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void EventAction::EndOfEventAction(const G4Event* event)
{
  // Accumulate statistics
  //

  // get analysis manager
  auto analysisManager = G4GenericAnalysisManager::Instance();

  // // fill histograms
  analysisManager->FillH1(0, fEnergyVeto);
  // // if (fEnergyVeto == 0 ){
  analysisManager->FillH1(1, fEnergyIc);
    // analysisManager->FillH1(2,  fEnergyIc / fTrackLIc);
  // }

  // // fill ntuple
  analysisManager->FillNtupleDColumn(0, fEnergyVeto);
  analysisManager->FillNtupleDColumn(1, fEnergyIc);
  // // analysisManager->FillNtupleDColumn(2, fEnergyIc / fTrackLIc);
  analysisManager->AddNtupleRow();

  // Print per event (modulo n)
  //
  auto eventID = event->GetEventID();
  auto printModulo = G4RunManager::GetRunManager()->GetPrintProgress();
  if ( ( printModulo > 0 ) && ( eventID % printModulo == 0 ) ) {
    G4cout << "---> End of event: " << eventID << G4endl;

    G4cout
       << "   Ic: energy / length: " << std::setw(7)
                                        << G4BestUnit(fEnergyIc / fTrackLIc,"Energy")
      << "   Ic: total energy: " << std::setw(7)
                                        << G4BestUnit(fEnergyIc ,"Energy")
       << "       total track length: " << std::setw(7)
                                        << G4BestUnit(fTrackLIc,"Length")
       << G4endl
       << "        Veto: total energy: " << std::setw(7)
                                        << G4BestUnit(fEnergyVeto,"Energy")
       << G4endl;
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

}
