#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <sstream>
#include <string>
#include <utility>
#include "TROOT.h"
#include "TChain.h"
#include "TH1D.h"
#include "TMath.h"


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

typedef struct
{
  double min;
  double max;
  double s; // scale
  double serr; // error of scale
} EnergyScale;

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
  if (!eenumdata.good() ) 
  {
    std::cout << "initEEEtaRingTable():: bad eering.dat file" << std::endl;
    return ;
  }
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

////////////////////////////////////
// variables for ROOT Tree
//Declaration of leaves types
   Int_t           runNumber;
   ULong64_t       eventNumber;
   Int_t           lumiBlock;
   ULong64_t          runTime;
   Float_t         mcGenWeight;
   Char_t          HLTfire;
   Int_t           nPU[1];
   Float_t         rho;
   Int_t           nPV;
   Int_t           eleID[2];
   Int_t           ZStat;
   Int_t           chargeEle[2];
   Float_t         etaSCEle[2];
   Float_t         phiSCEle[2];
   Float_t         etaEle[2];
   Float_t         phiEle[2];
   Int_t           classificationEle[2];
   Int_t           recoFlagsEle[2];
   Float_t         PtEle[2];
   Float_t         fbremEle[2];
   Float_t         seedXSCEle[2];
   Float_t         seedYSCEle[2];
   Float_t         seedEnergySCEle[2];
   Float_t         seedLCSCEle[2];
   Float_t         avgLCSCEle[2];
   UChar_t         gainEle[2];
   Float_t         energyMCEle[2];
   Float_t         energySCEle[2];
   Float_t         rawEnergySCEle[2];
   Float_t         esEnergySCEle[2];
   Float_t         energySCEle_corr[2];
   Float_t         energySCEle_regrCorr_ele[2];
   Float_t         energySCEle_regrCorr_pho[2];
   Float_t         energyEle_regrCorr_fra[2];
   Float_t         energySigmaEle_regrCorr_fra[2];
   Float_t         energyEle_regrCorr_egamma[2];
   Float_t         energySigmaEle_regrCorr_egamma[2];
   Float_t         energySigmaSCEle_regrCorr_ele[2];
   Float_t         energySigmaSCEle_regrCorr_pho[2];
   Float_t         energySCEle_regrCorrSemiParV4_ele[2];
   Float_t         energySCEle_regrCorrSemiParV4_pho[2];
   Float_t         energySCEle_regrCorrSemiParV5_ele[2];
   Float_t         energySCEle_regrCorrSemiParV5_pho[2];
   Float_t         energySigmaSCEle_regrCorrSemiParV4_ele[2];
   Float_t         energySigmaSCEle_regrCorrSemiParV4_pho[2];
   Float_t         energySigmaSCEle_regrCorrSemiParV5_ele[2];
   Float_t         energySigmaSCEle_regrCorrSemiParV5_pho[2];
   Float_t         energySCEle_regrCorrSemiParV6_ele[2];
   Float_t         energySCEle_regrCorrSemiParV6_pho[2];
   Float_t         energySigmaSCEle_regrCorrSemiParV6_ele[2];
   Float_t         energySigmaSCEle_regrCorrSemiParV6_pho[2];
   Float_t         energySCEle_regrCorrSemiParV7_ele[2];
   Float_t         energySCEle_regrCorrSemiParV7_pho[2];
   Float_t         energySigmaSCEle_regrCorrSemiParV7_ele[2];
   Float_t         energySigmaSCEle_regrCorrSemiParV7_pho[2];
   Float_t         energySCEle_regrCorrSemiParV8_ele[2];
   Float_t         energySCEle_regrCorrSemiParV8_pho[2];
   Float_t         energySigmaSCEle_regrCorrSemiParV8_ele[2];
   Float_t         energySigmaSCEle_regrCorrSemiParV8_pho[2];
   Float_t         energySCEle_regrCorrSemiPar7TeVtrainV6_ele[2];
   Float_t         energySCEle_regrCorrSemiPar7TeVtrainV6_pho[2];
   Float_t         energySigmaSCEle_regrCorrSemiPar7TeVtrainV6_ele[2];
   Float_t         energySigmaSCEle_regrCorrSemiPar7TeVtrainV6_pho[2];
   Float_t         energySCEle_regrCorrSemiPar7TeVtrainV7_ele[2];
   Float_t         energySCEle_regrCorrSemiPar7TeVtrainV7_pho[2];
   Float_t         energySigmaSCEle_regrCorrSemiPar7TeVtrainV7_ele[2];
   Float_t         energySigmaSCEle_regrCorrSemiPar7TeVtrainV7_pho[2];
   Float_t         energySCEle_regrCorrSemiPar7TeVtrainV8_ele[2];
   Float_t         energySCEle_regrCorrSemiPar7TeVtrainV8_pho[2];
   Float_t         energySigmaSCEle_regrCorrSemiPar7TeVtrainV8_ele[2];
   Float_t         energySigmaSCEle_regrCorrSemiPar7TeVtrainV8_pho[2];
   Float_t         R9Ele[2];
   Float_t         e5x5SCEle[2];
   Float_t         pModeGsfEle[2];
   Float_t         pAtVtxGsfEle[2];
   Float_t         invMass;
   Float_t         invMass_SC;
   Float_t         invMass_e5x5;
   Float_t         invMass_rawSC;
   Float_t         invMass_rawSC_esSC;
   Float_t         invMass_SC_corr;
   Float_t         invMass_SC_regrCorr_ele;
   Float_t         invMass_SC_regrCorr_pho;
   Float_t         invMass_regrCorr_fra;
   Float_t         invMass_regrCorr_egamma;
   Float_t         invMass_SC_regrCorrSemiParV4_pho;
   Float_t         invMass_SC_regrCorrSemiParV4_ele;
   Float_t         invMass_SC_regrCorrSemiParV5_pho;
   Float_t         invMass_SC_regrCorrSemiParV5_ele;
   Float_t         invMass_SC_regrCorrSemiParV6_pho;
   Float_t         invMass_SC_regrCorrSemiParV6_ele;
   Float_t         invMass_SC_regrCorrSemiParV7_pho;
   Float_t         invMass_SC_regrCorrSemiParV7_ele;
   Float_t         invMass_SC_regrCorrSemiParV8_pho;
   Float_t         invMass_SC_regrCorrSemiParV8_ele;
   Float_t         invMass_SC_regrCorrSemiPar7TeVtrainV6_pho;
   Float_t         invMass_SC_regrCorrSemiPar7TeVtrainV6_ele;
   Float_t         invMass_SC_regrCorrSemiPar7TeVtrainV7_pho;
   Float_t         invMass_SC_regrCorrSemiPar7TeVtrainV7_ele;
   Float_t         invMass_SC_regrCorrSemiPar7TeVtrainV8_pho;
   Float_t         invMass_SC_regrCorrSemiPar7TeVtrainV8_ele;
   Float_t         invMass_MC;
   Float_t         etaMCEle[2];
   Float_t         phiMCEle[2];
   Int_t           nHitsSCEle[2];

// extra tree

//Declaration of leaves types
   std::vector<float>*   rawIdRecHitSCEle1;
   std::vector<float>*   rawIdRecHitSCEle2;
   std::vector<float>*   XRecHitSCEle1;
   std::vector<float>*   XRecHitSCEle2;
   std::vector<float>*   YRecHitSCEle1;
   std::vector<float>*   YRecHitSCEle2;
   std::vector<float>*   energyRecHitSCEle1;
   std::vector<float>*   energyRecHitSCEle2;
   std::vector<float>*   LCRecHitSCEle1;
   std::vector<float>*   LCRecHitSCEle2;
   std::vector<float>*   ICRecHitSCEle1;
   std::vector<float>*   ICRecHitSCEle2;
   std::vector<float>*   AlphaRecHitSCEle1;
   std::vector<float>*   AlphaRecHitSCEle2;

//////////////////////

void printCalibRecord(calibRecord& record)
{
  std::cout << record.idx << " "
  << record.ix << " "
  << record.iy << " "
  << record.iz << " "
  << record.c << " "
  << record.cerr << " "
  << record.fixed << " "
  << record.nfits << " "
  << std::endl;
}

std::vector<calibRecord> getCalibTableFromFile(const char* filename)
{
  std::vector<calibRecord> mycalibTable;
  
  std::ifstream myfile(filename);
  std::string line;
  if (myfile.is_open())
  {
    mycalibTable.clear();
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
      mycalibTable.push_back(calib);
    }
    myfile.close();
  }
  return mycalibTable;
}

void printCalibTableToFile(const std::vector<calibRecord>& calibTable, const char* filename = "calibTable_out.dat")
{
  std::ofstream myfile(filename);
  if (myfile.is_open())
  {
    for (int i=0; i<(int)calibTable.size(); i++)
    {
      myfile << calibTable.at(i).idx << " "
      << calibTable.at(i).ix << " "
      << calibTable.at(i).iy<< " "
      << calibTable.at(i).iz<< " "
      << calibTable.at(i).c << " "
      << calibTable.at(i).cerr << " "
      << calibTable.at(i).fixed << " "
      << calibTable.at(i).nfits << " "
      << std::endl;
    }
    myfile.close();
  }
}

