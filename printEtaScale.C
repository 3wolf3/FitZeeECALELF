{
//TFile* file = new TFile("etascaleratio_ABC_inv.root");
TFile* file = new TFile(
"fitzeescale_out_D.root"
//"fitzeescale_out_ABC.root"
//"fitzeescale_out_ABC_data.root"
);

//TH1D* h1 = (TH1D*)file->Get("hEtaScaleRatio");
TH1D* h1 = (TH1D*)file->Get("hEtaScale");


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
