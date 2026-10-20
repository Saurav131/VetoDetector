# Geant4 Simulation of a Veto Detector for Charge-Changing Cross-Section Measurements

A computational nuclear physics project investigating the response of a veto detector for measuring the charge-changing cross section (CCCS) of carbon-12 (\(^{12}\mathrm{C}\)) beams incident on a carbon target.

Developed as an M.Sc. Physics thesis at **IIT (ISM) Dhanbad (2023)**, this project uses Geant4 to simulate particle transport, detector energy deposition, and the effect of veto selection on charge-changing cross-section measurements.

## Scientific Motivation

Charge-changing cross sections provide information about nuclear structure and charge-distribution radii. In transmission experiments, beam particles that do not interact with the target can still contribute to the measured event count, potentially affecting the cross-section estimate.

This project investigates a veto-detector configuration designed to identify events that should be excluded from the measurement. The detector response is studied at different incident beam energies, and the resulting cross-section estimates are compared with theoretical predictions from the Glauber model.

## Project Objectives

- Simulate the interaction of carbon-12 beams with a carbon target using Geant4.
- Model the ionization chamber and veto-detector response.
- Study energy deposition in the detector as a function of beam energy.
- Analyse energy-deposition distributions to identify unreacted and charge-changing events.
- Evaluate the effect of veto selection on calculated charge-changing cross sections.
- Compare simulated cross-section estimates with finite-range Glauber-model predictions.

## Implementation

### Geant4 detector simulation

The simulation is implemented in C++ using Geant4. It includes detector geometry, primary-ion generation, event handling, and energy-deposition scoring.

The primary generator defines a carbon-12 ion beam with a Gaussian spatial distribution and a small angular spread. The detector simulation records energy deposition in the ionization chamber and veto detector for subsequent analysis.

### Event-level data collection

The simulation records energy deposition in the detector volumes and writes the results to ROOT-compatible output files. Histograms and ntuples are used to study the detector response and support downstream analysis.

### Cross-section analysis

The analysis uses energy-deposition distributions to identify the dominant peak associated with unreacted beam particles. A Gaussian fit is used to characterize the peak and define an event-selection range.

The transmission ratios obtained with the target present and absent are then used to calculate the charge-changing cross section. Results are compared across configurations with and without the veto detector and veto selection.

## Results and Findings

The thesis reports the following findings:

- The veto detector's energy deposition was studied at incident beam energies of 100, 200, 300, 600, and 1000 MeV/u.
- The simulated energy deposition was compared with energy-loss estimates from WebAtima, with larger discrepancies observed at the lowest studied energy.
- Charge-changing cross sections were calculated for different veto-detector configurations.
- Including the veto detector improved agreement between the calculated cross sections and finite-range Glauber-model predictions.

These findings support the use of veto selection to improve charge-changing cross-section measurements within the simulated setup.

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

- **`CCCS Simulation/`** — Geant4 simulation source code, detector construction, event actions, and run macros.
- **`Graphs/`** — Additional analysis code.
- **Thesis PDF** — Full methodology, calculations, results, and conclusions.
- **Thesis presentation** — Summary of the research project.

## Software and Dependencies

- **C++**
- **Geant4** — Particle transport and detector simulation
- **CMake** — Build configuration
- **CERN ROOT** — Analysis of simulation output and histograms
- **WebAtima** — Reference energy-loss calculations used in the thesis

The simulation requires a compatible Geant4 installation. ROOT is needed for the associated ROOT-based analysis workflows.

## Building the Simulation

From the repository root, configure and build the Geant4 project:

```bash
cmake -S "CCCS Simulation" -B build
cmake --build build -j
```

The project uses Geant4's user-interface and visualization components by default. A compatible Geant4 installation with the required UI and visualization drivers is therefore needed for the default configuration.

**Note:** The repository indicates that additional files may be required to reproduce the original simulation. Review the thesis and configuration files before running the complete workflow.

## Academic Reference

**Thesis:** *Geant4 Simulation of the Response of a Veto Detector with Various Beam Energies for the Measurement of Charge-Changing Cross-Section (CCCS) of \(^{12}\mathrm{C}\) on a Carbon Target.*

M.Sc. Physics dissertation, Indian Institute of Technology (Indian School of Mines), Dhanbad, May 2023.

## Author

Saurav Mittal

[GitHub](https://github.com/Saurav131) · [LinkedIn](https://www.linkedin.com/in/mittalsaurav/)
