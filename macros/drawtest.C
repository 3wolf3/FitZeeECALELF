{
  TFile* file1 = TFile::Open("/afs/cern.ch/user/l/lcorpe/work/public/ECALELF/ntuple_160615.root");
  TFile* file2 = TFile::Open("root://eoscms//eos/cms/store/group/dpg_ecal/alca_ecalcalib/ecalelf/heli/ntuple/ntuple_DYJets-Summer12-START53-HighEtaSkim-runDependent-Extra-V4-2012D.root");

  char tagout[] = "checkNtuple";

  TTree* tree1 = (TTree*)file1->Get("selected");
  TTree* tree2 = (TTree*)file2->Get("selected");

  TH1D* h1;
  TH1D* h2;
  TLegend* lg;

  char name[3000];
  TCanvas* plots = new TCanvas("plots", "plots", 600, 600);
  sprintf(name, "plots_%s.ps[", tagout);
  plots->Print(name);


  // InvMass_SC
  h1 = new TH1D("h1", "h1", 100, 70, 120);
  h2 = new TH1D("h2", "h2", 100, 70, 120);
  h1->Sumw2();
  h2->Sumw2();
  tree1->Draw("invMass_SC>>h1");  
  tree2->Draw("invMass_SC>>h2");  
  h2->Scale(h1->Integral()/h2->Integral());
  h1->SetName("InvMass_SC1");
  h2->SetName("InvMass_SC2");
  h1->SetLineColor(2);
  h2->SetLineColor(4);
  h1->SetMarkerColor(2);
  h2->SetMarkerColor(4);
  h1->GetYaxis()->SetTitle("A.U.");
  h2->GetYaxis()->SetTitle("A.U.");
  h1->GetXaxis()->SetTitle("InvMass_SC (GeV)");
  h2->GetXaxis()->SetTitle("InvMass_SC (GeV)");
  
  lg = new TLegend(0.5, 0.6, 0.8, 0.9);
  lg->SetName("lg_InvMass_SC");
  lg->AddEntry(h1, "New Ntuple", "pl");
  lg->AddEntry(h2, "Old Ntuple", "pl");
  
  plots->Clear();
  h2->Draw("hist");
  h1->Draw("hist same");
  lg->Draw();
  sprintf(name, "plots_%s.ps", tagout);
  plots->Print(name);
  plots->Clear();


  // InvMass_SC
  h1 = new TH1D("h1", "h1", 100, 0, 100);
  h2 = new TH1D("h2", "h2", 100, 0, 100);
  h1->Sumw2();
  h2->Sumw2();
  tree1->Draw("nPV>>h1");  
  tree2->Draw("nPV>>h2");  
  h2->Scale(h1->Integral()/h2->Integral());
  h1->SetName("nPV1");
  h2->SetName("nPV2");
  h1->SetLineColor(2);
  h2->SetLineColor(4);
  h1->SetMarkerColor(2);
  h2->SetMarkerColor(4);
  h1->GetYaxis()->SetTitle("A.U.");
  h2->GetYaxis()->SetTitle("A.U.");
  h1->GetXaxis()->SetTitle("nPV");
  h2->GetXaxis()->SetTitle("nPV");
  
  lg = new TLegend(0.5, 0.6, 0.8, 0.9);
  lg->SetName("lg_nPV");
  lg->AddEntry(h1, "New Ntuple", "pl");
  lg->AddEntry(h2, "Old Ntuple", "pl");
  
  plots->Clear();
  h2->Draw("hist");
  h1->Draw("hist same");
  lg->Draw();
  sprintf(name, "plots_%s.ps", tagout);
  plots->Print(name);
  plots->Clear();


  ///
  // end 
  sprintf(name, "plots_%s.ps]", tagout);
  plots->Print(name);


  sprintf(name, ".! ps2pdf plots_%s.ps", tagout);
  gROOT->ProcessLine(name);
 

}
