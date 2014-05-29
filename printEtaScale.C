{
TFile* file = new TFile(
"fitzeescale_out_V8Elec_Mode781_Method7_ABC_MC_3.root"
//"out_V8Elec_mode781_method7_evenodd0_Data_3/fitzeescale_out_V8Elec_Mode781_Method7_ABC_Data_3.root"
//"fitzeescale_out_D.root"
//"fitzeescale_out_ABC.root"
//"fitzeescale_out_ABC_data.root"
);

TH1D* h1 = (TH1D*)file->Get("hEtaScaleRatio");
//TH1D* h1 = (TH1D*)file->Get("hEtaScale");


int EtaRing = -124;

for (int i=1; i<=h1->GetNbinsX(); i++)
{
  std::cout << EtaRing << " " << h1->GetBinContent(i) << " " << h1->GetBinError(i) << std::endl;

  if (EtaRing==-1)
  {
    EtaRing += 2;
  }
  else 
  {
    EtaRing += 1 ;
  }
}

}
