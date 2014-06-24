{
TFile* file1 = new TFile("drawMee_out_data_ZSkim_2012AB_EEP.root");

TH1D* h1 = (TH1D*)file1->Get("hMeeSC");
TH1D* h2 = (TH1D*)file1->Get("hMeeReg");
TH1D* h3 = (TH1D*)file1->Get("hMeeRegEtaScale");
TH1D* h4 = (TH1D*)file1->Get("hMeeRegEtaScaleNewICs");

h1->SetMarkerColor(2);
h1->SetLineColor(2);


TLegend* lg = new TLegend(0.6, 0.7, 0.9, 0.9);
lg->AddEntry(h1, "SC", "pl");
//lg->AddEntry(h2, "Reg", "pl");
//lg->AddEntry(h3, "Reg+EtaScale", "pl");
lg->AddEntry(h4, "Reg+EtaScale+Calib", "pl");


h4->Draw();
//h3->Draw("same");
//h2->Draw("same");
h1->Draw("same");
lg->Draw("same");

}
