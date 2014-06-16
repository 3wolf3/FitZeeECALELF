
#include <iostream>
#include <string>
#include<sstream>
#include<fstream>

TH2D* GetCorrelation2D(TH2D* hmap1, TH2D* hmap2, char* hname);

void compare_calibTable(){

char* file1 =
//"calibTable_out_ABCD_1th_P.root"
"calibTable_out_HighEta_ABCD_empty_EEP.root"
;

char* file2 =
"calibTable_out_HighEta_ABCD_inv_EEP.root"
;

TFile* f1 = new TFile(file1);
TFile* f2 = new TFile(file2);

 TH2D* h2d1 = (TH2D*)f1->Get("h2d");
 TH2D* h2d2 = (TH2D*)f2->Get("h2d");

 TH2D* hcorr = (TH2D*)GetCorrelation2D(h2d1, h2d2, "hcorr");

 hcorr->GetXaxis()->SetTitle("Without Eta-Scale");
 hcorr->GetYaxis()->SetTitle("With Eta-Scale");

 TCanvas* c1 = new TCanvas("c1", "c1");
 //hcorr->GetZaxis()->SetRangeUser(0.75,1.25);
 //hcorr->GetXaxis()->SetRangeUser(30, 70);
 //hcorr->GetYaxis()->SetRangeUser(30, 70);
 hcorr->Draw("colz");


}

TH2D* GetCorrelation2D(TH2D* hmap1, TH2D* hmap2, char* hname)
{
  int nbinsx = (int)hmap1->GetNbinsX();
  int nbinsy = (int)hmap1->GetNbinsY();
  if (nbinsx != (int)hmap2->GetNbinsX())
  {
    std::cout << "Mismatch NbinsX! Return nothing" << std::endl;
    return 0;
  }
  if (nbinsy != (int)hmap2->GetNbinsY())
  {
    std::cout << "Mismatch NbinsY! Return nothing" << std::endl;
    return 0;
  }

  TH2D* hout = new TH2D(hname, hname, 300, 0.0, 3.0, 300, 0.0, 3.0);
  for (int ix=0; ix<=nbinsx; ix++)
  {
    for (int iy=0; iy<=nbinsy; iy++)
    {
      double ic1 = hmap1->GetBinContent(ix, iy);
      double ic2 = hmap2->GetBinContent(ix, iy);
      if (ic1<=0.01||ic2<=0.01) continue;
      hout->Fill(ic1, ic2);
    }
  }

  return hout;
}
