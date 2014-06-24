{

   gROOT->SetStyle("Plain");

  const Int_t NRGBs = 5;
  UInt_t Number = 5;
  Double_t Red[Number]    = { 0.00, 0.2, 0.0, 1.0, 0.70};
  Double_t Green[Number]  = { 0.00, 0.8, 0.8, 1.0,  0.00};
  Double_t Blue[Number]   = { 0.60, 1.0, 0.1, 0.0,  0.00};
  Double_t Length[Number] = { 0.00, 0.42, 0.50, 0.58, 1.00 };
  Int_t nb=100;
  TColor::CreateGradientColorTable(Number, Length, Red, Green, Blue, nb);
  gStyle->SetNumberContours(nb);

  //gStyle->SetOptStat(0);
  gStyle->SetStatX(0.90);
  gStyle->SetStatY(0.90);
  gStyle->SetStatW(0.15);
  gStyle->SetStatH(0.10);
}
