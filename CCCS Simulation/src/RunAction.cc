
#include "RunAction.hh"

#include "G4GenericAnalysisManager.hh"
#include "G4Run.hh"
#include "G4RunManager.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"

namespace B4
{

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

RunAction::RunAction()
{
  // set printing event number per each event
  G4RunManager::GetRunManager()->SetPrintProgress(1);

  // Create analysis manager
  // The choice of the output format is done via the specified
  // file extension.
  auto analysisManager = G4GenericAnalysisManager::Instance();

  // Create directories
  //analysisManager->SetHistoDirectoryName("histograms");
  //analysisManager->SetNtupleDirectoryName("ntuple");
  analysisManager->SetVerboseLevel(1);
  analysisManager->SetNtupleMerging(true);
    // Note: merging ntuples is available only with Root output

  // Book histograms, ntuple
  //

  // // Creating histograms
  analysisManager->CreateH1("Energy_Veto","Edep in  Veto", 1000, 0., 1000*MeV);
  analysisManager->CreateH1("Energy_Ic","Edep in Ic", 1000, 0., 100*MeV);
  // analysisManager->CreateH1("Angle","Angle", 1000, 0., 100*mrad);


  // analysisManager->CreateH1("Energy_Ic/Length_Ic","E / trackL in Ic Mev / cm ", 500, 0, 10);

  // // Creating ntuple
  // //
  analysisManager->CreateNtuple("B4", "Edep and TrackL");
  analysisManager->CreateNtupleDColumn("EVeto");
  analysisManager->CreateNtupleDColumn("EIc");
  // // analysisManager->CreateNtupleDColumn("LIc");
  analysisManager->FinishNtuple();

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void RunAction::BeginOfRunAction(const G4Run* run)
{
  auto analysisManager = G4GenericAnalysisManager::Instance();

  // Open an output file
  G4int runID = run->GetRunID();
  std::stringstream strRunID;
  strRunID << runID;
  
  G4String fileName = "Target"+strRunID.str()+".root";
  // Other supported output types:
  // G4String fileName1 = "B4.csv";

  analysisManager->OpenFile(fileName);
  // analysisManager->OpenFile(fileName1);





  G4cout << "Using " << analysisManager->GetType() << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void RunAction::EndOfRunAction(const G4Run* /*run*/)
{
  // print histogram statistics
  //
  auto analysisManager = G4GenericAnalysisManager::Instance();
  // if ( analysisManager->GetH1(1) ) {
  //   G4cout << G4endl << " ----> print histograms statistic ";
  //   if(isMaster) {
  //     G4cout << "for the entire run " << G4endl << G4endl;
  //   }
  //   else {
  //     G4cout << "for the local thread " << G4endl << G4endl;
  //   }

  //   G4cout << " EAbs : mean = "
  //      << G4BestUnit(analysisManager->GetH1(0)->mean(), "Energy")
  //      << " rms = "
  //      << G4BestUnit(analysisManager->GetH1(0)->rms(),  "Energy") << G4endl;

  //   G4cout << " EGap : mean = "
  //      << G4BestUnit(analysisManager->GetH1(1)->mean(), "Energy")
  //      << " rms = "
  //      << G4BestUnit(analysisManager->GetH1(1)->rms(),  "Energy") << G4endl;

  //   G4cout << " LAbs : mean = "
  //     << G4BestUnit(analysisManager->GetH1(2)->mean(), "Length")
  //     << " rms = "
  //     << G4BestUnit(analysisManager->GetH1(2)->rms(),  "Length") << G4endl;

    // G4cout << " LGap : mean = "
    //   << G4BestUnit(analysisManager->GetH1(3)->mean(), "Length")
    //   << " rms = "
    //   << G4BestUnit(analysisManager->GetH1(3)->rms(),  "Length") << G4endl;
  // }

  // save histograms & ntuple
  //
  analysisManager->Write();
  analysisManager->CloseFile();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

}