void printCalibTableToScreen(const std::vector<calibRecord>& calibTable)
{
  for (int i=0; i<(int)calibTable.size(); i++)
  {
    std::cout << calibTable.at(i).idx << " "
    << calibTable.at(i).ix << " "
    << calibTable.at(i).iy<< " "
    << calibTable.at(i).iz<< " "
    << calibTable.at(i).c << " "
    << calibTable.at(i).cerr << " "
    << calibTable.at(i).fixed << " "
    << calibTable.at(i).nfits << " "
    << std::endl;
  }

}

// set tree branches
void SetTreeBranch(TChain* tree)
{
   // Set branch addresses.
   tree->SetBranchAddress("runNumber",&runNumber);
   tree->SetBranchAddress("eventNumber",&eventNumber);
   tree->SetBranchAddress("lumiBlock",&lumiBlock);
   tree->SetBranchAddress("runTime",&runTime);
   tree->SetBranchAddress("mcGenWeight",&mcGenWeight);
   tree->SetBranchAddress("HLTfire",&HLTfire);
   tree->SetBranchAddress("nPU",nPU);
   tree->SetBranchAddress("rho",&rho);
   tree->SetBranchAddress("nPV",&nPV);
   tree->SetBranchAddress("eleID",eleID);
   tree->SetBranchAddress("ZStat",&ZStat);
   tree->SetBranchAddress("chargeEle",chargeEle);
   tree->SetBranchAddress("etaSCEle",etaSCEle);
   tree->SetBranchAddress("phiSCEle",phiSCEle);
   tree->SetBranchAddress("etaEle",etaEle);
   tree->SetBranchAddress("phiEle",phiEle);
   tree->SetBranchAddress("classificationEle",classificationEle);
   tree->SetBranchAddress("recoFlagsEle",recoFlagsEle);
   tree->SetBranchAddress("PtEle",PtEle);
   tree->SetBranchAddress("fbremEle",fbremEle);
   tree->SetBranchAddress("seedXSCEle",seedXSCEle);
   tree->SetBranchAddress("seedYSCEle",seedYSCEle);
   tree->SetBranchAddress("seedEnergySCEle",seedEnergySCEle);
   tree->SetBranchAddress("seedLCSCEle",seedLCSCEle);
   tree->SetBranchAddress("avgLCSCEle",avgLCSCEle);
   tree->SetBranchAddress("gainEle",gainEle);
   tree->SetBranchAddress("energyMCEle",energyMCEle);
   tree->SetBranchAddress("energySCEle",energySCEle);
   tree->SetBranchAddress("rawEnergySCEle",rawEnergySCEle);
   tree->SetBranchAddress("esEnergySCEle",esEnergySCEle);
   tree->SetBranchAddress("energySCEle_corr",energySCEle_corr);
   tree->SetBranchAddress("energySCEle_regrCorr_ele",energySCEle_regrCorr_ele);
   tree->SetBranchAddress("energySCEle_regrCorr_pho",energySCEle_regrCorr_pho);
   tree->SetBranchAddress("energyEle_regrCorr_fra",energyEle_regrCorr_fra);
   tree->SetBranchAddress("energySigmaEle_regrCorr_fra",energySigmaEle_regrCorr_fra);
   tree->SetBranchAddress("energyEle_regrCorr_egamma",energyEle_regrCorr_egamma);
   tree->SetBranchAddress("energySigmaEle_regrCorr_egamma",energySigmaEle_regrCorr_egamma);
   tree->SetBranchAddress("energySigmaSCEle_regrCorr_ele",energySigmaSCEle_regrCorr_ele);
   tree->SetBranchAddress("energySigmaSCEle_regrCorr_pho",energySigmaSCEle_regrCorr_pho);
   tree->SetBranchAddress("energySCEle_regrCorrSemiParV4_ele",energySCEle_regrCorrSemiParV4_ele);
   tree->SetBranchAddress("energySCEle_regrCorrSemiParV4_pho",energySCEle_regrCorrSemiParV4_pho);
   tree->SetBranchAddress("energySCEle_regrCorrSemiParV5_ele",energySCEle_regrCorrSemiParV5_ele);
   tree->SetBranchAddress("energySCEle_regrCorrSemiParV5_pho",energySCEle_regrCorrSemiParV5_pho);
   tree->SetBranchAddress("energySigmaSCEle_regrCorrSemiParV4_ele",energySigmaSCEle_regrCorrSemiParV4_ele);
   tree->SetBranchAddress("energySigmaSCEle_regrCorrSemiParV4_pho",energySigmaSCEle_regrCorrSemiParV4_pho);
   tree->SetBranchAddress("energySigmaSCEle_regrCorrSemiParV5_ele",energySigmaSCEle_regrCorrSemiParV5_ele);
   tree->SetBranchAddress("energySigmaSCEle_regrCorrSemiParV5_pho",energySigmaSCEle_regrCorrSemiParV5_pho);
   tree->SetBranchAddress("energySCEle_regrCorrSemiParV6_ele",energySCEle_regrCorrSemiParV6_ele);
   tree->SetBranchAddress("energySCEle_regrCorrSemiParV6_pho",energySCEle_regrCorrSemiParV6_pho);
   tree->SetBranchAddress("energySigmaSCEle_regrCorrSemiParV6_ele",energySigmaSCEle_regrCorrSemiParV6_ele);
   tree->SetBranchAddress("energySigmaSCEle_regrCorrSemiParV6_pho",energySigmaSCEle_regrCorrSemiParV6_pho);
   tree->SetBranchAddress("energySCEle_regrCorrSemiParV7_ele",energySCEle_regrCorrSemiParV7_ele);
   tree->SetBranchAddress("energySCEle_regrCorrSemiParV7_pho",energySCEle_regrCorrSemiParV7_pho);
   tree->SetBranchAddress("energySigmaSCEle_regrCorrSemiParV7_ele",energySigmaSCEle_regrCorrSemiParV7_ele);
   tree->SetBranchAddress("energySigmaSCEle_regrCorrSemiParV7_pho",energySigmaSCEle_regrCorrSemiParV7_pho);
   tree->SetBranchAddress("energySCEle_regrCorrSemiParV8_ele",energySCEle_regrCorrSemiParV8_ele);
   tree->SetBranchAddress("energySCEle_regrCorrSemiParV8_pho",energySCEle_regrCorrSemiParV8_pho);
   tree->SetBranchAddress("energySigmaSCEle_regrCorrSemiParV8_ele",energySigmaSCEle_regrCorrSemiParV8_ele);
   tree->SetBranchAddress("energySigmaSCEle_regrCorrSemiParV8_pho",energySigmaSCEle_regrCorrSemiParV8_pho);
   tree->SetBranchAddress("energySCEle_regrCorrSemiPar7TeVtrainV6_ele",energySCEle_regrCorrSemiPar7TeVtrainV6_ele);
   tree->SetBranchAddress("energySCEle_regrCorrSemiPar7TeVtrainV6_pho",energySCEle_regrCorrSemiPar7TeVtrainV6_pho);
   tree->SetBranchAddress("energySigmaSCEle_regrCorrSemiPar7TeVtrainV6_ele",energySigmaSCEle_regrCorrSemiPar7TeVtrainV6_ele);
   tree->SetBranchAddress("energySigmaSCEle_regrCorrSemiPar7TeVtrainV6_pho",energySigmaSCEle_regrCorrSemiPar7TeVtrainV6_pho);
   tree->SetBranchAddress("energySCEle_regrCorrSemiPar7TeVtrainV7_ele",energySCEle_regrCorrSemiPar7TeVtrainV7_ele);
   tree->SetBranchAddress("energySCEle_regrCorrSemiPar7TeVtrainV7_pho",energySCEle_regrCorrSemiPar7TeVtrainV7_pho);
   tree->SetBranchAddress("energySigmaSCEle_regrCorrSemiPar7TeVtrainV7_ele",energySigmaSCEle_regrCorrSemiPar7TeVtrainV7_ele);
   tree->SetBranchAddress("energySigmaSCEle_regrCorrSemiPar7TeVtrainV7_pho",energySigmaSCEle_regrCorrSemiPar7TeVtrainV7_pho);
   tree->SetBranchAddress("energySCEle_regrCorrSemiPar7TeVtrainV8_ele",energySCEle_regrCorrSemiPar7TeVtrainV8_ele);
   tree->SetBranchAddress("energySCEle_regrCorrSemiPar7TeVtrainV8_pho",energySCEle_regrCorrSemiPar7TeVtrainV8_pho);
   tree->SetBranchAddress("energySigmaSCEle_regrCorrSemiPar7TeVtrainV8_ele",energySigmaSCEle_regrCorrSemiPar7TeVtrainV8_ele);
   tree->SetBranchAddress("energySigmaSCEle_regrCorrSemiPar7TeVtrainV8_pho",energySigmaSCEle_regrCorrSemiPar7TeVtrainV8_pho);
   tree->SetBranchAddress("R9Ele",R9Ele);
   tree->SetBranchAddress("e5x5SCEle",e5x5SCEle);
   tree->SetBranchAddress("pModeGsfEle",pModeGsfEle);
   tree->SetBranchAddress("pAtVtxGsfEle",pAtVtxGsfEle);
   tree->SetBranchAddress("invMass",&invMass);
   tree->SetBranchAddress("invMass_SC",&invMass_SC);
   tree->SetBranchAddress("invMass_e5x5",&invMass_e5x5);
   tree->SetBranchAddress("invMass_rawSC",&invMass_rawSC);
   tree->SetBranchAddress("invMass_rawSC_esSC",&invMass_rawSC_esSC);
   tree->SetBranchAddress("invMass_SC_corr",&invMass_SC_corr);
   tree->SetBranchAddress("invMass_SC_regrCorr_ele",&invMass_SC_regrCorr_ele);
   tree->SetBranchAddress("invMass_SC_regrCorr_pho",&invMass_SC_regrCorr_pho);
   tree->SetBranchAddress("invMass_regrCorr_fra",&invMass_regrCorr_fra);
   tree->SetBranchAddress("invMass_regrCorr_egamma",&invMass_regrCorr_egamma);
   tree->SetBranchAddress("invMass_SC_regrCorrSemiParV4_pho",&invMass_SC_regrCorrSemiParV4_pho);
   tree->SetBranchAddress("invMass_SC_regrCorrSemiParV4_ele",&invMass_SC_regrCorrSemiParV4_ele);
   tree->SetBranchAddress("invMass_SC_regrCorrSemiParV5_pho",&invMass_SC_regrCorrSemiParV5_pho);
   tree->SetBranchAddress("invMass_SC_regrCorrSemiParV5_ele",&invMass_SC_regrCorrSemiParV5_ele);
   tree->SetBranchAddress("invMass_SC_regrCorrSemiParV6_pho",&invMass_SC_regrCorrSemiParV6_pho);
   tree->SetBranchAddress("invMass_SC_regrCorrSemiParV6_ele",&invMass_SC_regrCorrSemiParV6_ele);
   tree->SetBranchAddress("invMass_SC_regrCorrSemiParV7_pho",&invMass_SC_regrCorrSemiParV7_pho);
   tree->SetBranchAddress("invMass_SC_regrCorrSemiParV7_ele",&invMass_SC_regrCorrSemiParV7_ele);
   tree->SetBranchAddress("invMass_SC_regrCorrSemiParV8_pho",&invMass_SC_regrCorrSemiParV8_pho);
   tree->SetBranchAddress("invMass_SC_regrCorrSemiParV8_ele",&invMass_SC_regrCorrSemiParV8_ele);
   tree->SetBranchAddress("invMass_SC_regrCorrSemiPar7TeVtrainV6_pho",&invMass_SC_regrCorrSemiPar7TeVtrainV6_pho);
   tree->SetBranchAddress("invMass_SC_regrCorrSemiPar7TeVtrainV6_ele",&invMass_SC_regrCorrSemiPar7TeVtrainV6_ele);
   tree->SetBranchAddress("invMass_SC_regrCorrSemiPar7TeVtrainV7_pho",&invMass_SC_regrCorrSemiPar7TeVtrainV7_pho);
   tree->SetBranchAddress("invMass_SC_regrCorrSemiPar7TeVtrainV7_ele",&invMass_SC_regrCorrSemiPar7TeVtrainV7_ele);
   tree->SetBranchAddress("invMass_SC_regrCorrSemiPar7TeVtrainV8_pho",&invMass_SC_regrCorrSemiPar7TeVtrainV8_pho);
   tree->SetBranchAddress("invMass_SC_regrCorrSemiPar7TeVtrainV8_ele",&invMass_SC_regrCorrSemiPar7TeVtrainV8_ele);
   tree->SetBranchAddress("invMass_MC",&invMass_MC);
   tree->SetBranchAddress("etaMCEle",etaMCEle);
   tree->SetBranchAddress("phiMCEle",phiMCEle);
   tree->SetBranchAddress("nHitsSCEle",nHitsSCEle);
}

