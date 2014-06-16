{

TFile* file1 = new TFile(
//"FT_R_53_V21/EcalIntercalibConstants_2012ABCD_offline_191691_ProdNewIC_EtaScale.root"
//"productICfile_EtaScale.root"
"fitzeescale_out_MODE782_WithNewIC_MC_2012AB.root"
);

TFile* file2 = new TFile(
//"FT_R_53_V21/EcalIntercalibConstants_2012ABCD_offline_191691_ProdNewIC_EtaScaleNorm_EtaScale.root"
//"productICfile_EtaScale_prodIC_EtaScale.root"
//"FT_R_53_V21/EcalIntercalibConstants_2012ABCD_offline_191691_NewICEtaScale_EtaScale.root"
"FT_R_53_V21/EcalIntercalibConstants_2012ABCD_offline_191691_NewICOnlyInvMCEtaScale_EtaScale.root"
);

//TH1D* h1 = (TH1D*)file1->Get("hEtaScaleRatio");
TH1D* h1 = (TH1D*)file1->Get("hEtaScale");
//TH1D* h2 = (TH1D*)file2->Get("hEtaScaleRatio");
TH1D* h2 = (TH1D*)file2->Get("hEtaScale");

h1->SetLineColor(2);
h1->SetMarkerColor(2);
h2->SetLineColor(4);
h2->SetMarkerColor(4);
h2->SetMarkerStyle(22);

TLegend* lg = new TLegend(0.6,0.7,0.9,0.9);
//lg->AddEntry(h1, "Before", "pl");
//lg->AddEntry(h2, "After", "pl");
lg->AddEntry(h1, "MC EtaScale", "pl");
lg->AddEntry(h2, "calculated EtaScale from IOV", "pl");

h1->Draw();
h2->Draw("same");
lg->Draw();



}
