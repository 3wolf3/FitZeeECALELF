
#include <iostream>
#include <string>
#include<sstream>
#include<fstream>

void draw_calibTable(){
 const char* filename = 
"calibTable_out_MCHighEta_ABC_EEP_withEtaScale_MC_V8Elec_Mode781_Method7_ABC_MC_3.dat"
//"calibTable_out_HighEta_D_MC_EEP.dat"
//"calibTable_out_HighEta_ABCD_empty_EEP.dat"
//"calibTable_out_HighEta_D_inv_EEP.dat"
//"calibTable_out_HighEta_ABCD_inv_EEP.dat"
//"calibTable_out_HighEta_ABCD_EEP.dat"
//"calibTable_out_HighEta_D_EEP.dat"
//"calibTable_out_D_2th_P.dat"
;
 const char* foutname =
"calibTable_out_MCHighEta_ABC_EEP_withEtaScale_MC_V8Elec_Mode781_Method7_ABC_MC_3.root"
//"calibTable_out_HighEta_D_MC_EEP.root"
//"calibTable_out_HighEta_ABCD_empty_EEP.root"
//"calibTable_out_HighEta_D_inv_EEP.root"
//"calibTable_out_HighEta_ABCD_inv_EEP.root"
//"calibTable_out_HighEta_ABCD_EEP.root"
//"calibTable_out_HighEta_D_EEP.root"
//"calibTable_out_D_2th_P.root"
;
 TFile* fout = new TFile(foutname, "recreate");
 

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
//  if(c>1.00000001||c<0.9999999) continue; // debug
     h2d->SetBinContent(ix, iy, c);
     h2d->SetBinError(ix, iy, cerr);
     h1d->Fill(c);
     h1derr->Fill(cerr/c*100);
   }
   myfile.close();
 }


 TCanvas* c1 = new TCanvas("c1", "c1");
 h2d->GetZaxis()->SetRangeUser(0.7,1.3);
 h2d->GetXaxis()->SetRangeUser(30, 70);
 h2d->GetYaxis()->SetRangeUser(30, 70);
 h2d->Draw("colz");

 TCanvas* c2 = new TCanvas("c2", "c2");
 h1d->Draw();

 TCanvas* c3 = new TCanvas("c3", "c3");
 h1derr->Draw();
 
 fout->cd();
 h1d->Write();
 h1derr->Write();
 h2d->Write();
 

}
