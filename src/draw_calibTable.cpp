// Author Hengne Li @ UVa CERN, 2014

#include "TROOT.h"
#include "TFile.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TCanvas.h"
#include "TAxis.h"
#include <iostream>
#include <string>
#include<sstream>
#include<fstream>


int main(int argc, char* argv[])
{
  if( argc<2 )
  {
    std::cout << argv[0] << " calibTable.dat" << std::endl;
    return 0;
  }
 std::string filename(argv[1]);

 std::string foutname = filename.substr(0, filename.find_last_of(".dat")-3) + ".root";
 std::string foutnameps = filename.substr(0, filename.find_last_of(".dat")-3) + ".ps";
 std::string foutnamepdf = filename.substr(0, filename.find_last_of(".dat")-3) + ".pdf";

 std::cout << " foutname = " << foutname << std::endl;
 std::cout << " foutnameps = " << foutnameps << std::endl;
 std::cout << " foutnamepdf = " << foutnamepdf << std::endl;

 TFile* fout = new TFile(foutname.c_str(), "recreate");
 
 char name[1000];

 sprintf(name, ".x root_style.C");
 gROOT->ProcessLine(name);

 TH1D* h1d = new TH1D("h1d", "h1d", 100,0.5,1.5);
 TH1D* h1derr = new TH1D("h1derr", "h1derr", 100,0.0,5);
 TH2D* h2d = new TH2D("h2d", "h2d", 100,0.,100.,100,0.,100.);
 h1d->Sumw2();
 h1derr->Sumw2();
 h2d->Sumw2();

 h1d->SetMarkerStyle(20);
 h1d->GetXaxis()->SetTitle("calib. const.");
 h1d->GetYaxis()->SetTitle("nCrystals");

 h1derr->SetMarkerStyle(20);
 h1derr->GetXaxis()->SetTitle("uncertainty (error/mean) of calib. const. (%)");
 h1derr->GetYaxis()->SetTitle("nCrystals");

 h2d->GetXaxis()->SetTitle("iX");
 h2d->GetYaxis()->SetTitle("iY");

 int idx, ix, iy, iz, fixed, nfits;
 double c, cerr;
 std::ifstream myfile(filename);
 std::string line;
 if (myfile.is_open())
 {
   while (getline(myfile,line))
   {
     std::stringstream sline(line);
     sline >> idx
            >> ix
            >> iy
            >> iz
            >> c
            >> cerr
            >> fixed
            >> nfits ;
     h2d->SetBinContent(ix, iy, c);
     h2d->SetBinError(ix, iy, cerr);
     h1d->Fill(c);
     h1derr->Fill(cerr/c*100);
   }
   myfile.close();
 }

 TCanvas* plots = new TCanvas("plots", "plots");
 sprintf(name, "%s[", foutnameps.c_str());
 plots->Print(name);
 
 plots->Clear();
 h2d->GetZaxis()->SetRangeUser(0.7,1.3);
 h2d->GetXaxis()->SetRangeUser(30, 70);
 h2d->GetYaxis()->SetRangeUser(30, 70);
 h2d->Draw("colz");
 plots->Print(foutnameps.c_str());

 plots->Clear();
 h1d->Draw();
 plots->Print(foutnameps.c_str());

 plots->Clear();
 h1derr->Draw();
 plots->Print(foutnameps.c_str());
 
 sprintf(name, "%s]", foutnameps.c_str());
 plots->Print(name);

 sprintf(name, ".! ps2pdf %s %s", foutnameps.c_str(), foutnamepdf.c_str());  
 gROOT->ProcessLine(name);

 fout->cd();
 h1d->Write();
 h1derr->Write();
 h2d->Write();
 
 return 1;

}
