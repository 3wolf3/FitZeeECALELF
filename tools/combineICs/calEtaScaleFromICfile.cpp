// Author Hengne Li  @ CERN  2014
#include <TH1D.h>
#include <string>
#include <vector>
#include <iostream>
#include <TFile.h>
#include <fstream>
#include <sstream>
#include "TROOT.h"
#include <etaring.hpp>
#include <icrecord.hpp>

// calculate the eta-scale from ICs

int main(int argc, char* argv[])
{
  if( argc<2 )
  {
    std::cout << argv[0] << "input_ICFile" << std::endl;
    return 0;
  }

  // infilename
  std::string infilename(argv[1]);
  // outfile txt
  std::string outfilename =  std::string(infilename.substr(0,infilename.find_last_of("."))+"_EtaScale.txt");
  // outrootfile txt
  std::string outrootfilename =  std::string(infilename.substr(0,infilename.find_last_of("."))+"_EtaScale.root");

  // get input ICs from input IC file
  std::vector<icrecord> inICtable = getVectorICTableFromFile(infilename.c_str());

  // get empty eta-ring eta-scale vector
  std::vector<EtaRingEnergyScale> EtaScale = GetEmptyVectorEtaRingEtaScale();

  // for each EtaScale, calculate the weighted mean from the ICs of the cells in that eta-ring
  for (int ibin=0; ibin<(int)EtaScale.size(); ibin++)
  {
    // get eta_ring number
    int eta_ring = EtaScale.at(ibin).EtaRing;

    // loop over all cells 
    // if there are cells in this eta-ring, count it in the caculation of the weighted mean;
    double sum_mean_err=0;
    double sum_err=0;
    for (int ic=0; ic<(int)inICtable.size(); ic++)
    {
      int ix = inICtable.at(ic).ix;
      int iy = inICtable.at(ic).iy;
      int iz = inICtable.at(ic).iz;

      // check if the ic is in that eta-ring
      if (GetEtaRing(ix, iy, iz) != eta_ring) continue;

      double cc = inICtable.at(ic).c;
      double ccerr = inICtable.at(ic).cerr;
      // 
      if (ccerr>10.0||cc<0||ccerr<0) continue;

      sum_err += 1./ccerr/ccerr;
      sum_mean_err += cc/ccerr/ccerr;

      //std::cout << "EtaRing " << eta_ring << ", ic = " << ic << " : cc = " << cc  << "; ccerr = " << ccerr << std::endl;
      //std::cout << "               " << " sum_err = " << sum_err << " : sum_mean_err = " << sum_mean_err << std::endl;
    }
    
    //
    double scale = 1.0;
    double scale_err = 0.0;
    if (sum_err>0) 
    {
      scale = sum_mean_err/sum_err;
      scale_err = 1./sum_err;
    }

    //
    EtaScale.at(ibin).s = 1.0/scale; // take the inverse, define the eta-scale as to make the IC to be flat in eta.
    EtaScale.at(ibin).serr = scale_err/scale/scale; // if y=1/x, then dy = dx/x^2
    //
    //std::cout << "EtaRing " << eta_ring << " :  scale = " << scale << " ; scale_err = " << scale_err << std::endl;
  }

  // write the EtaScale into IC table
  // define a out ICtable, init from inICtable, will replace its values by the eta-scale
  std::vector<icrecord> outICtable = inICtable;
  for (int ic=0; ic<(int)outICtable.size(); ic++)
  {
    int ix = outICtable.at(ic).ix;
    int iy = outICtable.at(ic).iy;
    int iz = outICtable.at(ic).iz;    
    int eta_ring = GetEtaRing(ix, iy, iz);

    for (int ibin=0; ibin<(int)EtaScale.size(); ibin++)
    {
      // check if in this eta-ring
      if( eta_ring != EtaScale.at(ibin).EtaRing) continue;
      // if yes
      outICtable.at(ic).c = EtaScale.at(ibin).s;
      outICtable.at(ic).cerr = EtaScale.at(ibin).serr;
      break; // break the loop because one Cell can be only in one Eta-Ring
    } // for EtaScale bin

  } // for (outICtalbe)

  // print to output file
  std::ofstream outfile(outfilename.c_str());
  if (outfile.is_open())
  {
    for (int i=0; i<(int)outICtable.size(); i++)
    {
      icrecord ic = outICtable.at(i);
      outfile << ic.ix << " " << ic.iy << " " << ic.iz << " " << ic.c << " " << ic.cerr << std::endl;
    }
    outfile.close();
  }


  // also write to a root file
  TFile* file = new TFile(outrootfilename.c_str(), "recreate");

  double histBins[1000];
  for (int ibin=0; ibin<(int)EtaScale.size(); ibin++)
  {
    histBins[ibin] = EtaScale.at(ibin).EtaRing-0.5;
    if (ibin==(int)EtaScale.size()-1)
    {
      histBins[ibin+1] = EtaScale.at(ibin).EtaRing+0.5;
    }
  }

  TH1D* hist = new TH1D("hEtaScale", "hEtaScale", (int)EtaScale.size(), histBins);
  hist->Sumw2();
  hist->SetMarkerStyle(20);

  for (int ibin=0; ibin<(int)EtaScale.size(); ibin++)
  {
    hist->SetBinContent(ibin+1, EtaScale.at(ibin).s);
    hist->SetBinError(ibin+1, EtaScale.at(ibin).serr);
  }

  hist->Write();

  file->Close();

  return 0;
}







