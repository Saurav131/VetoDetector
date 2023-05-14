#include "PrimaryGeneratorAction.hh"
#include "G4RunManager.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"
#include "G4IonTable.hh"

#include "G4UnitsTable.hh"


namespace B4
{

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

PrimaryGeneratorAction::PrimaryGeneratorAction()
{
  G4int nofParticles = 1;
  fParticleGun = new G4ParticleGun(nofParticles);

  // default particle kinematic
  //
  auto particleDefinition
    = G4ParticleTable::GetParticleTable()->FindParticle("gamma");
  fParticleGun->SetParticleDefinition(particleDefinition);
  fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0.,0.,1.));
  // fParticleGun->SetParticleEnergy(1000.*MeV);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
  delete fParticleGun;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
  // This function is called at the begining of event

  // In order to avoid dependence of PrimaryGeneratorAction
  // on DetectorConstruction class we get world volume
  // from G4LogicalVolumeStore
  //
  G4double worldZHalfLength = 0.;
  auto worldLV = G4LogicalVolumeStore::GetInstance()->GetVolume("World");

  // Check that the world volume has box shape
  G4Box* worldBox = nullptr;
  if (  worldLV ) {
    worldBox = dynamic_cast<G4Box*>(worldLV->GetSolid());
  }

  if ( worldBox ) {
    worldZHalfLength = worldBox->GetZHalfLength();
  }
  else  {
    G4ExceptionDescription msg;
    msg << "World volume of box shape not found." << G4endl;
    msg << "Perhaps you have changed geometry." << G4endl;
    msg << "The gun will be place in the center.";
    G4Exception("PrimaryGeneratorAction::GeneratePrimaries()",
      "MyCode0002", JustWarning, msg);
  }


  //Set definition of ION beam for C12:
	G4int Z=6;
	G4int A=12;
	G4double ionCharge = 0;
	G4double excitEnergy = 0*keV;
	
	G4ParticleDefinition* ion = G4IonTable::GetIonTable()->GetIon(Z,A,excitEnergy);
	fParticleGun->SetParticleDefinition(ion);
	fParticleGun->SetParticleCharge(ionCharge);

// gaussian distribution of beam 
  G4double x0 = 0;
  G4double x = x0;
  G4double y0 = 0;
  G4double y = y0;
  G4double z = -900*mm;
  G4double xx = 7.5*mm  ;
  G4double yy = 5*mm ;
  if (xx > 0.0)
    {
      x += G4RandGauss::shoot(x0 , xx);
    }  
  if (yy > 0.0)
    {
      y += G4RandGauss::shoot(y0 , yy);
    } 
  fParticleGun->SetParticlePosition(G4ThreeVector(x,y,z));
  

  // angle in the beam trajectory
  G4double angle = 75. ;
  G4double phi = angle * (G4UniformRand() - 0.5 ) *mrad ;
  G4double Theta = angle * (G4UniformRand()- 0.5) *mrad ;
  
  G4cout
       << "  phi: " << std::setw(7)
                                        << G4BestUnit(phi,"Angle")
      << "   Theta: " << std::setw(7)
                                        << G4BestUnit(Theta ,"Angle")
       << G4endl; 

  fParticleGun -> SetParticleMomentumDirection(G4ThreeVector(sin(Theta)*cos(phi),
							    sin(Theta)*sin(phi), cos(Theta)));

  fParticleGun->GeneratePrimaryVertex(anEvent);
} 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

}