// set tree branches
void SetExtraTreeBranch(TChain* extraCalibTree){

   // Set branch addresses.
   extraCalibTree->SetBranchAddress("runNumber",&runNumber);
   extraCalibTree->SetBranchAddress("eventNumber",&eventNumber);
   extraCalibTree->SetBranchAddress("lumiBlock",&lumiBlock);
   extraCalibTree->SetBranchAddress("runTime",&runTime);
   extraCalibTree->SetBranchAddress("nHitsSCEle",nHitsSCEle);
   extraCalibTree->SetBranchAddress("rawIdRecHitSCEle1",&rawIdRecHitSCEle1);
   extraCalibTree->SetBranchAddress("rawIdRecHitSCEle2",&rawIdRecHitSCEle2);
   extraCalibTree->SetBranchAddress("XRecHitSCEle1",&XRecHitSCEle1);
   extraCalibTree->SetBranchAddress("XRecHitSCEle2",&XRecHitSCEle2);
   extraCalibTree->SetBranchAddress("YRecHitSCEle1",&YRecHitSCEle1);
   extraCalibTree->SetBranchAddress("YRecHitSCEle2",&YRecHitSCEle2);
   extraCalibTree->SetBranchAddress("energyRecHitSCEle1",&energyRecHitSCEle1);
   extraCalibTree->SetBranchAddress("energyRecHitSCEle2",&energyRecHitSCEle2);
   extraCalibTree->SetBranchAddress("LCRecHitSCEle1",&LCRecHitSCEle1);
   extraCalibTree->SetBranchAddress("LCRecHitSCEle2",&LCRecHitSCEle2);
   extraCalibTree->SetBranchAddress("ICRecHitSCEle1",&ICRecHitSCEle1);
   extraCalibTree->SetBranchAddress("ICRecHitSCEle2",&ICRecHitSCEle2);
   extraCalibTree->SetBranchAddress("AlphaRecHitSCEle1",&AlphaRecHitSCEle1);
   extraCalibTree->SetBranchAddress("AlphaRecHitSCEle2",&AlphaRecHitSCEle2);

}






double calcMass(double E1, double Eta1, double Phi1,
                double E2, double Eta2, double Phi2)
{
  // direction
  double Theta1 = 2.0*atan(exp(-Eta1));
  double px1 = E1*sin(Theta1)*cos(Phi1);
  double py1 = E1*sin(Theta1)*sin(Phi1);
  double pz1 = E1*cos(Theta1);
  double Theta2 = 2.0*atan(exp(-Eta2));
  double px2 = E2*sin(Theta2)*cos(Phi2);
  double py2 = E2*sin(Theta2)*sin(Phi2);
  double pz2 = E2*cos(Theta2);
  // mass
  double px = px1+px2;
  double py = py1+py2;
  double pz = pz1+pz2;
  double E = E1+E2;
  double mass = sqrt(E*E-(px*px+py*py+pz*pz));
  return mass;
}

double getCalibConstFromCalibTable(int ix, int iy, int iz, const std::vector<calibRecord> calibTable)
{
  double calibConst(-100);
  // find the index from the calibTable
  for(int i=0; i<(int)calibTable.size(); i++)
  {
    if (ix==calibTable.at(i).ix && 
        iy==calibTable.at(i).iy &&
        iz==calibTable.at(i).iz)
    {
      calibConst = calibTable.at(i).c;
      return calibConst;
    }
  }
  //
  // Note here, if cannot find an entry in the calibTable,
  // the preset number -100 will be returned.
  return calibConst;
}


double calibCell(double E, int ix, int iy, int iz, const std::vector<calibRecord>& calibTable)
{
  double calibConst = getCalibConstFromCalibTable(ix, iy, iz, calibTable);
  // if cannot find the cell return its original energy
  if (calibConst<=0.0) {
    return E;
  }
  // if good, return the calibrated energy
  return calibConst*E;
}

  
double GetCalibConstFromCalibTable(const int& ix, const int& iy, const int& iz, 
      const std::map<int, std::map<int, std::map<int, calibRecord> > >& calibMap)
{
  std::map<int, std::map<int, std::map<int, calibRecord> > >::const_iterator _it_ix;
  std::map<int, std::map<int, calibRecord> >::const_iterator _it_iy;
  std::map<int, calibRecord>::const_iterator _it_iz;
  // check ix
  _it_ix = calibMap.find(ix);
  if (_it_ix == calibMap.end()) return -1000.0 ;
  // check iy
  _it_iy = (_it_ix->second).find(iy);
  if (_it_iy == (_it_ix->second).end()) return -1000.0;
  // check iz
  _it_iz = (_it_iy->second).find(iz);
  if (_it_iz == (_it_iy->second).end()) return -1000.0;
  // 
  return _it_iz->second.c ;

}

