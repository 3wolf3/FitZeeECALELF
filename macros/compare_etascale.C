{

TFile* file1 = new TFile(
"fitzeescale_out_MODE782_WithNewIC_MC_2012AB.root"
//"calculateEtaScaleFromICs_calibTable_out_MCHighEta_Mode42_Method6_AB_EEP_withEtaScale_MC_V8Elec_Mode781_Method7_AB_MC_3.root"
//"calculateEtaScaleFromICs_calibTable_out_MCHighEta_AB_EEP_withEtaScale_MC_V8Elec_Mode781_Method7_AB_MC_3.root"
//"calculateEtaScaleFromICs_calibTable_out_MCHighEta_AB_EEP_withEtaScale_MC_V8Elec_Mode781_Method7_AB_MC_3_NoHighEtaEEP.root"
//"calculateEtaScaleFromICs_MCHighEta_AB_EEP_withEtaScale_MC_V8Elec_Mode781_Method7_AB_MC_3.root"
//"calculateEtaScaleFromICs_DataHighEta_EEP_withEtaScale_V8Elec_Mode781_Method7_ABC_Data_3_NoHighEtaEEP.root"
//"etascale_calculateEtaScaleFromICs_ABC_empty_EEP.root"
//"etascale_calculateEtaScaleFromICs_ABC_data_EEP.root"
//"etascale_calculateEtaScaleFromICs_ABC_inv_ExceptEEP_EEP.root"
);

TFile* file2 = new TFile(
"out_V8Elec_mode781_method7_evenodd0_MC_3/fitzeescale_out_V8Elec_Mode781_Method7_AB_MC_3.root"
//"calculateEtaScaleFromICs_DataHighEta_EEP_withEtaScale_V8Elec_Mode781_Method7_ABC_Data_3_NoHighEtaEEP.root"
//"out_V8Elec_mode781_method7_evenodd0_Data_3/fitzeescale_out_V8Elec_Mode781_Method7_ABC_Data_3.root"
//"etascale_calculateEtaScaleFromICs_ABC_data_ExceptEEP_EEP.root"
//"fitzeescale_out_ABC_data.root"
//"etascale_calculateEtaScaleFromICs_ABC_empty_EEP.root"
//"etascaleratio_ABC_inv.root"
);

//TH1D* h1 = (TH1D*)file1->Get("hEtaScaleRatio");
TH1D* h1 = (TH1D*)file1->Get("hEtaScale");
//TH1D* h2 = (TH1D*)file2->Get("hEtaScaleRatio");
TH1D* h2 = (TH1D*)file2->Get("hEtaScale");


h1->SetLineColor(2);
h1->SetMarkerColor(2);
h2->SetLineColor(4);
h2->SetMarkerColor(4);


h1->Draw();
h2->Draw("same");




}
