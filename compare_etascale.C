{

TFile* file1 = new TFile("etascale_calculateEtaScaleFromICs_ABC_data_EEP.root");
TFile* file2 = new TFile("etascale_calculateEtaScaleFromICs_ABC_data_ExceptEEP_EEP.root");
//TFile* file2 = new TFile("fitzeescale_out_ABC_data.root");
//TFile* file1 = new TFile("etascale_calculateEtaScaleFromICs_ABC_inv_ExceptEEP_EEP.root");

//TFile* file2 = new TFile("etascale_calculateEtaScaleFromICs_ABC_empty_EEP.root");
//TFile* file2 = new TFile("etascaleratio_ABC_inv.root");

TH1D* h1 = (TH1D*)file1->Get("hEtaScaleRatio");
TH1D* h2 = (TH1D*)file2->Get("hEtaScaleRatio");
//TH1D* h2 = (TH1D*)file2->Get("hEtaScale");

h1->SetLineColor(2);
h1->SetMarkerColor(2);
h2->SetLineColor(4);
h2->SetMarkerColor(4);


h1->Draw();
h2->Draw("same");




}