TH1D* getTH1DMeeWithEtaScale(TChain* tree, TChain* extree,
                 const std::vector<calibRecord>& calibTable,
                 const std::vector<EnergyScale>& EtaScale,
                 const char* histname = "hist",
                 const int nbins=60,
                 const int maxevt=-1,
                 const int method=7,
                 const double scale=1.0)
{

  // new a histogram
  TH1D* hist = new TH1D(histname, histname, nbins, 60,120);
  hist->Sumw2();
  hist->GetXaxis()->SetTitle("M(ee) (GeV)");
  hist->GetYaxis()->SetTitle("nEvents");
  hist->SetMarkerStyle(20);
  hist->SetTitle(histname);

  // re-format calibTable to calibMap for fast access
  std::map<int, std::map<int, std::map<int, calibRecord> > > calibMap;
  // directly refer to the one that is given
  for (int idx=0; idx<(int)calibTable.size(); idx++)
  {
    calibRecord record = calibTable.at(idx);
    calibMap[record.ix][record.iy][record.iz] = record;
  }

  //
  int nevts = (int)tree->GetEntries();

  // fill data vectors
  for (int i=0; i<nevts; i++)
  {
    // get event from tree
    tree->GetEntry(i);
    extree->GetEntry(i);

    // Energy
    double E1 = rawEnergySCEle[0]+esEnergySCEle[0];
    double E2 = rawEnergySCEle[1]+esEnergySCEle[1];

    if (method==7) 
    {
      // similar to method2, but on top of energy regression

      // regression energy
      double EReg1 = energySCEle_regrCorrSemiParV8_ele[0];
      double EReg2 = energySCEle_regrCorrSemiParV8_ele[0];
      double RegScale1 = EReg1/E1;
      double RegScale2 = EReg2/E2;

      // recalib E1
      for (int ii=0; ii<(int)energyRecHitSCEle1->size(); ii++)
      {
        double hitE = energyRecHitSCEle1->at(ii);
        int hitIX = XRecHitSCEle1->at(ii);
        int hitIY = YRecHitSCEle1->at(ii);
        int hitIZ = 0;
        if (etaSCEle[0]<-1.49) hitIZ = -1;
        else if (etaSCEle[0]>=-1.49&&etaSCEle[0]<=1.49) hitIZ = 0;
        else hitIZ = 1;
   
        double CalibC = GetCalibConstFromCalibTable(hitIX, hitIY, hitIZ, calibMap);
        double Eold = hitE;
        double Enew = Eold * CalibC * scale;

        if (CalibC>-900.0)
        {
          //calculate new Energy as :
          // Ecorr = E - Sum(Eraw_i) + Sum(Eraw_i * C_i)
          E1 = E1 - Eold + Enew;
        }
      }

      // recalib E2
      for (int ii=0; ii<(int)energyRecHitSCEle2->size(); ii++)
      {
        double hitE = energyRecHitSCEle2->at(ii);
        int hitIX = XRecHitSCEle2->at(ii);
        int hitIY = YRecHitSCEle2->at(ii);
        int hitIZ = 0;
        if (etaSCEle[1]<-1.49) hitIZ = -1;
        else if (etaSCEle[1]>=-1.49&&etaSCEle[1]<=1.49) hitIZ = 0;
        else hitIZ = 1;

        double CalibC = GetCalibConstFromCalibTable(hitIX, hitIY, hitIZ, calibMap);
        double Eold = hitE;
        double Enew = Eold * CalibC * scale;

        if (CalibC>-900.0)
        {
          //calculate new Energy as :
          // Ecorr = E - Sum(Eraw_i) + Sum(Eraw_i * C_i)
          E2 = E2 - Eold + Enew;
        }
      }

      // apply regression scale
      E1 = E1 * RegScale1;
      E2 = E2 * RegScale2;

      // eta scale
      double scale1(1.0), scale2(1.0);
      for (int ibin=0; ibin<(int)EtaScale.size(); ibin++)
      {
        if (etaEle[0]>EtaScale.at(ibin).min&&etaEle[0]<EtaScale.at(ibin).max) scale1 = EtaScale.at(ibin).s;
        if (etaEle[1]>EtaScale.at(ibin).min&&etaEle[1]<EtaScale.at(ibin).max) scale2 = EtaScale.at(ibin).s;
      }

      // calculate mass
      double mee = calcMass(E1*scale1, etaEle[0], phiEle[0], E2*scale2, etaEle[1], phiEle[1]);

      // fill
      hist->Fill(mee);
    }

    // print
    if(i%10000==0)
    {
      std::cout << "Events " << i << std::endl;
    }

    //
    if (maxevt!=-1&&i>maxevt)
    {
      break;
    }
  }

  return hist;
}

/////////
TH1D* getTH1DMeeWithEtaScaleABCD(TChain* tree, TChain* extree,
                 const std::vector<calibRecord>& calibTable,
                 const std::vector<EnergyScale>& EtaScaleA,
                 const std::vector<EnergyScale>& EtaScaleB,
                 const std::vector<EnergyScale>& EtaScaleC,
                 const std::vector<EnergyScale>& EtaScaleD,
                 const char* histname = "hist",
                 const int nbins=60,
                 const int maxevt=-1,
                 const int method=7,
                 const double scale=1.0,
                 const int oddeven=0)
{

  // new a histogram
  TH1D* hist = new TH1D(histname, histname, nbins, 60,120);
  hist->Sumw2();
  hist->GetXaxis()->SetTitle("M(ee) (GeV)");
  hist->GetYaxis()->SetTitle("nEvents");
  hist->SetMarkerStyle(20);
  hist->SetTitle(histname);

  // re-format calibTable to calibMap for fast access
  std::map<int, std::map<int, std::map<int, calibRecord> > > calibMap;
  // directly refer to the one that is given
  for (int idx=0; idx<(int)calibTable.size(); idx++)
  {
    calibRecord record = calibTable.at(idx);
    calibMap[record.ix][record.iy][record.iz] = record;
  }

  // ABCD runNum range
  const int Amin(190645), Amax(193621);
  const int Bmin(193834), Bmax(196531);
  const int Cmin(198022), Cmax(203742);
  const int Dmin(203777), Dmax(208686);

  // counts
  int NumA(0), NumB(0), NumC(0), NumD(0), NumAll(0);

  //
  int nevts = (int)tree->GetEntries();

  // fill data vectors
  for (int i=0; i<nevts; i++)
  {
    // get event from tree
    tree->GetEntry(i);
    extree->GetEntry(i);

     // even odd event check
    if (oddeven==1 && eventNumber%2==0) continue;
    else if (oddeven==2 && eventNumber%2==1) continue;

    // define an empty reference EtaScale vector
    const std::vector<EnergyScale> *EtaScale;

    // check run range
    if (runNumber>=Amin&&runNumber<=Amax) { EtaScale = &EtaScaleA; NumA++;}
    else if (runNumber>=Bmin&&runNumber<=Bmax) { EtaScale = &EtaScaleB; NumB++;}
    else if (runNumber>=Cmin&&runNumber<=Cmax) { EtaScale = &EtaScaleC; NumC++;}
    else if (runNumber>=Dmin&&runNumber<=Dmax) { EtaScale = &EtaScaleD; NumD++;}
    else continue;

    NumAll++;

    // Energy
    double E1 = rawEnergySCEle[0]+esEnergySCEle[0]; 
    double E2 = rawEnergySCEle[1]+esEnergySCEle[1];

    if (method==71)
    {
      // similar to method2, but on top of energy regression

      // regression energy
      double EReg1 = energySCEle_regrCorrSemiParV8_ele[0];
      double EReg2 = energySCEle_regrCorrSemiParV8_ele[1];
      double RegScale1 = EReg1/E1;
      double RegScale2 = EReg2/E2;

      // recalib E1
      for (int ii=0; ii<(int)energyRecHitSCEle1->size(); ii++)
      {
        double hitE = energyRecHitSCEle1->at(ii);
        int hitIX = XRecHitSCEle1->at(ii);
        int hitIY = YRecHitSCEle1->at(ii);
        int hitIZ = 0;
        if (etaSCEle[0]<-1.49) hitIZ = -1;
        else if (etaSCEle[0]>=-1.49&&etaSCEle[0]<=1.49) hitIZ = 0;
        else hitIZ = 1;

        double CalibC = GetCalibConstFromCalibTable(hitIX, hitIY, hitIZ, calibMap);
        double Eold = hitE;
        double Enew = Eold * CalibC * scale;

        if (CalibC>-900.0)
        {
          //calculate new Energy as :
          // Ecorr = E - Sum(Eraw_i) + Sum(Eraw_i * C_i)
          E1 = E1 - Eold + Enew;
        }
      }

      // recalib E2
      for (int ii=0; ii<(int)energyRecHitSCEle1->size(); ii++)
      {
        double hitE = energyRecHitSCEle2->at(ii);
        int hitIX = XRecHitSCEle2->at(ii);
        int hitIY = YRecHitSCEle2->at(ii);
        int hitIZ = 0;
        if (etaSCEle[1]<-1.49) hitIZ = -1;
        else if (etaSCEle[1]>=-1.49&&etaSCEle[1]<=1.49) hitIZ = 0;
        else hitIZ = 1;

        double CalibC = GetCalibConstFromCalibTable(hitIX, hitIY, hitIZ, calibMap);
        double Eold = hitE;
        double Enew = Eold * CalibC * scale;

        if (CalibC>-900.0)
        {
          //calculate new Energy as :
          // Ecorr = E - Sum(Eraw_i) + Sum(Eraw_i * C_i)
          E2 = E2 - Eold + Enew;
        }
      }

      // apply regression scale
      E1 = E1 * RegScale1;
      E2 = E2 * RegScale2;

      // eta scale
      double scale1(1.0), scale2(1.0);
      for (int ibin=0; ibin<(int)EtaScale->size(); ibin++)
      {
        if (etaEle[0]>EtaScale->at(ibin).min&&etaEle[0]<EtaScale->at(ibin).max) scale1 = EtaScale->at(ibin).s;
        if (etaEle[1]>EtaScale->at(ibin).min&&etaEle[1]<EtaScale->at(ibin).max) scale2 = EtaScale->at(ibin).s;
      }

      // calculate mass
      double mee = calcMass(E1*scale1, etaEle[0], phiEle[0], E2*scale2, etaEle[1], phiEle[1]);

      // fill
      hist->Fill(mee);
    }

    // print
    if(i%10000==0)
    {
      std::cout << "Events " << i << std::endl;
    }

    //
    if (maxevt!=-1&&i>maxevt)
    {
      break;
    }
  }

  return hist;
}

