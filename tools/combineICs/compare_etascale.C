{

TFile* file1 = new TFile(
"productICfile_EtaScale.root"
);

TFile* file2 = new TFile(
"productICfile_EtaScale_prodIC_EtaScale.root"
);

//TH1D* h1 = (TH1D*)file1->Get("hEtaScaleRatio");
TH1D* h1 = (TH1D*)file1->Get("hEtaScale");
//TH1D* h2 = (TH1D*)file2->Get("hEtaScaleRatio");
TH1D* h2 = (TH1D*)file2->Get("hEtaScale");

h1->SetLineColor(2);
h1->SetMarkerColor(2);
h2->SetLineColor(4);
h2->SetMarkerColor(4);

TLegend* lg = new TLegend(0.6,0.7,0.9,0.9);
lg->AddEntry(h1, "Before", "pl");
lg->AddEntry(h2, "After", "pl");

h1->Draw();
h2->Draw("same");
lg->Draw();



}
