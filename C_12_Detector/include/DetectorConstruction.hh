
#ifndef B1DetectorConstruction_h
#define B1DetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"
#include "detector.hh"

class G4VPhysicalVolume;
class G4LogicalVolume;

/// Detector construction class to define materials and geometry.

// namespace B1
// {

class DetectorConstruction : public G4VUserDetectorConstruction
{
  public:
    DetectorConstruction();
    ~DetectorConstruction() override;

    G4VPhysicalVolume* Construct() override;

    //G4LogicalVolume* GetScoringVolume() const { return fScoringVolume; }
    
   
  // private:
  // 	G4LogicalVolume *logic_detector;
  //   virtual void ConstructSDandField();

  private:
  // we add logical volume of our detector here so that sensitive volume can refer to this logical volume outside of construct function
    G4LogicalVolume *logic_ic;
    // virtual because it is predefined
    virtual void ConstructSDandField();
    protected:
    G4LogicalVolume* fScoringVolume = nullptr;
};

// }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