////////
/////////
TH1D* getTH1DMeeWithEtaRingEtaScaleABCD(TChain* tree, TChain* extree, 
                 const std::vector<calibRecord>& calibTable,
                 const std::vector<EtaRingEnergyScale>& EtaScaleA,
                 const std::vector<EtaRingEnergyScale>& EtaScaleB,
                 const std::vector<EtaRingEnergyScale>& EtaScaleC,
                 const std::vector<EtaRingEnergyScale>& EtaScaleD,
                 const char* histname = "hist",
                 const int nbins=60,
                 const int maxevt=-1,
                 const int method=72,
                 const double scale=1.0,
                 const int oddeven=0,
                 const std::string regVersion = "RegV8")
{

  // new a histogram
  TH1D* hist = new TH1D(histname, histname, nbins, 60,120);
  hist->Sumw2();
  hist->GetXaxis()->SetTitle("M(ee) (GeV)");
  hist->GetYaxis()->SetTitle("nEvents");
  hist->SetMarkerStyle(20);
  hist->SetTitle(histname);

  // re-format calibTable to calibMap for fast access
  std::map<int, std::map<int, std::map<int, calibRecord> > > calibMap;
  // directly refer to the one that is given
  for (int idx=0; idx<(int)calibTable.size(); idx++)
  {
    calibRecord record = calibTable.at(idx);
    calibMap[record.ix][record.iy][record.iz] = record;
  }

  // ABCD runNum range
  const int Amin(190645), Amax(193621);
  const int Bmin(193834), Bmax(196531);
  const int Cmin(198022), Cmax(203742);
  const int Dmin(203777), Dmax(208686);

  // counts
  int NumA(0), NumB(0), NumC(0), NumD(0), NumAll(0);

  //
  int nevts = (int)tree->GetEntries();

  // fill data vectors
  for (int i=0; i<nevts; i++)
  {
    // get event from tree
    tree->GetEntry(i);
    extree->GetEntry(i);

     // even odd event check
    if (oddeven==1 && eventNumber%2==0) continue;
    else if (oddeven==2 && eventNumber%2==1) continue;

    // define an empty reference EtaScale vector
    const std::vector<EtaRingEnergyScale> *EtaScale;

    // check run range
    if (runNumber>=Amin&&runNumber<=Amax) { EtaScale = &EtaScaleA; NumA++;}
    else if (runNumber>=Bmin&&runNumber<=Bmax) { EtaScale = &EtaScaleB; NumB++;}
    else if (runNumber>=Cmin&&runNumber<=Cmax) { EtaScale = &EtaScaleC; NumC++;}
    else if (runNumber>=Dmin&&runNumber<=Dmax) { EtaScale = &EtaScaleD; NumD++;}
    else continue;
    NumAll++;

    // Energy
    // Energy
    double E1 = rawEnergySCEle[0]+esEnergySCEle[0];
    double E2 = rawEnergySCEle[1]+esEnergySCEle[1];

    if (method==72)
    {
      // similar to method2, but on top of energy regression

      // regression energy
      double EReg1(0), EReg2(0);
      if (regVersion=="RegV8")
      {
        EReg1 = energySCEle_regrCorrSemiParV8_ele[0];
        EReg2 = energySCEle_regrCorrSemiParV8_ele[1];
      }
      else if (regVersion=="RegV6")
      {
        EReg1 = energySCEle_regrCorrSemiParV6_ele[0];
        EReg2 = energySCEle_regrCorrSemiParV6_ele[1];
      }
      else if (regVersion=="RegV5")
      {
        EReg1 = energySCEle_regrCorrSemiParV5_ele[0];
        EReg2 = energySCEle_regrCorrSemiParV5_ele[1];
      }
      else if (regVersion=="RegV7")
      {
        EReg1 = energySCEle_regrCorrSemiParV7_ele[0];
        EReg2 = energySCEle_regrCorrSemiParV7_ele[1];
      }

      // reg scale
      double RegScale1 = EReg1/E1;
      double RegScale2 = EReg2/E2;

      // recalib E1
      for (int ii=0; ii<(int)energyRecHitSCEle1->size(); ii++)
      {
        double hitE = energyRecHitSCEle1->at(ii);
        int hitIX = XRecHitSCEle1->at(ii);
        int hitIY = YRecHitSCEle1->at(ii);
        int hitIZ = 0;
        if (etaSCEle[0]<-1.49) hitIZ = -1;
        else if (etaSCEle[0]>=-1.49&&etaSCEle[0]<=1.49) hitIZ = 0;
        else hitIZ = 1;
        double CalibC = GetCalibConstFromCalibTable(hitIX, hitIY, hitIZ, calibMap);
        double Eold = hitE;
        double Enew = Eold * CalibC * scale;

        if (CalibC>-900.0)
        {
          //calculate new Energy as :
          // Ecorr = E - Sum(Eraw_i) + Sum(Eraw_i * C_i)
          E1 = E1 - Eold + Enew;
        }
      }
      // recalib E2
      for (int ii=0; ii<(int)energyRecHitSCEle2->size(); ii++)
      {
        double hitE = energyRecHitSCEle2->at(ii);
        int hitIX = XRecHitSCEle2->at(ii);
        int hitIY = YRecHitSCEle2->at(ii);
        int hitIZ = 0;
        if (etaSCEle[1]<-1.49) hitIZ = -1;
        else if (etaSCEle[1]>=-1.49&&etaSCEle[1]<=1.49) hitIZ = 0;
        else hitIZ = 1;
        double CalibC = GetCalibConstFromCalibTable(hitIX, hitIY, hitIZ, calibMap);
        double Eold = hitE;
        double Enew = Eold * CalibC * scale;

        if (CalibC>-900.0)
        {
          //calculate new Energy as :
          // Ecorr = E - Sum(Eraw_i) + Sum(Eraw_i * C_i)
          E2 = E2 - Eold + Enew;
        }
      }

      // apply regression scale
      E1 = E1 * RegScale1;
      E2 = E2 * RegScale2;
      // eta scale
      double scale1(1.0), scale2(1.0);
      for (int ibin=0; ibin<(int)EtaScale->size(); ibin++)
      {
        int SeedIX1 = seedXSCEle[0];
        int SeedIY1 = seedYSCEle[0];
        int SeedIZ1 = 0;
        if (etaSCEle[0]<-1.49) SeedIZ1 = -1;
        else if (etaSCEle[0]>=-1.49&&etaSCEle[0]<=1.49) SeedIZ1 = 0;
        else SeedIZ1 = 1;

        int SeedIX2 = seedXSCEle[1];
        int SeedIY2 = seedYSCEle[1];
        int SeedIZ2 = 0;
        if (etaSCEle[1]<-1.49) SeedIZ2 = -1;
        else if (etaSCEle[1]>=-1.49&&etaSCEle[1]<=1.49) SeedIZ2 = 0;
        else SeedIZ2 = 1;

        if (GetEtaRing(SeedIX1, SeedIY1, SeedIZ1)==EtaScale->at(ibin).EtaRing) scale1 = EtaScale->at(ibin).s;
        if (GetEtaRing(SeedIX2, SeedIY2, SeedIZ2)==EtaScale->at(ibin).EtaRing) scale2 = EtaScale->at(ibin).s;
      }

      // calculate mass
      double mee = calcMass(E1*scale1, etaEle[0], phiEle[0], E2*scale2, etaEle[1], phiEle[1]);

      // fill
      hist->Fill(mee);
    }

    // print
    if(i%10000==0)
    {
      std::cout << "Events " << i << std::endl;
    }

    //
    if (maxevt!=-1&&i>maxevt)
    {
      break;
    }
  }

  return hist;
}

////////


//////////


