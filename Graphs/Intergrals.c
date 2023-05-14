
{
  gROOT->Reset();
  gROOT->SetStyle("Bold");
  gStyle->SetPalette(kOcean);

  TFile *file0=new TFile("./with_target/B42.root");
  TCanvas* c1 = new TCanvas("c1", "", 1500, 800);
  c1->cd();
  gStyle->SetOptStat(0);
  TH1F *h = (TH1F*)file0->Get("Energy_Veto;1");
  // h->Divide(Total);
  h->Draw("hist");

  int bin0 = h->GetXaxis()->FindBin(5);
  int bin1 = h->GetXaxis()->FindBin(180);
  int Back = h->Integral(bin0,bin1);
  cout<< bin0 <<endl;
  cout<<bin1 <<endl;
  cout<<Back<<endl;

  int bin2 = h->GetXaxis()->FindBin(1);
  int bin3 = h->GetXaxis()->FindBin(5);
  int through = h->Integral(bin2,bin3);
  cout<< bin2 <<endl;
  cout<<bin3 <<endl;
  cout<<through<<endl;

  int bin4 = h->GetXaxis()->FindBin(180);
  int bin5 = h->GetXaxis()->FindBin(205);
  int Direct = h->Integral(bin4,bin5);
  cout<< bin4 <<endl;
  cout<<bin5 <<endl;
  cout<<Direct<<endl;

  int bin6 = h->GetXaxis()->FindBin(1);
  int bin7 = h->GetXaxis()->FindBin(1000);
  int Total = h->Integral(bin6,bin7);
  cout<<Total<<endl;

   auto legend = new TLegend(0.25,0.7,0.9,0.99);

   legend->SetHeader("The Veto Energy Deposition for 4gm/cm3","C"); // option "C" allows to center the header
   legend->AddEntry(h,std::string("The backscattering event integral is ") +Back,"l");
   legend->AddEntry(h,std::string("The integral of event that passed through veto and didnot backscatter is ") +through,"l");
   legend->AddEntry(h,std::string("The Event which hit Veto Directly ") + Direct ,"l");
   legend->Draw();
  c1->Print("./with_target/Integral.png");

}
