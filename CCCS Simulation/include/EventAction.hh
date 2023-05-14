#ifndef B4aEventAction_h
#define B4aEventAction_h 1

#include "G4UserEventAction.hh"
#include "globals.hh"

namespace B4a
{

/// Event action class
///
/// It defines data members to hold the energy deposit and track lengths
/// of charged particles in Absober and Gap layers:
/// - fEnergyAbs, fEnergyGap, fTrackLAbs, fTrackLGap
/// which are collected step by step via the functions
/// - AddAbs(), AddGap()

class EventAction : public G4UserEventAction
{
  public:
    EventAction() = default;
    ~EventAction() override = default;

    void  BeginOfEventAction(const G4Event* event) override;
    void    EndOfEventAction(const G4Event* event) override;

    void AddIc(G4double de, G4double dl);
    void AddVeto(G4double de);

  private:
    G4double  fEnergyIc = 0.;
    G4double  fEnergyVeto = 0.;
    G4double  fTrackLIc = 0.;
};

// inline functions
inline void EventAction::AddVeto(G4double de) {
  fEnergyVeto += de;
}
inline void EventAction::AddIc(G4double de, G4double dl) {
  fEnergyIc += de;
  fTrackLIc += dl;
}

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif


