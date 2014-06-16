
#include <TH1D.h>
#include <string>
#include <vector>
#include <iostream>
#include <TFile.h>
#include <fstream>
#include <sstream>
#include "TROOT.h"


typedef struct
{
  int EtaRing;
  double s; // scale
  double serr; // error of scale
} EtaRingEnergyScale;

// EE Eta Ring
std::string _defEtaRingEE = "eering.dat";
int _eering_eta[150][150];



// init EE Eta Ring data
void initEEEtaRingTable()
{
  for( int i1 = 0 ; i1 < 150 ; i1++ )
  {
    for( int i2 = 0 ; i2 < 150 ; i2++ )
    {
      _eering_eta[i1][i2] = -1;
    }
  }

  std::ifstream eenumdata (_defEtaRingEE.c_str());
  while ( eenumdata.good() && !eenumdata.eof() )
  {
    std::string line;
    std::getline(eenumdata,line,'\n');
    std::istringstream isstream(line);
    int i1,i2,i3;
    isstream >> i1 >> i2 >> i3;
    _eering_eta[i1][i2] = i3+1;
  }
  eenumdata.close();

}

int GetEtaRing(int ix, int iy, int iz)
{
  if (iz==0) return ix;
  else if (iz==+1) return _eering_eta[ix][iy] + 85;
  else if (iz==-1) return -(_eering_eta[ix][iy] + 85);
  else return -1000;

}



typedef struct
{
  int idx; // index
  int ix;  // cell ix
  int iy;  // cell iy
  int iz;  // cell iz
  double c; // calibration constant
  double cerr; // error of calibratioin constant
  int fixed;  // true: fixed ; false: not fixed.
  int nfits; // n times of fits
} calibRecord;


std::vector<calibRecord> _calibTable;

void initCalibTable(const char* filename)
{
  std::ifstream myfile(filename);
  std::string line;
  if (myfile.is_open())
  {
    _calibTable.clear();
    while (getline(myfile,line))
    {
      calibRecord calib;
      std::stringstream sline(line);
      sline >> calib.idx
             >> calib.ix
             >> calib.iy
             >> calib.iz
             >> calib.c
             >> calib.cerr
             >> calib.fixed
             >> calib.nfits ;
      _calibTable.push_back(calib);
    }
    myfile.close();
  }


}

// Eta bins
std::vector<EtaRingEnergyScale> EtaScale;


void initEtaRingEtaScale()
{


    // 39 EE- bins
    for (int ibin=-39; ibin<=-1; ibin++)
    {
      EtaRingEnergyScale Ascale = {-85+ibin, 1.0, 0.001};
      EtaScale.push_back(Ascale);
    }
    // 85 EB- bins
    for (int ibin=-85; ibin<=-1; ibin++)
    {
      EtaRingEnergyScale Ascale = {ibin, 1.0, 0.001};
      EtaScale.push_back(Ascale);
    }
    // 85 EB+ bins
    for (int ibin=1; ibin<=85; ibin++)
    {
      EtaRingEnergyScale Ascale = {ibin, 1.0, 0.001};
      EtaScale.push_back(Ascale);
    }
    // 39 EE+ bins
    for (int ibin=1; ibin<=39; ibin++)
    {
      EtaRingEnergyScale Ascale = {85+ibin, 1.0, 0.001};
      EtaScale.push_back(Ascale);
    }
}

int main(int argc, char* argv[])
{
  if( argc<2 )
  {
    std::cout << argv[0] << " calibTable.dat" << std::endl;
    return 0;
  }

  std::string _calib_table_file(argv[1]);
  std::string _output_etascale_file = "calculateEtaScaleFromICs_" + _calib_table_file.substr(0, _calib_table_file.find_last_of(".dat")-3) + ".root";

  // init eta-ring
  initEEEtaRingTable();

  // init calib table
  initCalibTable(_calib_table_file.c_str());
  
  // etaring etascale
  initEtaRingEtaScale();   

  // for each EtaScale, calculate the weighted mean from the ICs of the cells in that eta-ring
  for (int ibin=0; ibin<(int)EtaScale.size(); ibin++)
  {
    // get eta_ring number
    int eta_ring = EtaScale.at(ibin).EtaRing;

    // loop over all cells 
    // if there are cells in this eta-ring, count it in the caculation of the weighted mean;
    double sum_mean_err=0;
    double sum_err=0;
    for (int ic=0; ic<(int)_calibTable.size(); ic++)
    {
      int ix = _calibTable.at(ic).ix;
      int iy = _calibTable.at(ic).iy;
      int iz = _calibTable.at(ic).iz;

      // check if the ic is in that eta-ring
      if (GetEtaRing(ix, iy, iz) != eta_ring) continue;

      double cc = _calibTable.at(ic).c;
      double ccerr = _calibTable.at(ic).cerr;
      // 
      //if (cc>0.9999999&&cc<1.0000001) continue;

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
    EtaScale.at(ibin).s = scale;
    EtaScale.at(ibin).serr = scale_err;
    //
    //std::cout << "EtaRing " << eta_ring << " :  scale = " << scale << " ; scale_err = " << scale_err << std::endl;
  }


  TFile* file = new TFile(_output_etascale_file.c_str(), "recreate");

  double histBins[1000];
  for (int ibin=0; ibin<(int)EtaScale.size(); ibin++)
  {
    histBins[ibin] = EtaScale.at(ibin).EtaRing-0.5;
    if (ibin==(int)EtaScale.size()-1)
    {
      histBins[ibin+1] = EtaScale.at(ibin).EtaRing+0.5;
    }
  }

  TH1D* hist = new TH1D("hEtaScaleRatio", "hEtaScaleRatio", (int)EtaScale.size(), histBins);
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







