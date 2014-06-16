{
TFile* file = new TFile(
//"fitzeescale_out_MODE782_WithNewIC_MC_2012D.root"
);

//TH1D* h1 = (TH1D*)file->Get("hEtaScaleRatio");
TH1D* h1 = (TH1D*)file->Get("hEtaScale");


int EtaRing = -124;

for (int i=1; i<=h1->GetNbinsX(); i++)
{
  double xxx = h1->GetBinContent(i);
  double err = h1->GetBinError(i);
  std::cout << EtaRing << " " << 1.0/xxx << " " << err/xxx/xxx << std::endl;

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