TH1D* getTH1DMee(TChain* tree, TChain* extree, 
                 const std::vector<calibRecord>& calibTable, 
                 const char* histname = "hist", 
                 const int nbins=60,
                 const int maxevt=-1,
                 const int method=2,
                 const double scale=1.0,
                 const int oddeven=0)
{
  
  // new a histogram
  TH1D* hist = new TH1D(histname, histname, nbins, 60,120);
  hist->Sumw2();
  hist->GetXaxis()->SetTitle("M(ee) (GeV)");
  hist->GetYaxis()->SetTitle("nEvents");
  hist->SetMarkerStyle(20);
  hist->SetTitle(histname);
  
  // re-format calibTable to calibMap for fast access
  std::map<int, std::map<int, std::map<int, calibRecord> > > calibMap;
  // directly refer to the one that is given
  for (int idx=0; idx<(int)calibTable.size(); idx++)
  {
    calibRecord record = calibTable.at(idx);
    calibMap[record.ix][record.iy][record.iz] = record;
  }
    
  //
  int nevts = (int)tree->GetEntries();
  // fill data vectors
  for (int i=0; i<nevts; i++)
  {
     // even odd event check
    if (oddeven==1 && eventNumber%2==0) continue;
    else if (oddeven==2 && eventNumber%2==1) continue;

    // get event from tree
    tree->GetEntry(i);
    extree->GetEntry(i);

    // Energy
    double E1 = rawEnergySCEle[0]+esEnergySCEle[0]; //rE[0];
    double E2 = rawEnergySCEle[1]+esEnergySCEle[1]; //rE[1];
    
    
    if (method==2) 
    {
      // recalib E1
      for (int ii=0; ii<(int)energyRecHitSCEle1->size(); ii++)
      {
        double hitE = energyRecHitSCEle1->at(ii);
        int hitIX = XRecHitSCEle1->at(ii);
        int hitIY = YRecHitSCEle1->at(ii);
        int hitIZ = 0;
        if (etaSCEle[0]<-1.49) hitIZ = -1;
        else if (etaSCEle[0]>=-1.49&&etaSCEle[0]<=1.49) hitIZ = 0;
        else hitIZ = 1;

        double CalibC = GetCalibConstFromCalibTable(hitIX, hitIY, hitIZ, calibMap);
        double Eold = hitE;
        double Enew = Eold * CalibC * scale;
      
        if (CalibC>-900.0)
        {
          //calculate new Energy as :
          // Ecorr = E - Sum(Eraw_i) + Sum(Eraw_i * C_i)
          E1 = E1 - Eold + Enew;
        }
      }
    
      // recalib E2
      for (int ii=0; ii<(int)energyRecHitSCEle2->size(); ii++)
      {
        double hitE = energyRecHitSCEle2->at(ii);
        int hitIX = XRecHitSCEle2->at(ii);
        int hitIY = YRecHitSCEle2->at(ii);
        int hitIZ = 0;
        if (etaSCEle[1]<-1.49) hitIZ = -1;
        else if (etaSCEle[1]>=-1.49&&etaSCEle[1]<=1.49) hitIZ = 0;
        else hitIZ = 1;

        double CalibC = GetCalibConstFromCalibTable(hitIX, hitIY, hitIZ, calibMap);
        double Eold = hitE;
        double Enew = Eold * CalibC * scale;
      
        if (CalibC>-900.0)
        {
          //calculate new Energy as :
          // Ecorr = E - Sum(Eraw_i) + Sum(Eraw_i * C_i)
          E2 = E2 - Eold + Enew;
        }
      }
      
      // calculate mass
      double mee = calcMass(E1, etaEle[0], phiEle[0], E2, etaEle[1], phiEle[1]);
      
      // fill
      hist->Fill(mee);
    
    }
    if (method==23)
    {
      // similar to method2, but on top of energy regression

      // regression energy
      double EReg1 = energySCEle_regrCorrSemiParV8_ele[0];
      double EReg2 = energySCEle_regrCorrSemiParV8_ele[1];
      double RegScale1 = EReg1/E1;
      double RegScale2 = EReg2/E2;

      // recalib E1
      for (int ii=0; ii<(int)energyRecHitSCEle1->size(); ii++)
      {
        double hitE = energyRecHitSCEle1->at(ii);
        int hitIX = XRecHitSCEle1->at(ii);
        int hitIY = YRecHitSCEle1->at(ii);
        int hitIZ = 0;
        if (etaSCEle[0]<-1.49) hitIZ = -1;
        else if (etaSCEle[0]>=-1.49&&etaSCEle[0]<=1.49) hitIZ = 0;
        else hitIZ = 1;

        double CalibC = GetCalibConstFromCalibTable(hitIX, hitIY, hitIZ, calibMap);
        double Eold = hitE;
        double Enew = Eold * CalibC * scale;

        if (CalibC>-900.0)
        {
          //calculate new Energy as :
          // Ecorr = E - Sum(Eraw_i) + Sum(Eraw_i * C_i)
          E1 = E1 - Eold + Enew;
        }
      }

      // recalib E2
      for (int ii=0; ii<(int)energyRecHitSCEle2->size(); ii++)
      {
        double hitE = energyRecHitSCEle2->at(ii);
        int hitIX = XRecHitSCEle2->at(ii);
        int hitIY = YRecHitSCEle2->at(ii);
        int hitIZ = 0;
        if (etaSCEle[1]<-1.49) hitIZ = -1;
        else if (etaSCEle[1]>=-1.49&&etaSCEle[1]<=1.49) hitIZ = 0;
        else hitIZ = 1;

        double CalibC = GetCalibConstFromCalibTable(hitIX, hitIY, hitIZ, calibMap);
        double Eold = hitE;
        double Enew = Eold * CalibC * scale;

        if (CalibC>-900.0)
        {
          //calculate new Energy as :
          // Ecorr = E - Sum(Eraw_i) + Sum(Eraw_i * C_i)
          E2 = E2 - Eold + Enew;
        }
      }

      // apply regression scale
      E1 = E1 * RegScale1;
      E2 = E2 * RegScale2;

      // calculate mass
      double mee = calcMass(E1, etaEle[0], phiEle[0], E2, etaEle[1], phiEle[1]);

      // fill
      hist->Fill(mee);

    }
    else if (method==3)
    {
      // method 3:
      // only recalculate one of the two
      // even ievt for E1, odd ievt for E2
      // the other take GsfElectron
      // take E1  or E2
      bool takeE1(false);
      bool takeE2(false);
      // even or odd
      if (i%2==0) takeE2 = true;
      else takeE1 = true;
      
      // dE1 = Sum(-Eold + Enew)
      double dE1(0);
      
      // recalib E1
      if (takeE1) 
      for (int ii=0; ii<(int)energyRecHitSCEle1->size(); ii++)
      {
        double hitE = energyRecHitSCEle1->at(ii);
        int hitIX = XRecHitSCEle1->at(ii);
        int hitIY = YRecHitSCEle1->at(ii);
        int hitIZ = 0;
        if (etaSCEle[0]<-1.49) hitIZ = -1;
        else if (etaSCEle[0]>=-1.49&&etaSCEle[0]<=1.49) hitIZ = 0;
        else hitIZ = 1;

        double CalibC = GetCalibConstFromCalibTable(hitIX, hitIY, hitIZ, calibMap);
        double Eold = hitE;
        double Enew = Eold * CalibC * scale;
      
        if (CalibC>-900.0)
        {
          //calculate new Energy as :
          // dEcorr = 0 - Sum(Eraw_i) + Sum(Eraw_i * C_i)
          dE1 = dE1 - Eold + Enew;
        }
      }
    
      // check if take E1
      if (takeE1) E1 = E1 + dE1;
                
                
      // dE2 = Sum(-Eold + Enew)
      double dE2(0);   
    
      // recalib E2
      if (takeE2)
      for (int ii=0; ii<(int)energyRecHitSCEle2->size(); ii++)
      {
        double hitE = energyRecHitSCEle2->at(ii);
        int hitIX = XRecHitSCEle2->at(ii);
        int hitIY = YRecHitSCEle2->at(ii);
        int hitIZ = 0;
        if (etaSCEle[1]<-1.49) hitIZ = -1;
        else if (etaSCEle[1]>=-1.49&&etaSCEle[1]<=1.49) hitIZ = 0;
        else hitIZ = 1;

        double CalibC = GetCalibConstFromCalibTable(hitIX, hitIY, hitIZ, calibMap);
        double Eold = hitE;
        double Enew = Eold * CalibC * scale;
      
        if (CalibC>-900.0)
        {
          //calculate new Energy as :
          // dEcorr = 0 - Sum(Eraw_i) + Sum(Eraw_i * C_i)
          dE2 = dE2 - Eold + Enew;
        }
      }
      
      // check if take E2
      if (takeE2) E2 = E2 + dE2;
      
      // calculate mass
      double mee = calcMass(E1, etaEle[0], phiEle[0], E2, etaEle[1], phiEle[1]);
      
      // fill
      hist->Fill(mee);
      
    }
    else if (method==31)
    {
      // method 31:
      // one recalculate one GsfElectron
      // repeat for the two
      // i.e. fill two Mee for each event for the two possible combinations.

      
      // dE1 = Sum(-Eold + Enew)
      double dE1(0);
      
      // recalib E1
      for (int ii=0; ii<(int)energyRecHitSCEle1->size(); ii++)
      {
        double hitE = energyRecHitSCEle1->at(ii);
        int hitIX = XRecHitSCEle1->at(ii);
        int hitIY = YRecHitSCEle1->at(ii);
        int hitIZ = 0;
        if (etaSCEle[0]<-1.49) hitIZ = -1;
        else if (etaSCEle[0]>=-1.49&&etaSCEle[0]<=1.49) hitIZ = 0;
        else hitIZ = 1;

        double CalibC = GetCalibConstFromCalibTable(hitIX, hitIY, hitIZ, calibMap);
        double Eold = hitE;
        double Enew = Eold * CalibC * scale;
      
        if (CalibC>-900.0)
        {
          //calculate new Energy as :
          // dEcorr = 0 - Sum(Eraw_i) + Sum(Eraw_i * C_i)
          dE1 = dE1 - Eold + Enew;
        }
      }
    
      // calculate mass for recalib E1 + GsfElectron of E2
      double mee1 = calcMass(E1+dE1, etaEle[0], phiEle[0], E2, etaEle[1], phiEle[1]);
      
      // fill
      hist->Fill(mee1);
                
                
      // dE2 = Sum(-Eold + Enew)
      double dE2(0);   
    
      // recalib E2
      for (int ii=0; ii<(int)energyRecHitSCEle2->size(); ii++)
      {
        double hitE = energyRecHitSCEle2->at(ii);
        int hitIX = XRecHitSCEle2->at(ii);
        int hitIY = YRecHitSCEle2->at(ii);
        int hitIZ = 0;
        if (etaSCEle[1]<-1.49) hitIZ = -1;
        else if (etaSCEle[1]>=-1.49&&etaSCEle[1]<=1.49) hitIZ = 0;
        else hitIZ = 1;

        double CalibC = GetCalibConstFromCalibTable(hitIX, hitIY, hitIZ, calibMap);
        double Eold = hitE;
        double Enew = Eold * CalibC * scale;
      
        if (CalibC>-900.0)
        {
          //calculate new Energy as :
          // dEcorr = 0 - Sum(Eraw_i) + Sum(Eraw_i * C_i)
          dE2 = dE2 - Eold + Enew;
        }
      }
      
      // calculate mass for recalib E2 + GsfElectron of E1
      double mee2 = calcMass(E1, etaEle[0], phiEle[0], E2+dE2, etaEle[1], phiEle[1]);
      
      // fill
      hist->Fill(mee2);
      
    }

    
    // print
    if(i%10000==0)
    {
      std::cout << "Events " << i << std::endl;
    }
    
    //
    if (maxevt!=-1&&i>maxevt)
    {
      break;
    }
  }
  
  return hist;
}




