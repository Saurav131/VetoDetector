# Geant4 Simulation of a Veto Detector for Charge-Changing Cross-Section Measurements

A computational nuclear physics project investigating the response of a veto detector for measuring the charge-changing cross section (CCCS) of carbon-12 (^12C) beams incident on a carbon target.

Developed as an M.Sc. Physics thesis at **IIT (ISM) Dhanbad (2023)**, this project uses Geant4 to simulate particle transport, detector energy deposition, and the effect of veto selection on charge-changing cross-section measurements.

## Scientific Motivation

Charge-changing cross sections provide information about nuclear structure and charge-distribution radii. In transmission experiments, unreacted beam particles can contribute to the measured event count and affect the cross-section estimate.

This project investigates a veto-detector configuration designed to identify events that should be excluded from the measurement. The detector response is studied at different incident beam energies, and the resulting cross-section estimates are compared with theoretical predictions from the Glauber model.

## Project Objectives

- Simulate carbon-12 beam interactions with a carbon target using Geant4.
- Model the ionization chamber and veto-detector response.
- Study detector energy deposition at different beam energies.
- Analyse energy-deposition distributions to identify unreacted and charge-changing events.
- Evaluate the effect of veto selection on calculated charge-changing cross sections.
- Compare simulated cross-section estimates with finite-range Glauber-model predictions.

## Implementation

### Geant4 Detector Simulation

The simulation is implemented in C++ using Geant4. It includes detector geometry, primary-ion generation, event handling, and energy-deposition scoring.

The primary generator defines a carbon-12 ion beam with a Gaussian spatial distribution and a small angular spread. Energy deposition in the ionization chamber and veto detector is recorded for subsequent analysis.

### Event-Level Data Collection

The simulation records energy deposition in detector volumes and writes the results to ROOT-compatible output files. Histograms and ntuples are used to study detector response and support downstream analysis.

### Cross-Section Analysis

Energy-deposition distributions are analysed to identify the dominant peak associated with unreacted beam particles. A Gaussian fit characterizes the peak and defines an event-selection range.

Transmission ratios obtained with the target present and absent are used to calculate the charge-changing cross section. Results are compared across configurations with and without the veto detector and veto selection.

## Results and Findings

- Studied veto-detector energy deposition at incident beam energies of 100, 200, 300, 600, and 1000 MeV/u.
- Compared simulated energy deposition with energy-loss estimates from WebAtima, observing larger discrepancies at the lowest studied energy.
- Calculated charge-changing cross sections for different veto-detector configurations.
- Observed improved agreement with finite-range Glauber-model predictions when the veto detector was included.

These results support the use of veto selection to improve charge-changing cross-section measurements within the simulated setup.

## Repository Structure

```text
VetoDetector/
├── CCCS Simulation/
│   ├── CMakeLists.txt
│   ├── GNUmakefile
│   ├── exampleB4a.cc
│   ├── include/
│   ├── src/
│   ├── run1.mac
│   ├── run2.mac
│   ├── vis.mac
│   ├── plotHisto.C
│   └── plotNtuple.C
├── Graphs/
│   └── Ionization chamber.c
├── Final Thesis - Saurav Mittal.pdf
└── Thesis_Presentation.pptx
```

- **CCCS Simulation:** Geant4 simulation source code, detector construction, event actions, and run macros.
- **Graphs:** Additional analysis code.
- **Final Thesis:** Detailed methodology, calculations, results, and conclusions.
- **Thesis Presentation:** Summary of the research project.

## Software and Dependencies

- C++
- Geant4
- CMake
- CERN ROOT
- WebAtima for reference energy-loss calculations

A compatible Geant4 installation is required to build and run the simulation. ROOT is required for the associated ROOT-based analysis workflows.

## Building the Simulation

From the repository root, configure and build the project:

```bash
cmake -S "CCCS Simulation" -B build
cmake --build build -j
```

The default configuration uses Geant4 user-interface and visualization components, so the corresponding drivers must be available in your Geant4 installation.

**Note:** Additional files or configuration changes may be required to reproduce the original simulation. Consult the thesis and source files for details.

## Academic Reference

**Thesis:** *Geant4 Simulation of the Response of a Veto Detector with Various Beam Energies for the Measurement of Charge-Changing Cross-Section (CCCS) of ^12C on a Carbon Target.*

M.Sc. Physics dissertation, Indian Institute of Technology (Indian School of Mines), Dhanbad, May 2023.

## Author

Saurav Mittal

- [GitHub](https://github.com/Saurav131)
- [LinkedIn](https://www.linkedin.com/in/mittalsaurav/)
