{
  gROOT->Reset();
  gROOT->SetStyle("Bold");
  gStyle->SetPalette(kOcean);

  // Draw histos filled by Geant4 simulation
  // Open file filled by Geant4 simulation
  TFile *file0=new TFile("./without_target/B40.root");
  TFile *file1=new TFile("./without_target/B41.root");
  TFile *file2=new TFile("./without_target/B42.root");

  // Create a canvas and divide it into 2x2 pads
  TCanvas* c1 = new TCanvas("c1", "", 1500, 800);
  c1->cd();
  gStyle->SetOptStat(0);
  
  
  
  // Get ntuple
  TH1F *hist0 = (TH1F*)file0->Get("Energy_Veto;1");
  TH1F *hist1 = (TH1F*)file1->Get("Energy_Veto;1");
  TH1F *hist2 = (TH1F*)file2->Get("Energy_Veto;1");
  hist0->SetLineColor(kGreen);
  hist0->SetFillStyle(3001);
  // hist0->SetFillColor(kGreen-10);
  hist0->SetLineWidth(1);
  hist1->SetLineWidth(1);
  hist2->SetLineWidth(1);
  hist1->SetLineColor(kBlue);
  hist1->SetFillStyle(3001);
  // hist1->SetFillColor(kCyan-10);  
  hist2->SetLineColor(kRed);
  hist2->SetFillStyle(3001);
  // hist2->SetFillColor(kRed-10);
  // void SetHistLineColor(Color_t color = 1);
  gPad->SetLogy(1);
  hist0->Draw("hist");
  hist1->Draw("histsame");
  hist2->Draw("histsame");

   auto legend = new TLegend(0.5,0.7,0.9,0.9);
   legend->SetHeader("The Energy Depostion In veto Detector for 4gm/cm3","C"); // option "C" allows to center the header
   legend->AddEntry(hist0,"600 MeV/u Beam Energy","l");
   legend->AddEntry(hist1,"800 MeV/u Beam Energy","l");
   legend->AddEntry(hist2,"1000 MeV/u Beam Energy","l");
   legend->Draw();
  c1->Print("./with_target/Combine EVeto.png");

}
