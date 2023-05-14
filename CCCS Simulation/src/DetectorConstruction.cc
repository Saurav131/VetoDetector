#include "DetectorConstruction.hh"
#include "G4Material.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4PVReplica.hh"
// #include "G4GlobalMagFieldMessenger.hh"
#include "G4AutoDelete.hh"
#include "G4GeometryManager.hh"
#include "G4PhysicalVolumeStore.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4SolidStore.hh"
#include "G4VisAttributes.hh"
#include "G4Colour.hh"
#include "G4SubtractionSolid.hh"
#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"

namespace B4
{


G4VPhysicalVolume* DetectorConstruction::Construct()
{
  // Define materials
  DefineMaterials();

  // Define volumes
  return DefineVolumes();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorConstruction::DefineMaterials()
{
  // Lead material defined using NIST Manager
  auto nistManager = G4NistManager::Instance();
  nistManager->FindOrBuildMaterial("G4_AIR");

  // Carbon 12
  G4double a;  // mass of a mole;
  G4double z;  // z=mean number of protons;
  G4double density , nel;
  new G4Material("carbon_12", z=6., a= 12*g/mole, density= 2.267*g/cm3);
  // new G4Material("carbon_12", z=6., a= 12*g/mole, density= 2*g/cm3);
  
	G4Element* C;
	G4Element* H;
  G4Material* Plastics;
  C = new G4Element("Carbon"  , "C", z=6., a= 12.01*g/mole);
  H = new G4Element("Hydrogen"  , "H", z=1., a= 1.008*g/mole);
  Plastics = new G4Material("Plastics",density=1.145*g/cm3, nel=2);
  Plastics->AddElement(H,8);
  Plastics->AddElement(C,10);

// IC material
  G4Element* F;
  G4Material* R14;
  F= new G4Element("Floride","F",z=9., a = 18.99*g/mole);
  R14 = new G4Material("R14",density=3.72*kg/m3,nel=2);
  R14->AddElement(C,1);
  R14->AddElement(F,4);


  // Print materials
  G4cout << *(G4Material::GetMaterialTable()) << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* DetectorConstruction::DefineVolumes()
{
  G4double shift =  500.*mm;
  G4double calorSize  = 100.*mm;
  G4double targetSize1        = 8.822*mm;
  // G4double targetSize1  = 4.411 *mm; 
  auto worldSizeX = 1.25* calorSize;
  auto worldSizeY = 0.75* calorSize;
  auto worldSizeZ  = 10 * calorSize;

  // Get materials
  auto WorldMaterial = G4Material::GetMaterial("G4_AIR");
  auto IcMaterial = G4Material::GetMaterial("R14");
  auto TargetMaterial = G4Material::GetMaterial("carbon_12");
  auto VetoMaterial = G4Material::GetMaterial("Plastics");


  if (  ! IcMaterial || ! VetoMaterial || ! TargetMaterial) {
    G4ExceptionDescription msg;
    msg << "Cannot retrieve materials already defined.";
    G4Exception("DetectorConstruction::DefineVolumes()",
      "MyCode0001", FatalException, msg);
  }

  //
  // World
  //
  auto worldS
    = new G4Box("World",           // its name
                 worldSizeX, worldSizeY, worldSizeZ); // its size

  auto worldLV
    = new G4LogicalVolume(
                 worldS,           // its solid
                 WorldMaterial,  // its material
                 "World");         // its name

  auto worldPV = new G4PVPlacement(nullptr,  // no rotation
    G4ThreeVector(),                         // at (0,0,0)
    worldLV,                                 // its logical volume
    "World",                                 // its name
    nullptr,                                 // its mother  volume
    false,                                   // no boolean operation
    0,                                       // copy number
    fCheckOverlaps);                         // checking overlaps

  //
  // Target


  // auto calorimeterS
  //   = new G4Box("Target",     // its name
  //                40*mm,19*mm, targetSize1); // its size

  // auto calorLV
  //   = new G4LogicalVolume(
  //                calorimeterS,     // its solid
  //                TargetMaterial,  // its material
  //                "Target");   // its name

  // new G4PVPlacement(nullptr,  // no rotation
  //   G4ThreeVector(0*m,0,shift),          // at (0,0,0)
  //   calorLV,                  // its lo  gical volume
  //   "Target",            // its name
  //   worldLV,                  // its mother  volume
  //   false,                    // no boolean operation
  //   0,                        // copy number
  //   fCheckOverlaps);          // checking overlaps

//   // //
//   // Veto
//   auto VetoS
//     = new G4Box("Veto",           // its name
//                  100*mm, 60*mm, 10*mm); // its size

//   auto hole_cavity
//     = new G4Box("Veto",40*mm+2*mm,19*mm+2*mm,10*mm+0.05*mm);

//   auto cavityS = new G4SubtractionSolid("Veto",VetoS,hole_cavity);
  
//   auto VetoLV
//     = new G4LogicalVolume(
//                     cavityS,           // its solid
//                     VetoMaterial,  // its material
//                     "Veto");         // its name

// fVetoPV = new G4PVPlacement(nullptr,  // no rotation
//                   G4ThreeVector(0*m,0,shift - 25*mm),          // at (0,0,0)
//                   VetoLV,                  // its logical volume
//                   "Veto",            // its name
//                   worldLV,                  // its mother  volume
//                   false,                    // no boolean operation
//                   0,                        // copy number
//                   fCheckOverlaps);   

// // Angle Detector
// G4Box* Detector
//     = new G4Box("Detector",           // its name
//                  100*mm, 60*mm, 0.000001*mm); // its size

  
// DetectorLV
//     = new G4LogicalVolume(
//                     Detector,           // its solid
//                     IcMaterial,  // its material
//                     "Detector");         // its name

// fDetectorPV = new G4PVPlacement(nullptr,  // no rotation
//                   G4ThreeVector(0*m,0,shift - 200*mm),          // at (0,0,0)
//                   DetectorLV,                  // its logical volume
//                   "Detector",            // its name
//                   worldLV,                  // its mother  volume
//                   false,                    // no boolean operation
//                   0,                        // copy number
//                   fCheckOverlaps);   



  // //
  // // IC 
  // //
  auto absorberS
    = new G4Box("IonChamber",40*mm,            // its name
                19*mm, 200*mm); // its size

  auto absorberLV
    = new G4LogicalVolume(
                 absorberS,        // its solid
                 IcMaterial, // its material
                 "IonChamber");          // its name

  fIcPV = new G4PVPlacement(nullptr,     // no rotation
    G4ThreeVector(0., 0. , shift + 215*mm)  // its position
    ,absorberLV,                                // its logical volume
    "IonChamber",                                    // its name
    worldLV,                                   // its mother  volume
    false,                                     // no boolean operation
    0,                                         // copy number
    fCheckOverlaps);                           // checking overlaps
  
  // fScoringVolume = VetoLV;
  
  return worldPV;
}



// void DetectorConstruction :: ConstructSDandField()
// {
// MySensitiveDetector *SD = new MySensitiveDetector("MySensitiveDetector");

// // logic_detector -> SetSensitiveDetector(SD);
// VetoLV -> SetSensitiveDetector(SD);

// }
}
