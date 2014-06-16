{
TFile* file1 = new TFile("drawMee_out_ABC_MC_EEN.root");

TH1D* h1 = (TH1D*)file1->Get("hMeeRegElec");
TH1D* h2 = (TH1D*)file1->Get("hMeeRegElecEtaScale");
TH1D* h3 = (TH1D*)file1->Get("hMeeRegElecEtaScaleReCalib");

TLegend* lg = new TLegend(0.6, 0.7, 0.9, 0.9);
lg->AddEntry(h1, "Reg", "pl");
lg->AddEntry(h2, "Reg+EtaScale", "pl");
lg->AddEntry(h3, "Reg+EtaScale+Calib", "pl");


h3->Draw();
h2->Draw("same");
h1->Draw("same");
lg->Draw("same");

}
