{
  gROOT->Reset();
  gROOT->SetStyle("Bold");
  gStyle->SetPalette(kOcean);
  gStyle->SetOptStat(0);
  // Draw histos filled by Geant4 simulation
  //

  // Open file filled by Geant4 simulation
  TFile f("./with_target/B41.root");

  // Create a canvas and divide it into 2x2 pads
  TCanvas* c1 = new TCanvas("c1", "", 1500, 800);
  c1->Divide(2,2);

  // Get ntuple
  TNtuple* ntuple = (TNtuple*)f.Get("B4");

  c1->cd(1);
  gPad->SetLogy(1);
  TH1F * hb = new TH1F("hb","", 400, 0, 25);
  TH1F * ha = new TH1F("ha","", 400, 0, 25);
  // TH1F * hc = new TH1F("hc","", 400, 0, 25);
  ntuple->Draw("EIc>>ha(400,0,25)");
  ntuple->Draw("EIc>>hb(400,0,25)","EVeto< 5","same");
  // ntuple->Draw("EIc>>hc(400,0,25)","EVeto>10","same");
  hb->SetLineColor(kRed-4);
  // hc->SetLineColor(kGreen-4);
  auto legend3 = new TLegend(0.25,0.85,0.9,0.99);
  legend3->SetHeader("The Energy Depostion In Ionization Chamber","C"); // option "C" allows to center the header
  legend3->AddEntry(ha,"All events","l");
  legend3->AddEntry(hb,"For event with EVeto<5 ","l");
  // legend3->AddEntry(hc,"For event with EVeto>10 ","l");
  legend3->Draw();

  c1->cd(2);
  gPad->SetLogy(1);
  TH1F * ha1 = new TH1F("ha1","", 400, 0, 25);
  ntuple->Draw("EIc>>ha1(400,0,25)");
  auto legend = new TLegend(0.25,0.85,0.9,.99);
  legend->SetHeader("For All Events for 1000 MeV/u","C"); // option "C" allows to center the header
  legend->AddEntry(ha1,"All events","l");
  legend->Draw();
  
  c1->cd(3);
  gPad->SetLogy(1);
  TH1F * hb1 = new TH1F("hb1","", 400, 0, 25);
  ntuple->Draw("EIc>>hb1(400,0,25)","EVeto<5");
  auto legend1 = new TLegend(0.25,0.85,0.9,.99);
  legend1->SetHeader("Acectable events","C"); // option "C" allows to center the header
  legend1->AddEntry(hb1,"For event with EVeto<5 ","l");
  legend1->Draw();


  c1->cd(4);
  gPad->SetLogy(1);
  TH1F * hc1 = new TH1F("hc1","", 400, 0, 25);
  ntuple->Draw("EIc>>hc(400,0,25)","EVeto>5");
  auto legend2 = new TLegend(0.25,0.85,0.9,.99);
  legend2->SetHeader("Rejected event","C"); // option "C" allows to center the header
  legend2->AddEntry(hc1,"For event with EVeto>5 ","l");
  legend2->Draw();
  c1->Print("./with_target/EIc.png");


}