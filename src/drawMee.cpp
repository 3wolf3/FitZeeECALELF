// Author: Hengne Li UVa CERN 2014

#include "TFile.h"
#include "drawMee.hpp"
#include "config.hpp"
#include "TCanvas.h"
#include "TLegend.h"

int main(int argc, char* argv[])
{

  if( argc<2 )
  {
    std::cout << argv[0] << " config_file " << std::endl;
    return 0;
  }

  // open steering file names
  config steer(argv[1]);

  std::string inrootfilename = steer.getString("inrootfilename");
  std::string calibtablename = steer.getString("calibtablename");
  std::string outrootfilename = steer.getString("outrootfilename");

  std::string foutnameps = outrootfilename.substr(0, outrootfilename.find_last_of(".root")-4) + ".ps";
  std::string foutnamepdf = outrootfilename.substr(0, outrootfilename.find_last_of(".root")-4) + ".pdf";
 
  int maxevt = steer.getInt("maxevt");
  int nbins = steer.getInt("nbins"); 
  int method = steer.getInt("method");
  double scale = steer.getDouble("scale");
  int oddeven = steer.getInt("oddeven");
 
  std::string etascale_refA = steer.getString("etascale_refA");
  std::string etascale_refB = steer.getString("etascale_refB");
  std::string etascale_refC = steer.getString("etascale_refC");
  std::string etascale_refD = steer.getString("etascale_refD");

  std::string regVersion = steer.getString("regVersion");

  std::cout << "Input file: " << inrootfilename << std::endl;
  std::cout << "Calib Table file: " << calibtablename << std::endl;
  std::cout << "ouput file: " << outrootfilename << std::endl;
  std::cout << " foutnameps = " << foutnameps << std::endl;
  std::cout << " foutnamepdf = " << foutnamepdf << std::endl;
  std::cout << "max events: " << maxevt << std::endl;
  std::cout << "nbins in the hist: " << nbins << std::endl;
  std::cout << "method: " << method << std::endl;
  std::cout << "scale: " << scale << std::endl;
  std::cout << "RegVersion: " << regVersion << std::endl;
  std::cout << "Both/Odd/Even: " << oddeven << std::endl;
  std::cout << "  EtaScale Reference File A = " << etascale_refA << std::endl;
  std::cout << "  EtaScale Reference File B = " << etascale_refB << std::endl;
  std::cout << "  EtaScale Reference File C = " << etascale_refC << std::endl;
  std::cout << "  EtaScale Reference File D = " << etascale_refD << std::endl;

  // reading data
  TChain* tree = new TChain("selected", "selected");
  tree->Add(inrootfilename.c_str());
 
  // reading extra tree
  TChain* extree = new TChain("extraCalibTree", "extraCalibTree");
  extree->Add(inrootfilename.c_str());

  // Set the branches for the TChain/TTree
  SetTreeBranch(tree);
  SetExtraTreeBranch(extree);

 
  // output root file
  TFile* fout = TFile::Open(outrootfilename.c_str(), "recreate");

  // calibTable
  std::map<int, std::map<int, std::map<int, calibRecord> > > calibTable = getMapCalibTableFromFile(calibtablename.c_str());
  
  // EtaScale files
  std::vector<EtaRingEnergyScale> EtaRingEtaScaleRefA;
  std::vector<EtaRingEnergyScale> EtaRingEtaScaleRefB;
  std::vector<EtaRingEnergyScale> EtaRingEtaScaleRefC;
  std::vector<EtaRingEnergyScale> EtaRingEtaScaleRefD;

  EtaRingEtaScaleRefA = GetVectorEtaRingEtaScaleFromFile(etascale_refA.c_str());
  EtaRingEtaScaleRefB = GetVectorEtaRingEtaScaleFromFile(etascale_refB.c_str());
  EtaRingEtaScaleRefC = GetVectorEtaRingEtaScaleFromFile(etascale_refC.c_str());
  EtaRingEtaScaleRefD = GetVectorEtaRingEtaScaleFromFile(etascale_refD.c_str());

  // Get Mee Hist using SC energy
  TH1D* h1 = (TH1D*)getTH1DMeeSCEnergy(tree, "hMeeSC", nbins, maxevt, scale, oddeven);
  h1->SetMarkerColor(2);
  h1->SetLineColor(2);

  // Get Mee Hist using Original Energy regression
  TH1D* h2 = (TH1D*)getTH1DMeeRegEnergy(tree, "hMeeReg", nbins, maxevt, scale, oddeven, regVersion);
  h2->SetMarkerColor(6);
  h2->SetLineColor(6);

  // Get Mee Hist using Energy Reg. + EtaScale
  TH1D* h3 = (TH1D*)getTH1DMeeRegEnergyEtaRingEtaScale(tree, 
                 EtaRingEtaScaleRefA, EtaRingEtaScaleRefB, EtaRingEtaScaleRefC, EtaRingEtaScaleRefD,
                 "hMeeRegEtaScale", nbins, maxevt, scale, oddeven, regVersion);
  h3->SetMarkerColor(8);
  h3->SetLineColor(8);

  // Get Mee Hist with Energy Reg. + EtaScale + Re-Calib
  TH1D* h4 = (TH1D*)getTH1DMeeRegEnergyEtaRingEtaScaleNewICs(tree, extree, calibTable, 
                 EtaRingEtaScaleRefA, EtaRingEtaScaleRefB, EtaRingEtaScaleRefC, EtaRingEtaScaleRefD, 
                 "hMeeRegEtaScaleNewICs", nbins, maxevt, method, scale, oddeven, regVersion);
  h4->SetMarkerColor(4);
  h4->SetLineColor(4);

  char name[1000];

  sprintf(name, ".x interface/root_style.C");
  gROOT->ProcessLine(name); 

  TCanvas* plots = new TCanvas("plots", "plots");
  sprintf(name, "%s[", foutnameps.c_str());
  plots->Print(name);

  TLegend* lg = new TLegend(0.6, 0.7, 0.9, 0.9);

  plots->Clear();
  lg->AddEntry(h1, "SC", "pl");
  lg->AddEntry(h4, "Reg+EtaScale+Calib", "pl");


  h4->Draw();
  h1->Draw("same");
  lg->Draw("same");
  plots->Print(foutnameps.c_str());

  plots->Clear();
  lg->Clear();
  lg->AddEntry(h1, "SC", "pl");
  lg->AddEntry(h2, "Reg", "pl");
  lg->AddEntry(h3, "Reg+EtaScale", "pl");
  lg->AddEntry(h4, "Reg+EtaScale+Calib", "pl");


  h4->Draw();
  h3->Draw("same");
  h2->Draw("same");
  h1->Draw("same");
  lg->Draw("same");
  plots->Print(foutnameps.c_str());

   sprintf(name, "%s]", foutnameps.c_str());
   plots->Print(name);

   sprintf(name, ".! ps2pdf %s %s", foutnameps.c_str(), foutnamepdf.c_str());
   gROOT->ProcessLine(name);

 
  // write the hist to out root file
  fout->cd();
  h1->Write();
  h2->Write();
  h3->Write();
  h4->Write();

  // delete the chain no more need it
  tree->Delete();
  extree->Delete();
 
  // close
  fout->Close();
  
  //
  return 0;
}