TH1D* getTH1DOriginalMee(TChain* tree, 
                         const char* histname = "hist", 
                         const int nbins=60, 
                         const int maxevt=-1,
                         const double scale=1.0,
                         const int oddeven=0)
{
  
  // new a histogram
  TH1D* hist = new TH1D(histname, histname, nbins, 60,120);
  hist->Sumw2();
  hist->GetXaxis()->SetTitle("M(ee) (GeV)");
  hist->GetYaxis()->SetTitle("nEvents");
  hist->SetMarkerStyle(20);
  hist->SetTitle(histname);
  
  int nevts = (int)tree->GetEntries();
  // fill data vectors
  for (int i=0; i<nevts; i++){

    // even odd event check
    if (oddeven==1 && eventNumber%2==0) continue;
    else if (oddeven==2 && eventNumber%2==1) continue;

    // get event from tree
    tree->GetEntry(i);

    // Energy
    double E1 = rawEnergySCEle[0]+esEnergySCEle[0]; //rE[0];
    double E2 = rawEnergySCEle[1]+esEnergySCEle[1]; //rE[1];
    
    // calculate mass
    double mee = calcMass(E1, etaEle[0], phiEle[0], E2, etaEle[1], phiEle[1]);
    
    // apply scale
    mee = mee*scale;
    
    // fill
    hist->Fill(mee);
    
    //
    if (maxevt!=-1&&i>maxevt)
    {
      break;
    }
  }
  
  return hist;
}


TH1D* getTH1DMeeRegV8ElecWithEtaScale(TChain* tree,
                         const std::vector<EnergyScale>& EtaScale,
                         const char* histname = "hist",
                         const int nbins=60,
                         const int maxevt=-1,
                         const double scale=1.0)
{

  // new a histogram
  TH1D* hist = new TH1D(histname, histname, nbins, 60,120);
  hist->Sumw2();
  hist->GetXaxis()->SetTitle("M(ee) (GeV)");
  hist->GetYaxis()->SetTitle("nEvents");
  hist->SetMarkerStyle(20);
  hist->SetTitle(histname);

  int nevts = (int)tree->GetEntries();
  // fill data vectors
  for (int i=0; i<nevts; i++){
    // get event from tree
    tree->GetEntry(i);

    double scale1(1.0), scale2(1.0);
    for (int ibin=0; ibin<(int)EtaScale.size(); ibin++)
    {
      if (etaEle[0]>EtaScale.at(ibin).min&&etaEle[0]<EtaScale.at(ibin).max) scale1 = EtaScale.at(ibin).s; 
      if (etaEle[1]>EtaScale.at(ibin).min&&etaEle[1]<EtaScale.at(ibin).max) scale2 = EtaScale.at(ibin).s; 
    }

    // calculate mass
    double mee = calcMass(energySCEle_regrCorrSemiParV8_ele[0]*scale1, etaEle[0], phiEle[0], energySCEle_regrCorrSemiParV8_ele[1]*scale2, etaEle[1], phiEle[1]);

    mee = mee*scale;

    // fill
    hist->Fill(mee);

    //
    if (maxevt!=-1&&i>maxevt)
    {
      break;
    }
  }

  return hist;
}
///////////

TH1D* getTH1DMeeRegV8ElecWithEtaScaleABCD(TChain* tree,
                         const std::vector<EnergyScale>& EtaScaleA,
                         const std::vector<EnergyScale>& EtaScaleB,
                         const std::vector<EnergyScale>& EtaScaleC,
                         const std::vector<EnergyScale>& EtaScaleD,
                         const char* histname = "hist",
                         const int nbins=60,
                         const int maxevt=-1,
                         const double scale=1.0,
                         const int oddeven=0)
{

  // new a histogram
  TH1D* hist = new TH1D(histname, histname, nbins, 60,120);
  hist->Sumw2();
  hist->GetXaxis()->SetTitle("M(ee) (GeV)");
  hist->GetYaxis()->SetTitle("nEvents");
  hist->SetMarkerStyle(20);
  hist->SetTitle(histname);

  // ABCD runNum range
  const int Amin(190645), Amax(193621);
  const int Bmin(193834), Bmax(196531);
  const int Cmin(198022), Cmax(203742);
  const int Dmin(203777), Dmax(208686);

  // counts
  int NumA(0), NumB(0), NumC(0), NumD(0), NumAll(0);


  int nevts = (int)tree->GetEntries();
  // fill data vectors
  for (int i=0; i<nevts; i++){
    // get event from tree
    tree->GetEntry(i);

     // even odd event check
    if (oddeven==1 && eventNumber%2==0) continue;
    else if (oddeven==2 && eventNumber%2==1) continue;

    // define an empty reference EtaScale vector
    const std::vector<EnergyScale> *EtaScale;

    // check run range
    if (runNumber>=Amin&&runNumber<=Amax) { EtaScale = &EtaScaleA; NumA++;}
    else if (runNumber>=Bmin&&runNumber<=Bmax) { EtaScale = &EtaScaleB; NumB++;}
    else if (runNumber>=Cmin&&runNumber<=Cmax) { EtaScale = &EtaScaleC; NumC++;}
    else if (runNumber>=Dmin&&runNumber<=Dmax) { EtaScale = &EtaScaleD; NumD++;}
    else continue;

    NumAll++;

    double scale1(1.0), scale2(1.0);
    for (int ibin=0; ibin<(int)EtaScale->size(); ibin++)
    {
      if (etaEle[0]>EtaScale->at(ibin).min&&etaEle[0]<EtaScale->at(ibin).max) scale1 = EtaScale->at(ibin).s;
      if (etaEle[1]>EtaScale->at(ibin).min&&etaEle[1]<EtaScale->at(ibin).max) scale2 = EtaScale->at(ibin).s;
    }

    // calculate mass
    double mee = calcMass(energySCEle_regrCorrSemiParV8_ele[0]*scale1, etaEle[0], phiEle[0], energySCEle_regrCorrSemiParV8_ele[1]*scale2, etaEle[1], phiEle[1]);

    mee = mee*scale;

    // fill
    hist->Fill(mee);

    //
    if (maxevt!=-1&&i>maxevt)
    {
      break;
    }
  }

  return hist;
}

///////
TH1D* getTH1DMeeRegV8Elec(TChain* tree,
                         const char* histname = "hist",
                         const int nbins=60,
                         const int maxevt=-1,
                         const double scale=1.0,
                         const int oddeven=0)
{

  // new a histogram
  TH1D* hist = new TH1D(histname, histname, nbins, 60,120);
  hist->Sumw2();
  hist->GetXaxis()->SetTitle("M(ee) (GeV)");
  hist->GetYaxis()->SetTitle("nEvents");
  hist->SetMarkerStyle(20);
  hist->SetTitle(histname);

  int nevts = (int)tree->GetEntries();
  // fill data vectors
  for (int i=0; i<nevts; i++){

    // even odd event check
    if (oddeven==1 && eventNumber%2==0) continue;
    else if (oddeven==2 && eventNumber%2==1) continue;

    // get event from tree
    tree->GetEntry(i);

    // calculate mass
    double mee = calcMass(energySCEle_regrCorrSemiParV8_ele[0], etaEle[0], phiEle[0], energySCEle_regrCorrSemiParV8_ele[1], etaEle[1], phiEle[1]);

    // apply scale
    mee = mee*scale;

    // fill
    hist->Fill(mee);

    //
    if (maxevt!=-1&&i>maxevt)
    {
      break;
    }
  }

  return hist;
}


///////
TH1D* getTH1DMeeRegElec(TChain* tree,
                         const char* histname = "hist",
                         const int nbins=60,
                         const int maxevt=-1,
                         const double scale=1.0,
                         const int oddeven=0,
                         const std::string regVersion = "RegV8")
{

  // new a histogram
  TH1D* hist = new TH1D(histname, histname, nbins, 60,120);
  hist->Sumw2();
  hist->GetXaxis()->SetTitle("M(ee) (GeV)");
  hist->GetYaxis()->SetTitle("nEvents");
  hist->SetMarkerStyle(20);
  hist->SetTitle(histname);

  int nevts = (int)tree->GetEntries();
  // fill data vectors
  for (int i=0; i<nevts; i++){

    // even odd event check
    if (oddeven==1 && eventNumber%2==0) continue;
    else if (oddeven==2 && eventNumber%2==1) continue;

    // get event from tree
    tree->GetEntry(i);

    double RegE1(0), RegE2(0);

    if (regVersion=="RegV8") 
    {
      RegE1 = energySCEle_regrCorrSemiParV8_ele[0];
      RegE2 = energySCEle_regrCorrSemiParV8_ele[1];
    }
    else if (regVersion=="RegV6")
    {
      RegE1 = energySCEle_regrCorrSemiParV6_ele[0];
      RegE2 = energySCEle_regrCorrSemiParV6_ele[1];
    }
    else if (regVersion=="RegV5")
    {
      RegE1 = energySCEle_regrCorrSemiParV5_ele[0];
      RegE2 = energySCEle_regrCorrSemiParV5_ele[1];
    }
    else if (regVersion=="RegV7")
    {
      RegE1 = energySCEle_regrCorrSemiParV7_ele[0];
      RegE2 = energySCEle_regrCorrSemiParV7_ele[1];
    }
    // calculate mass
    double mee = calcMass(RegE1, etaEle[0], phiEle[0], RegE2, etaEle[1], phiEle[1]);

    // apply scale
    mee = mee*scale;

    // fill
    hist->Fill(mee);

    //
    if (maxevt!=-1&&i>maxevt)
    {
      break;
    }
  }

  return hist;
}
/////////////////////////////////


