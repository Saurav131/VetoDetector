#include "SteppingAction.hh"
#include "EventAction.hh"
#include "DetectorConstruction.hh"

#include "G4Step.hh"
#include "G4RunManager.hh"

using namespace B4;

namespace B4a
{

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

SteppingAction::SteppingAction(const DetectorConstruction* detConstruction,
                               EventAction* eventAction)
  : fDetConstruction(detConstruction),
    fEventAction(eventAction)
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void SteppingAction::UserSteppingAction(const G4Step* step)
{
// Collect energy and track length step by step

  // get volume of the current step
  auto volume = step->GetPreStepPoint()->GetTouchableHandle()->GetVolume();

  // energy deposit
  auto edep = step->GetTotalEnergyDeposit();

  // step length
  G4double stepLength = 0.;

  // if ( step->GetTrack()->GetDefinition()->GetPDGCharge() != 0. ) {
  //   stepLength = step->GetStepLength();
  // }
  stepLength = step->GetStepLength();

  // G4Track *track = step->GetTrack();  

  // G4ThreeVector direction = track-> GetMomentumDirection();

  // G4cout << "events Direction : " << direction[0] << G4endl;

  if ( volume == fDetConstruction->GetVetoPV() ) {
    fEventAction->AddVeto(edep);
  }

  if ( volume == fDetConstruction->GetIcPV() ) {
    fEventAction->AddIc(edep,stepLength);
  }

}

}
