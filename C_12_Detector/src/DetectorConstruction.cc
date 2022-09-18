
#include "DetectorConstruction.hh"
#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4RotationMatrix.hh"
#include "G4Cons.hh"
#include "G4Orb.hh"
#include "G4Sphere.hh"
#include "G4Trd.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"

// namespace B1
// {

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DetectorConstruction::DetectorConstruction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DetectorConstruction::~DetectorConstruction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* DetectorConstruction::Construct()
{
  // Get nist material manager
  G4NistManager* nist = G4NistManager::Instance();

  // Envelope parameters
  //
  G4double env_sizeXY = 20*cm, env_sizeZ = 50*cm;
  G4Material* env_mat = nist->FindOrBuildMaterial("G4_AIR");
  // 
  // Option to switch on/off checking of volumes overlaps
  //
  G4bool checkOverlaps = true;
  //
  // World
  //
  G4double world_sizeXY = 1.2*env_sizeXY;
  G4double world_sizeZ  = 1.2*env_sizeZ;
  G4Material* world_mat = nist->FindOrBuildMaterial("G4_AIR");

  G4Box* solidWorld =
    new G4Box("World",                       //its name
       0.5*world_sizeXY, 0.5*world_sizeXY, 0.5*world_sizeZ);     //its size

  G4LogicalVolume* logicWorld =
    new G4LogicalVolume(solidWorld,          //its solid
                        world_mat,           //its material
                        "World");            //its name

  G4VPhysicalVolume* physWorld =
    new G4PVPlacement(0,                     //no rotation
                      G4ThreeVector(),       //at (0,0,0)
                      logicWorld,            //its logical volume
                      "World",               //its name
                      0,                     //its mother  volume
                      false,                 //no boolean operation
                      0,                     //copy number
                      checkOverlaps);        //overlaps checking


  // Envelope
  
  G4Box* solidEnv =
    new G4Box("Envelope",                    //its name
        0.5*env_sizeXY, 0.5*env_sizeXY, 0.5*env_sizeZ); //its size =(10,10,15)

  G4LogicalVolume* logicEnv =
    new G4LogicalVolume(solidEnv,            //its solid
                        env_mat,             //its material
                        "Envelope");         //its name

  new G4PVPlacement(0,                       //no rotation
                    G4ThreeVector(),         //at (0,0,0)
                    logicEnv,                //its logical volume
                    "Envelope",              //its name
                    logicWorld,              //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking
//target material
  G4double a , z , density;
  
  G4Material* target_mat = new G4Material("carbon_12",z=6.,a= 12*g/mole, density= 2.267*g/cm3);

  G4Box *solid_target = new G4Box("target",5*cm,5*cm,0.5*cm);
  
  G4LogicalVolume* logic_target = new G4LogicalVolume(solid_target,target_mat,"target");

   new G4PVPlacement(0,
   G4ThreeVector(0*m,0,0*cm),
  logic_target
  ,"target"
  ,logicEnv,
  false,
   0 
   ,true);

  //Ic chamber material


      G4double density2 = 27.*mg/cm3;
      G4double temperature = 325.*kelvin;
      G4double pressure = 50.*atmosphere;
      G4Material* CO2 = new G4Material("CO2", density2, 2 ,kStateGas, temperature, pressure);
      CO2->AddElement(nist->FindOrBuildElement("C"),1);
      CO2->AddElement(nist->FindOrBuildElement("O"),2);

  // IC chamber construction

    G4RotationMatrix rotm  = G4RotationMatrix();
    rotm.rotateY(90.*deg);
    rotm.rotateZ(0.*deg);
    G4ThreeVector  position= G4ThreeVector(0.,0.,-15.5*cm);
    G4ThreeVector  position2= G4ThreeVector(0.,0.,15.5*cm);
    
    G4Transform3D transform = G4Transform3D(rotm,position);
    G4Transform3D transform2 = G4Transform3D(rotm,position2);

  G4VSolid* detectSolid = new G4Tubs("chamber",0. , 4.5*cm ,4.5*cm, 0.0*deg, 360.0*deg);
  logic_ic = new G4LogicalVolume(detectSolid, CO2, "chamber");
  new G4PVPlacement(transform, logic_ic, "chamber", logicEnv,
                    false, 0, checkOverlaps);


  new G4PVPlacement(transform2, logic_ic, "detectPhysical2", logicEnv,
                    false, 0, checkOverlaps);

  // plastic cavity
    G4Box *solid_cavity = new G4Box("cavity",5*cm,5*cm,0.5*cm);
  
  G4LogicalVolume* logic_cavity = new G4LogicalVolume(solid_cavity,target_mat,"cavity");

   new G4PVPlacement(0,
   G4ThreeVector(0*m,0,-5*cm),
  logic_cavity
  ,"cavity"
  ,logicEnv,
  false,
   0 
   ,true);

    G4Box *solid_cavity_inner = new G4Box("cavity_inner",2.5*cm,2.5*cm,0.5*cm);
  
  G4LogicalVolume* logic_cavity_inner = new G4LogicalVolume(solid_cavity_inner,env_mat,"cavity_inner");

   new G4PVPlacement(0,
   G4ThreeVector(0*m,0,-5*cm),
  logic_cavity_inner
  ,"cavity_inner"
  ,logicEnv,
  false,
   1 
   ,true);
  //   //detectors
  // G4Box *solid_detector = new G4Box("solid_detector",0.2*cm,0.2*cm,0.2*cm);
  // logic_detector = new G4LogicalVolume(solid_detector,target_mat,"logic_detector");
  // for (G4int i=0; i < 30 ; i++)
  // {
  //   for (G4int j=0; j < 30 ; j++)
  //   {
  //     new G4PVPlacement(0,
  //     G4ThreeVector(-7*cm+i*.5*cm,-7*cm+j*0.5*cm  ,10*cm),
  //     logic_detector
  //     ,"physical_detector"
  //     ,logicWorld,
  //     false,
  //     0 
  //     ,true);
  //   }

  // }

  // Set Shape2 as scoring volume
  
  fScoringVolume = logic_ic;

  //
  //always return the physical World
  //
  return physWorld;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......



void DetectorConstruction :: ConstructSDandField()
{
MySensitiveDetector *SD = new MySensitiveDetector("SensitiveDetector");

// logic_detector -> SetSensitiveDetector(SD);
logic_ic -> SetSensitiveDetector(SD);

}
// }