TH1D* getTH1DMeeRegElecWithEtaScaleABCD(TChain* tree,
                         const std::vector<EnergyScale>& EtaScaleA,
                         const std::vector<EnergyScale>& EtaScaleB,
                         const std::vector<EnergyScale>& EtaScaleC,
                         const std::vector<EnergyScale>& EtaScaleD,
                         const char* histname = "hist",
                         const int nbins=60,
                         const int maxevt=-1,
                         const double scale=1.0,
                         const int oddeven=0,
                         const std::string regVersion = "RegV8")
{

  // new a histogram
  TH1D* hist = new TH1D(histname, histname, nbins, 60,120);
  hist->Sumw2();
  hist->GetXaxis()->SetTitle("M(ee) (GeV)");
  hist->GetYaxis()->SetTitle("nEvents");
  hist->SetMarkerStyle(20);
  hist->SetTitle(histname);

  // ABCD runNum range
  const int Amin(190645), Amax(193621);
  const int Bmin(193834), Bmax(196531);
  const int Cmin(198022), Cmax(203742);
  const int Dmin(203777), Dmax(208686);

  // counts
  int NumA(0), NumB(0), NumC(0), NumD(0), NumAll(0);


  int nevts = (int)tree->GetEntries();
  // fill data vectors
  for (int i=0; i<nevts; i++){
    // get event from tree
    tree->GetEntry(i);

     // even odd event check
    if (oddeven==1 && eventNumber%2==0) continue;
    else if (oddeven==2 && eventNumber%2==1) continue;

    // define an empty reference EtaScale vector
    const std::vector<EnergyScale> *EtaScale;

    // check run range
    if (runNumber>=Amin&&runNumber<=Amax) { EtaScale = &EtaScaleA; NumA++;}
    else if (runNumber>=Bmin&&runNumber<=Bmax) { EtaScale = &EtaScaleB; NumB++;}
    else if (runNumber>=Cmin&&runNumber<=Cmax) { EtaScale = &EtaScaleC; NumC++;}
    else if (runNumber>=Dmin&&runNumber<=Dmax) { EtaScale = &EtaScaleD; NumD++;}
    else continue;

    NumAll++;

    double scale1(1.0), scale2(1.0);
    for (int ibin=0; ibin<(int)EtaScale->size(); ibin++)
    {
      if (etaEle[0]>EtaScale->at(ibin).min&&etaEle[0]<EtaScale->at(ibin).max) scale1 = EtaScale->at(ibin).s;
      if (etaEle[1]>EtaScale->at(ibin).min&&etaEle[1]<EtaScale->at(ibin).max) scale2 = EtaScale->at(ibin).s;
    }

    double RegE1(0), RegE2(0);

    if (regVersion=="RegV8")
    {
      RegE1 = energySCEle_regrCorrSemiParV8_ele[0];
      RegE2 = energySCEle_regrCorrSemiParV8_ele[1];
    }
    else if (regVersion=="RegV6")
    {
      RegE1 = energySCEle_regrCorrSemiParV6_ele[0];
      RegE2 = energySCEle_regrCorrSemiParV6_ele[1];
    }
    else if (regVersion=="RegV5")
    {
      RegE1 = energySCEle_regrCorrSemiParV5_ele[0];
      RegE2 = energySCEle_regrCorrSemiParV5_ele[1];
    }
    else if (regVersion=="RegV7")
    {
      RegE1 = energySCEle_regrCorrSemiParV7_ele[0];
      RegE2 = energySCEle_regrCorrSemiParV7_ele[1];
    }

    // calculate mass
    double mee = calcMass(RegE1*scale1, etaEle[0], phiEle[0], RegE2*scale2, etaEle[1], phiEle[1]);

    mee = mee*scale;

    // fill
    hist->Fill(mee);

    //
    if (maxevt!=-1&&i>maxevt)
    {
      break;
    }
  }

  return hist;
}

/////////////////////
TH1D* getTH1DMeeRegElecWithEtaRingEtaScaleABCD(TChain* tree,
                         const std::vector<EtaRingEnergyScale>& EtaScaleA,
                         const std::vector<EtaRingEnergyScale>& EtaScaleB,
                         const std::vector<EtaRingEnergyScale>& EtaScaleC,
                         const std::vector<EtaRingEnergyScale>& EtaScaleD,
                         const char* histname = "hist",
                         const int nbins=60,
                         const int maxevt=-1,
                         const double scale=1.0,
                         const int oddeven=0,
                         const std::string regVersion = "RegV8")
{

  // new a histogram
  TH1D* hist = new TH1D(histname, histname, nbins, 60,120);
  hist->Sumw2();
  hist->GetXaxis()->SetTitle("M(ee) (GeV)");
  hist->GetYaxis()->SetTitle("nEvents");
  hist->SetMarkerStyle(20);
  hist->SetTitle(histname);

  // ABCD runNum range
  const int Amin(190645), Amax(193621);
  const int Bmin(193834), Bmax(196531);
  const int Cmin(198022), Cmax(203742);
  const int Dmin(203777), Dmax(208686);

  // counts
  int NumA(0), NumB(0), NumC(0), NumD(0), NumAll(0);


  int nevts = (int)tree->GetEntries();
  // fill data vectors
  for (int i=0; i<nevts; i++){
    // get event from tree
    tree->GetEntry(i);

     // even odd event check
    if (oddeven==1 && eventNumber%2==0) continue;
    else if (oddeven==2 && eventNumber%2==1) continue;

    // define an empty reference EtaScale vector
    const std::vector<EtaRingEnergyScale> *EtaScale;

    // check run range
    if (runNumber>=Amin&&runNumber<=Amax) { EtaScale = &EtaScaleA; NumA++;}
    else if (runNumber>=Bmin&&runNumber<=Bmax) { EtaScale = &EtaScaleB; NumB++;}
    else if (runNumber>=Cmin&&runNumber<=Cmax) { EtaScale = &EtaScaleC; NumC++;}
    else if (runNumber>=Dmin&&runNumber<=Dmax) { EtaScale = &EtaScaleD; NumD++;}
    else continue;

    NumAll++;

    double scale1(1.0), scale2(1.0);
    for (int ibin=0; ibin<(int)EtaScale->size(); ibin++)
    {
      int SeedIX1 = seedXSCEle[0];
      int SeedIY1 = seedYSCEle[0];
      int SeedIZ1 = 0;
      if (etaSCEle[0]<-1.49) SeedIZ1 = -1;
      else if (etaSCEle[0]>=-1.49&&etaSCEle[0]<=1.49) SeedIZ1 = 0;
      else SeedIZ1 = 1;

      int SeedIX2 = seedXSCEle[1];
      int SeedIY2 = seedYSCEle[1];
      int SeedIZ2 = 0;
      if (etaSCEle[1]<-1.49) SeedIZ2 = -1;
      else if (etaSCEle[1]>=-1.49&&etaSCEle[1]<=1.49) SeedIZ2 = 0;
      else SeedIZ2 = 1;

      if (GetEtaRing(SeedIX1, SeedIY1, SeedIZ1)==EtaScale->at(ibin).EtaRing) scale1 = EtaScale->at(ibin).s;
      if (GetEtaRing(SeedIX2, SeedIY2, SeedIZ2)==EtaScale->at(ibin).EtaRing) scale2 = EtaScale->at(ibin).s;
    }

    double RegE1(0), RegE2(0);

    if (regVersion=="RegV8")
    {
      RegE1 = energySCEle_regrCorrSemiParV8_ele[0];
      RegE2 = energySCEle_regrCorrSemiParV8_ele[1];
    }
    else if (regVersion=="RegV6")
    {
      RegE1 = energySCEle_regrCorrSemiParV6_ele[0];
      RegE2 = energySCEle_regrCorrSemiParV6_ele[1];
    }
    else if (regVersion=="RegV5")
    {
      RegE1 = energySCEle_regrCorrSemiParV5_ele[0];
      RegE2 = energySCEle_regrCorrSemiParV5_ele[1];
    }
    else if (regVersion=="RegV7")
    {
      RegE1 = energySCEle_regrCorrSemiParV7_ele[0];
      RegE2 = energySCEle_regrCorrSemiParV7_ele[1];
    }

    // calculate mass
    double mee = calcMass(RegE1*scale1, etaEle[0], phiEle[0], RegE2*scale2, etaEle[1], phiEle[1]);

    mee = mee*scale;

    // fill
    hist->Fill(mee);

    //
    if (maxevt!=-1&&i>maxevt)
    {
      break;
    }
  }

  return hist;
}















