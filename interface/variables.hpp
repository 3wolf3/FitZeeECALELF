// Author: Hengne Li @ UVa CERN ,, 2014

#include "TROOT.h"
#include "TChain.h"
#include "Minuit2/MnUserParameters.h"
#include <string>
#include <vector>
#include <utility>
#include <fstream>
#include <sstream>
#include <map>

typedef struct
{
  double min;
  double max;
  double s; // scale
  double serr; // error of scale
} EnergyScale;

typedef struct
{
  int ix;
  int iy;
  int iz;
  double s; // scale
  double serr; // error of scale
} SeedEnergyScale;

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

// define vectors to store data

// store all events
int nEventsAll, nSignalsAll;
std::vector<Int_t> allRunNum;
std::vector<ULong64_t> allEvtNum; 
std::vector<double> allE1, allEReg1, allEta1, allPhi1;
//std::vector<double> allE1, allEta1, allPhi1;
std::vector<double> allE2, allEReg2, allEta2, allPhi2;
//std::vector<double> allE2, allEta2, allPhi2;
std::vector<double> allSCEta1, allSCEta2;
std::vector<int> allnHits1, allnHits2;
std::vector< std::vector<double> > allHitE1, allHitE2;
std::vector< std::vector<int> > allHitIX1, allHitIY1, allHitIZ1;
std::vector< std::vector<int> > allHitIX2, allHitIY2, allHitIZ2;
std::vector<int> allSeedIX1, allSeedIY1, allSeedIZ1;
std::vector<int> allSeedIX2, allSeedIY2, allSeedIZ2;
std::vector<double> allRawEEcal1, allRawEEcal2;
std::vector<int> allScaleBin1, allScaleBin2;
std::vector<double> allRawSCE1, allRawSCE2;
std::vector<double> allRawESE1, allRawESE2;
std::vector<double> allERegScale1, allERegScale2;

// store selected events
int nEvents, nSignals;
std::vector<double*> E1, EReg1, Eta1, Phi1;
//std::vector<double*> E1, Eta1, Phi1;
std::vector<double*> E2, EReg2, Eta2, Phi2;
//std::vector<double*> E2, Eta2, Phi2;
std::vector<int*> nHits1, nHits2;
std::vector< std::vector<double>* > HitE1, HitE2;
std::vector< std::vector<int>* > HitIX1, HitIY1, HitIZ1;
std::vector< std::vector<int>* > HitIX2, HitIY2, HitIZ2;
std::vector<bool> UseEle1, UseEle2;
std::vector<int> ScaleBin1, ScaleBin2;
std::vector<int*> SeedIX1, SeedIY1, SeedIZ1;
std::vector<int*> SeedIX2, SeedIY2, SeedIZ2;
std::vector<double*> RawEEcal1, RawEEcal2;
std::vector<double*> RawSCE1, RawSCE2;
std::vector<double*> RawESE1, RawESE2;
std::vector<double*> ERegScale1, ERegScale2;

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
   /*Float_t         energySCEle_regrCorr_ele[2];
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
   Float_t         energySigmaSCEle_regrCorrSemiPar7TeVtrainV8_pho[2];*/
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
   /*Float_t         invMass_SC_regrCorr_ele;
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
   Float_t         invMass_SC_regrCorrSemiPar7TeVtrainV8_ele;*/
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
   /*tree->SetBranchAddress("energySCEle_regrCorr_ele",energySCEle_regrCorr_ele);
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
   tree->SetBranchAddress("energySigmaSCEle_regrCorrSemiPar7TeVtrainV8_pho",energySigmaSCEle_regrCorrSemiPar7TeVtrainV8_pho);*/
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
   /*tree->SetBranchAddress("invMass_SC_regrCorr_ele",&invMass_SC_regrCorr_ele);
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
   tree->SetBranchAddress("invMass_SC_regrCorrSemiPar7TeVtrainV8_ele",&invMass_SC_regrCorrSemiPar7TeVtrainV8_ele);*/
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


// store all events from the Tree to vectors
void FillAllEvents(TChain* tree, TChain* extree, const int debug=0, const std::string regVersion="V8Elec", const bool fitscale=false, const int doEvenOdd=0)
{
  // build index if !fitscale (i.e. need hits information)
  if (!fitscale) 
  {
    extree->BuildIndex("runNumber","eventNumber");
  }

  nEventsAll = (int)tree->GetEntries();
  nSignalsAll = 0.99999*nEventsAll; // guess a number
  if (debug>1) std::cout << "fill all data vectors: " << nEventsAll << " events Using Regression "<< regVersion << std::endl;

  // fill data vectors
  for (int i=0; i<nEventsAll; i++){
    // get event from tree
    tree->GetEntry(i);
    if(!fitscale)
    {
      extree->GetEntryWithIndex(runNumber, eventNumber);
    }

    // even odd check
    if (doEvenOdd==1 && eventNumber%2==0) continue;
    else if (doEvenOdd==2 && eventNumber%2==1) continue;

    // remove track driven electrons
    if (recoFlagsEle[0]==1||(recoFlagsEle[1]==1&&ZStat==1)) continue; 

    allRunNum.push_back(runNumber);
    allEvtNum.push_back(eventNumber);
  
    // first electron
    //allE1.push_back(rawEnergySCEle[0]); // SC raw as in Regression
    allE1.push_back(rawEnergySCEle[0]+esEnergySCEle[0]); // need to know rawEnergySCEle is ECAL only or including ES?
    /*if(regVersion=="V5Elec") allEReg1.push_back(energySCEle_regrCorrSemiParV5_ele[0]);
    else if(regVersion=="V6Elec") allEReg1.push_back(energySCEle_regrCorrSemiParV6_ele[0]);
    else if(regVersion=="V7Elec") allEReg1.push_back(energySCEle_regrCorrSemiParV7_ele[0]);
    else if(regVersion=="VWElec") allEReg1.push_back(energySCEle_corr[0]);//EVAN
    else allEReg1.push_back(energySCEle_regrCorrSemiParV8_ele[0]);    */
    if(regVersion=="VWElec") allEReg1.push_back(energySCEle_corr[0]);//EVAN

    allERegScale1.push_back(allEReg1.back()/allE1.back());
    allEta1.push_back(etaEle[0]);
    allPhi1.push_back(phiEle[0]);
    allSCEta1.push_back(etaSCEle[0]);
    //allRawEEcal1.push_back(rawEnergySCEle[0]-esEnergySCEle[0]);
    allRawEEcal1.push_back(rawEnergySCEle[0]);
    allRawESE1.push_back(esEnergySCEle[0]);
    allSeedIX1.push_back(seedXSCEle[0]);
    allSeedIY1.push_back(seedYSCEle[0]);
    if (etaSCEle[0]<-1.49) allSeedIZ1.push_back(-1);
    else if (etaSCEle[0]>=-1.49&&etaSCEle[0]<=1.49) allSeedIZ1.push_back(0);
    else allSeedIZ1.push_back(1);

    // if fit scale, then we don't need the following information
    if(!fitscale) 
    {
      allnHits1.push_back((int)energyRecHitSCEle1->size());
      std::vector<double> hitE1;
      std::vector<int> hitIX1, hitIY1, hitIZ1;
      for (int ii=0; ii<(int)energyRecHitSCEle1->size(); ii++){
        hitE1.push_back(energyRecHitSCEle1->at(ii));
        hitIX1.push_back(XRecHitSCEle1->at(ii));
        hitIY1.push_back(YRecHitSCEle1->at(ii));
        if (etaSCEle[0]<-1.49) hitIZ1.push_back(-1);
        else if (etaSCEle[0]>=-1.49&&etaSCEle[0]<=1.49) hitIZ1.push_back(0);
        else hitIZ1.push_back(1);
      }
      allHitE1.push_back(hitE1);
      allHitIX1.push_back(hitIX1);
      allHitIY1.push_back(hitIY1);
      allHitIZ1.push_back(hitIZ1);
    }
    // second electron
    //allE2.push_back(rawEnergySCEle[1]); // SC raw as in Regression
    allE2.push_back(rawEnergySCEle[1]+esEnergySCEle[1]); // 
    /*if(regVersion=="V5Elec") allEReg2.push_back(energySCEle_regrCorrSemiParV5_ele[1]);
    else if(regVersion=="V6Elec") allEReg2.push_back(energySCEle_regrCorrSemiParV6_ele[1]);
    else if(regVersion=="V7Elec") allEReg2.push_back(energySCEle_regrCorrSemiParV7_ele[1]);
    else if(regVersion=="VWElec") allEReg2.push_back(energySCEle_corr[1]);//EVAN
    else allEReg2.push_back(energySCEle_regrCorrSemiParV8_ele[1]); */
    if(regVersion=="VWElec") allEReg2.push_back(energySCEle_corr[1]);//EVAN

    allERegScale2.push_back(allEReg2.back()/allE2.back());
    allEta2.push_back(etaEle[1]);
    allPhi2.push_back(phiEle[1]);
    allSCEta2.push_back(etaSCEle[1]);
    //allRawEEcal2.push_back(rawEnergySCEle[1]-esEnergySCEle[1]);
    allRawEEcal2.push_back(rawEnergySCEle[1]);
    allRawESE2.push_back(esEnergySCEle[1]);
    allSeedIX2.push_back(seedXSCEle[1]);
    allSeedIY2.push_back(seedYSCEle[1]);
    if (etaSCEle[1]<-1.49) allSeedIZ2.push_back(-1);
    else if (etaSCEle[1]>=-1.49&&etaSCEle[1]<=1.49) allSeedIZ2.push_back(0);
    else allSeedIZ2.push_back(1);
    // if fit scale, then we don't need the following information
    if(!fitscale)
    {
      allnHits2.push_back((int)energyRecHitSCEle2->size());
      std::vector<double> hitE2;
      std::vector<int> hitIX2, hitIY2, hitIZ2;
      for (int ii=0; ii<(int)energyRecHitSCEle2->size(); ii++){
        hitE2.push_back(energyRecHitSCEle2->at(ii));
        hitIX2.push_back(XRecHitSCEle2->at(ii));
        hitIY2.push_back(YRecHitSCEle2->at(ii));
        if (etaSCEle[1]<-1.49) hitIZ2.push_back(-1);
        else if (etaSCEle[1]>=-1.49&&etaSCEle[1]<=1.49) hitIZ2.push_back(0);
        else hitIZ2.push_back(1);
      }
      allHitE2.push_back(hitE2);
      allHitIX2.push_back(hitIX2);
      allHitIY2.push_back(hitIY2);
      allHitIZ2.push_back(hitIZ2);
    }
  }
  nEventsAll = (int)allE1.size();
  nSignalsAll = 0.99999*nEventsAll; // guess a number
}


double GetICFromCalibTable(const int& ix, const int& iy, const int& iz, const std::map<int, std::map<int, std::map<int, calibRecord> > >& calibTable) 
{
    std::map<int, std::map<int, std::map<int, calibRecord> > >::const_iterator _it_ix;
    std::map<int, std::map<int, calibRecord> >::const_iterator _it_iy;
    std::map<int, calibRecord>::const_iterator _it_iz;
    // check ix
    _it_ix = calibTable.find(ix);
    if (_it_ix == calibTable.end()) return -1000.0 ;
    // check iy
    _it_iy = (_it_ix->second).find(iy);
    if (_it_iy == (_it_ix->second).end()) return -1000.0;
    // check iz
    _it_iz = (_it_iy->second).find(iz);
    if (_it_iz == (_it_iy->second).end()) return -1000.0;
    //
    return _it_iz->second.c ;

}


// calculate New Raw SC Energy for all Events
void CalculateNewRawSCEnergyForAllEvents(std::map<int, std::map<int, std::map<int, calibRecord> > > calibTable)
{

  int nEventsAll = (int)allE1.size();

  // first make sure I have all Hits energies stored.
  if (nEventsAll != (int) allHitE1.size() ) 
  {
    std::cout << "ERROR:: CalculateNewRawSCEnergyForAllEvents, here I need all Hits Energies. " << std::endl; 
    abort();
  }

  bool doPrint = false;

  //loop over all events
  for (int i=0; i<nEventsAll; i++)
  {
    double NewRawE1 = allE1.at(i);
    double NewRawE2 = allE2.at(i);

    for (int ih=0; ih<allnHits1.at(i); ih++)
    {
      const int ix = allHitIX1.at(i).at(ih);
      const int iy = allHitIY1.at(i).at(ih);
      const int iz = allHitIZ1.at(i).at(ih);
      double icc = GetICFromCalibTable(ix, iy, iz, calibTable);
      if (icc>-900) 
      { 
        NewRawE1 += (icc - 1.0) * allHitE1.at(i).at(ih);
        doPrint=true;
      }
    }

    for (int ih=0; ih<allnHits2.at(i); ih++)
    {
      const int ix = allHitIX2.at(i).at(ih);
      const int iy = allHitIY2.at(i).at(ih);
      const int iz = allHitIZ2.at(i).at(ih);
      double icc = GetICFromCalibTable(ix, iy, iz, calibTable);
      if (icc>-900)
      {
        NewRawE2 += (icc - 1.0) * allHitE2.at(i).at(ih);
        doPrint=true;
      }
    }

    if (doPrint)
    {
    //  std::cout << "RawE1 = " << allE1.at(i) << " NewRawE1 = " << NewRawE1 << std::endl;
    //  std::cout << "RawE2 = " << allE2.at(i) << " NewRawE2 = " << NewRawE2 << std::endl;
    }

    allRawSCE1.push_back(NewRawE1);
    allRawSCE2.push_back(NewRawE2);
    
  }

}


// generate an empty calib table
void GenEmptyCalibTable(std::vector<std::vector<int> > cells, const char* filename = "EmptyCalibTable.dat", int start_idx=0)
{
  // init txt file and print
  std::ofstream myfile(filename);
  if (myfile.is_open())
  {
    for (int i=0; i<(int)cells.size(); i++)
    {
      myfile << i << " "
      << cells.at(i).at(0) << " "
      << cells.at(i).at(1) << " "
      << cells.at(i).at(2) << " "
      << 1.0 << " "
      << 0.1 << " "
      << 0 << " "
      << 0 << " "
      << std::endl;
    }
    myfile.close();
  }
}

// this one is store the selection in E1, Eta1, .. E2, Eta2, .. HitE1, ... vectors.
// select events with at least one hit falling in one particular cell
int SelectEventsInOneCell(int ix, int iy, int iz)
{
  // clear previous vectors
  nEvents = 0;
  nSignals = 0;
  E1.clear();
  EReg1.clear();
  Eta1.clear();
  Phi1.clear();
  E2.clear();
  EReg2.clear();
  Eta2.clear();
  Phi2.clear();
  nHits1.clear();
  nHits2.clear();
  HitE1.clear();
  HitE2.clear();
  HitIX1.clear();
  HitIY1.clear();
  HitIZ1.clear();
  HitIX2.clear();
  HitIY2.clear();
  HitIZ2.clear();
  
  // loop over all events and select events
  for (int i=0; i<nEventsAll; i++)
  {
    bool take=false;
    // loop over all hits of electron1
    for (int ii=0; ii<(int)allHitE1.at(i).size(); ii++ )
    {
      if(take==true) break;
      
      if((allHitIX1.at(i).at(ii)==ix) &&
         (allHitIY1.at(i).at(ii)==iy) &&
         (allHitIZ1.at(i).at(ii)==iz) )
      {
        // if there is even one hit match a cell in selection, take the event
        take = true;
        break;
      }
    }
    
    // loop over all hits of electron2
    for (int ii=0; ii<(int)allHitE2.at(i).size(); ii++ )
    {
      if(take==true) break;
      
      if((allHitIX2.at(i).at(ii)==ix) &&
         (allHitIY2.at(i).at(ii)==iy) &&
         (allHitIZ2.at(i).at(ii)==iz) )
      {
        // if there is even one hit match a cell in selection, take the event
        take = true;
        break;
      }
    }
    // if do not decide to take this event, continue
    if (!take)
    {
      continue;
    }
    
    // if not continue above, it is a useful event to use
    E1.push_back(&(allE1.at(i)));
    EReg1.push_back(&(allEReg1.at(i)));
    Eta1.push_back(&(allEta1.at(i)));
    Phi1.push_back(&(allPhi1.at(i)));
    E2.push_back(&(allE2.at(i)));
    EReg2.push_back(&(allEReg2.at(i)));
    Eta2.push_back(&(allEta2.at(i)));
    Phi2.push_back(&(allPhi2.at(i)));
    nHits1.push_back(&(allnHits1.at(i)));
    HitE1.push_back(&(allHitE1.at(i)));
    HitIX1.push_back(&(allHitIX1.at(i)));
    HitIY1.push_back(&(allHitIY1.at(i)));
    HitIZ1.push_back(&(allHitIZ1.at(i)));
    nHits2.push_back(&(allnHits2.at(i)));
    HitE2.push_back(&(allHitE2.at(i)));
    HitIX2.push_back(&(allHitIX2.at(i)));
    HitIY2.push_back(&(allHitIY2.at(i)));
    HitIZ2.push_back(&(allHitIZ2.at(i)));
  }
  
  // nEvents
  nEvents = (int)E1.size();
  nSignals = nEvents; // assume no background (fix me)
  //
  return nEvents;
}



// this one is store the selection in E1, Eta1, .. E2, Eta2, .. HitE1, ... vectors.
// select events with one hit falling in one particular cell
// and the energy of this hit should be greater than a fraction
int SelectEventsInOneCellWithFraction(int ix, int iy, int iz, double fraction=0.5, int doEvenOdd=0)
{
  // clear previous vectors
  nEvents = 0;
  nSignals = 0;
  E1.clear();
  EReg1.clear();
  Eta1.clear();
  Phi1.clear();
  E2.clear();
  EReg2.clear();
  Eta2.clear();
  Phi2.clear();
  nHits1.clear();
  nHits2.clear();
  HitE1.clear();
  HitE2.clear();
  HitIX1.clear();
  HitIY1.clear();
  HitIZ1.clear();
  HitIX2.clear();
  HitIY2.clear();
  HitIZ2.clear();
  
  // loop over all events and select events
  for (int i=0; i<nEventsAll; i++)
  {
    bool take=false;
    
    // even odd event check
    if (doEvenOdd==1 && i%2==0) continue;
    else if (doEvenOdd==2 && i%2==1) continue; 
    
    // loop over all hits of electron1
    for (int ii=0; ii<(int)allHitE1.at(i).size(); ii++ )
    {
      if(take==true) break;
      
      // if there is even one hit match a cell in selection,
      // also this hit energy is bigger than fraction*E(total),
      // take this event
      if((allHitIX1.at(i).at(ii)==ix) &&
         (allHitIY1.at(i).at(ii)==iy) &&
         (allHitIZ1.at(i).at(ii)==iz) &&
         (allHitE1.at(i).at(ii)>fraction*allE1.at(i)) )
      {

        take = true;
        break;
      }
    }
    
    // loop over all hits of electron2
    for (int ii=0; ii<(int)allHitE2.at(i).size(); ii++ )
    {
      if(take==true) break;
      // if there is even one hit match a cell in selection,
      // also this hit energy is bigger than fraction*E(total),
      // take this event
      if((allHitIX2.at(i).at(ii)==ix) &&
         (allHitIY2.at(i).at(ii)==iy) &&
         (allHitIZ2.at(i).at(ii)==iz) &&
         (allHitE2.at(i).at(ii)>fraction*allE2.at(i)) )
      {
        take = true;
        break;
      }
    }
    // if do not decide to take this event, continue
    if (!take)
    {
      continue;
    }
    
    // if not continue above, it is a useful event to use
    E1.push_back(&(allE1.at(i)));
    EReg1.push_back(&(allEReg1.at(i)));
    Eta1.push_back(&(allEta1.at(i)));
    Phi1.push_back(&(allPhi1.at(i)));
    E2.push_back(&(allE2.at(i)));
    EReg2.push_back(&(allEReg2.at(i)));
    Eta2.push_back(&(allEta2.at(i)));
    Phi2.push_back(&(allPhi2.at(i)));
    nHits1.push_back(&(allnHits1.at(i)));
    HitE1.push_back(&(allHitE1.at(i)));
    HitIX1.push_back(&(allHitIX1.at(i)));
    HitIY1.push_back(&(allHitIY1.at(i)));
    HitIZ1.push_back(&(allHitIZ1.at(i)));
    nHits2.push_back(&(allnHits2.at(i)));
    HitE2.push_back(&(allHitE2.at(i)));
    HitIX2.push_back(&(allHitIX2.at(i)));
    HitIY2.push_back(&(allHitIY2.at(i)));
    HitIZ2.push_back(&(allHitIZ2.at(i)));
  }
  
  // nEvents
  nEvents = (int)E1.size();
  nSignals = nEvents; // assume no background (fix me)
  //
  return nEvents;
}

// this one is store the selection in E1, Eta1, .. E2, Eta2, .. HitE1, ... vectors.
// select events with one hit falling in one particular cell
// and the energy of this hit should be greater than a fraction
// with selection of EBEB, EBEE, or EEEE combination
int SelectEventsInOneCellWithFractionEBorEECombine(int ix, int iy, int iz, double fraction=0.5, int doEvenOdd=0, std::string Combine="")
{
  // clear previous vectors
  nEvents = 0;
  nSignals = 0;
  E1.clear();
  EReg1.clear();
  Eta1.clear();
  Phi1.clear();
  E2.clear();
  EReg2.clear();
  Eta2.clear();
  Phi2.clear();
  nHits1.clear();
  nHits2.clear();
  HitE1.clear();
  HitE2.clear();
  HitIX1.clear();
  HitIY1.clear();
  HitIZ1.clear();
  HitIX2.clear();
  HitIY2.clear();
  HitIZ2.clear();

  // loop over all events and select events
  for (int i=0; i<nEventsAll; i++)
  {
    bool take=false;

    // even odd event check
    if (doEvenOdd==1 && i%2==0) continue;
    else if (doEvenOdd==2 && i%2==1) continue;

    // EB or EE combinatioin check
    if ( Combine=="EBEB" ) // both in EB
    {
      if ( !(fabs(allEta1[i])<1.48&&fabs(allEta2[i])<1.48) ) continue;
    }
    if ( Combine=="EBEE" ) // one in EB one in EE
    {
      if ( !( (fabs(allEta1[i])<1.48&&fabs(allEta2[i])>1.48)||(fabs(allEta2[i])<1.48&&fabs(allEta1[i])>1.48) ) ) continue;
    }
    if ( Combine=="EEEE" ) // both in EE
    {
      if ( !(fabs(allEta1[i])>1.48&&fabs(allEta2[i])>1.48) ) continue;
    }
    if ( Combine=="EE" ) // any one of the two in EE 
    {
      if ( !(fabs(allEta1[i])>1.48||fabs(allEta2[i])>1.48) ) continue;
    }
    if ( Combine=="EB" ) // any one of the two in EB
    {
      if ( !(fabs(allEta1[i])<1.48||fabs(allEta2[i])<1.48) ) continue;
    }

    // loop over all hits of electron1
    for (int ii=0; ii<(int)allHitE1.at(i).size(); ii++ )
    {
      if(take==true) break;

      // if there is even one hit match a cell in selection,
      // also this hit energy is bigger than fraction*E(total),
      // take this event
      if((allHitIX1.at(i).at(ii)==ix) &&
         (allHitIY1.at(i).at(ii)==iy) &&
         (allHitIZ1.at(i).at(ii)==iz) &&
         (allHitE1.at(i).at(ii)>fraction*allE1.at(i)) )
      {

        take = true;
        break;
      }
    }

    // loop over all hits of electron2
    for (int ii=0; ii<(int)allHitE2.at(i).size(); ii++ )
    {
      if(take==true) break;
      // if there is even one hit match a cell in selection,
      // also this hit energy is bigger than fraction*E(total),
      // take this event
      if((allHitIX2.at(i).at(ii)==ix) &&
         (allHitIY2.at(i).at(ii)==iy) &&
         (allHitIZ2.at(i).at(ii)==iz) &&
         (allHitE2.at(i).at(ii)>fraction*allE2.at(i)) )
      {
        take = true;
        break;
      }
    }

    // if do not decide to take this event, continue
    if (!take)
    {
      continue;
    }

    // if not continue above, it is a useful event to use
    E1.push_back(&(allE1.at(i)));
    EReg1.push_back(&(allEReg1.at(i)));
    Eta1.push_back(&(allEta1.at(i)));
    Phi1.push_back(&(allPhi1.at(i)));
    E2.push_back(&(allE2.at(i)));
    EReg2.push_back(&(allEReg2.at(i)));
    Eta2.push_back(&(allEta2.at(i)));
    Phi2.push_back(&(allPhi2.at(i)));
    nHits1.push_back(&(allnHits1.at(i)));
    HitE1.push_back(&(allHitE1.at(i)));
    HitIX1.push_back(&(allHitIX1.at(i)));
    HitIY1.push_back(&(allHitIY1.at(i)));
    HitIZ1.push_back(&(allHitIZ1.at(i)));
    nHits2.push_back(&(allnHits2.at(i)));
    HitE2.push_back(&(allHitE2.at(i)));
    HitIX2.push_back(&(allHitIX2.at(i)));
    HitIY2.push_back(&(allHitIY2.at(i)));
    HitIZ2.push_back(&(allHitIZ2.at(i)));
  }

  // nEvents
  nEvents = (int)E1.size();
  nSignals = nEvents; // assume no background (fix me)
  //
  return nEvents;

}

int SelectEventsInOneSeed(int ix, int iy, int iz, int doEvenOdd=0, std::string Combine="")
{
  // clear previous vectors
  nEvents = 0;
  nSignals = 0;
  E1.clear();
  EReg1.clear();
  Eta1.clear();
  Phi1.clear();
  E2.clear();
  EReg2.clear();
  Eta2.clear();
  Phi2.clear();
  nHits1.clear();
  nHits2.clear();
  HitE1.clear();
  HitE2.clear();
  HitIX1.clear();
  HitIY1.clear();
  HitIZ1.clear();
  HitIX2.clear();
  HitIY2.clear();
  HitIZ2.clear();

  UseEle1.clear();
  UseEle2.clear();
  RawEEcal1.clear();
  RawEEcal2.clear();
  SeedIX1.clear();
  SeedIX2.clear();
  SeedIY1.clear();
  SeedIY2.clear();
  SeedIZ1.clear();
  SeedIZ2.clear();

  // loop over all events and select events
  for (int i=0; i<nEventsAll; i++)
  {
 
    // even odd check
    if (doEvenOdd==1 && allEvtNum[i]%2==0) continue;
    else if (doEvenOdd==2 && allEvtNum[i]%2==1) continue;

    // EB or EE combinatioin check
    if ( Combine=="EBEB" ) // both in EB
    {
      if ( !(fabs(allEta1[i])<1.48&&fabs(allEta2[i])<1.48) ) continue;
    }
    else if ( Combine=="EBEE" ) // one in EB one in EE
    {
      if ( !( (fabs(allEta1[i])<1.48&&fabs(allEta2[i])>1.48)||(fabs(allEta2[i])<1.48&&fabs(allEta1[i])>1.48) ) ) continue;
    }
    else if ( Combine=="EEEE" ) // both in EE
    {
      if ( !(fabs(allEta1[i])>1.48&&fabs(allEta2[i])>1.48) ) continue;
    }
    else if ( Combine=="EE" ) // any one of the two in EE
    {
      if ( !(fabs(allEta1[i])>1.48||fabs(allEta2[i])>1.48) ) continue;
    }
    else if ( Combine=="EB" ) // any one of the two in EB
    {
      if ( !(fabs(allEta1[i])<1.48||fabs(allEta2[i])<1.48) ) continue;
    }

    // check if e1 or e2 is in the cell to be fitted
    bool takeEle1(false), takeEle2(false);
    // e1
    if (allSeedIX1.at(i)==ix &&
        allSeedIY1.at(i)==iy &&
        allSeedIZ1.at(i)==iz )
    {
       takeEle1=true;
    }
    // e2
    if (allSeedIX2.at(i)==ix &&
        allSeedIY2.at(i)==iy &&
        allSeedIZ2.at(i)==iz )
    {
       takeEle2=true;
    }
    // if do not decide to take this event, continue
    if (!takeEle1&&!takeEle2)
    {
      continue;
     std::cout << " continue " << std::endl;
    }

    // if not continue above, it is a useful event to use
    E1.push_back(&(allE1.at(i)));
    EReg1.push_back(&(allEReg1.at(i)));
    Eta1.push_back(&(allEta1.at(i)));
    Phi1.push_back(&(allPhi1.at(i)));
    E2.push_back(&(allE2.at(i)));
    EReg2.push_back(&(allEReg2.at(i)));
    Eta2.push_back(&(allEta2.at(i)));
    Phi2.push_back(&(allPhi2.at(i)));

    RawEEcal1.push_back(&(allRawEEcal1.at(i)));  
    RawEEcal2.push_back(&(allRawEEcal2.at(i)));  

    UseEle1.push_back(takeEle1);
    UseEle2.push_back(takeEle2);

  }

  // nEvents
  nEvents = (int)E1.size();
  nSignals = nEvents; // assume no background (fix me)
  //
  return nEvents;

}

//
// Store the selection in E1, Eta1, .. E2, Eta2, .. HitE1, ... vectors.
// select events according to the following rule:
// - center at ix,iy,iz among a group of 3x3 = 9 cells
// - if one event has one electron falls inside these 9cells and deposits >90% 
//   of its energy inside these 9 cells, take the event.
// - no need to have all the 9 cells be fired by the same electron in the same 
//   event, but >90% electron energy is required.
// - no need to be exactly 9 cells if the center cell is at (or near) an edge.
// - store those cells among these 9 cells that follow some requirements.
// - if not an electron/event among all the events deposits >10% of the electron 
//   energy into this center cell ix, iy, iz, skip this cell and also all the 
//   other 8 cells around it.
// - if not an electron/event among all the events deposits >2% of its energy 
//   inside the 8 cells around the center cell, skip this surrounding cell.
// 
// Has selection of EBEB, EBEE, or EEEE combination
int SelectEventsInOneCellWith3x3Others(int ix, int iy, int iz, 
                   std::vector<int>& ixx, std::vector<int>& iyy, std::vector<int>& izz, 
                   std::string Combine="")
{
  // clear previous vectors
  nEvents = 0;
  nSignals = 0;
  E1.clear();
  EReg1.clear();
  Eta1.clear();
  Phi1.clear();
  E2.clear();
  EReg2.clear();
  Eta2.clear();
  Phi2.clear();
  nHits1.clear();
  nHits2.clear();
  HitE1.clear();
  HitE2.clear();
  HitIX1.clear();
  HitIY1.clear();
  HitIZ1.clear();
  HitIX2.clear();
  HitIY2.clear();
  HitIZ2.clear();

  // define default 3x3 celles taking ix,iy,iz as center
  // positions
  std::vector<int> iixx, iiyy, iizz;
  // largest energy fraction in all events
  std::vector<double> iimaxefrac;
  // push_back the fitted cell as the first item in the vector
  iixx.push_back(ix);
  iiyy.push_back(iy);
  iizz.push_back(iz);
  iimaxefrac.push_back(0.0);
  // push_back the rest 8 cells
  for (int jx=ix-1; jx<=ix+1; jx++)
  {
    for (int jy=iy-1; jy<=iy+1; jy++)
    {
      // skip the fitting cell that has already been booked.
      if (jx==ix&&jy==iy) continue;
      iiyy.push_back(jy);
      iizz.push_back(iz);
      iimaxefrac.push_back(0.0);
      if (iz==0&&jx==0&&ix==1) 
      {
        iixx.push_back(jx-1);
      }
      else if (iz==0&&jx==0&&ix==-1)
      {
        iixx.push_back(jx+1);
      }
      else
      {
        iixx.push_back(jx);
      } 
    }
  }

  // some debug
  std::cout << " Debug:: print 3x3 cells " << std::endl;
  for (int icell=0; icell<(int)iixx.size(); icell++)
  {
    std::cout << "(" << iixx.at(icell) << "," << iiyy.at(icell) << "," << iizz.at(icell) << ")" << std::endl;
  }

  // loop over all events and select events
  for (int i=0; i<nEventsAll; i++)
  {

    // EB or EE combinatioin check
    if ( Combine=="EBEB" ) // both in EB
    {
      if ( !(fabs(allEta1[i])<1.48&&fabs(allEta2[i])<1.48) ) continue;
    }
    if ( Combine=="EBEE" ) // one in EB one in EE
    {
      if ( !( (fabs(allEta1[i])<1.48&&fabs(allEta2[i])>1.48)||(fabs(allEta2[i])<1.48&&fabs(allEta1[i])>1.48) ) ) continue;
    }
    if ( Combine=="EEEE" ) // both in EE
    {
      if ( !(fabs(allEta1[i])>1.48&&fabs(allEta2[i])>1.48) ) continue;
    }
    if ( Combine=="EE" ) // any one of the two in EE
    {
      if ( !(fabs(allEta1[i])>1.48||fabs(allEta2[i])>1.48) ) continue;
    }
    if ( Combine=="EB" ) // any one of the two in EB
    {
      if ( !(fabs(allEta1[i])<1.48||fabs(allEta2[i])<1.48) ) continue;
    }
    // note, if not any of the string above, this event will always pass this check.

    // 
    double E1_9cells(0);
    // loop over all hits of electron1
    for (int ii=0; ii<(int)allHitE1.at(i).size(); ii++ )
    {
      double hitfrac = allHitE1.at(i).at(ii)/allE1.at(i);
      // loop over all 9 cells
      for (int icell=0; icell<(int)iixx.size(); icell++)
      {
        // check matching
        if( (allHitIX1.at(i).at(ii)==iixx.at(icell)) &&
            (allHitIY1.at(i).at(ii)==iiyy.at(icell)) &&
            (allHitIZ1.at(i).at(ii)==iizz.at(icell)) )
        {
          E1_9cells += allHitE1.at(i).at(ii);
          if (hitfrac>iimaxefrac.at(icell))
          {
            iimaxefrac.at(icell) = hitfrac;
          }
        } // if ( (allHitIX1.at(i)...
      } // for (int icell=0; ..
    } // for (int ii=0; ..
   
    //
    double E2_9cells(0);
    // loop over all hits of electron2
    for (int ii=0; ii<(int)allHitE2.at(i).size(); ii++ )
    {
      double hitfrac = allHitE2.at(i).at(ii)/allE2.at(i);
      // loop over all 9 cells
      for (int icell=0; icell<(int)iixx.size(); icell++)
      {
        // check matching
        if( (allHitIX2.at(i).at(ii)==iixx.at(icell)) &&
            (allHitIY2.at(i).at(ii)==iiyy.at(icell)) &&
            (allHitIZ2.at(i).at(ii)==iizz.at(icell)) )
        {
          E2_9cells += allHitE2.at(i).at(ii);
          if (hitfrac>iimaxefrac.at(icell))
          {
            iimaxefrac.at(icell) = hitfrac;
          }
        } // if ( (allHitIX2.at(i)...
      } // for (int icell=0; ..
    } // for (int ii=0; ..

    // if the 9cells energy in both the two electrons are 
    //  less than 90% of the electrons' energy, I skip this 
    //  event.
    if ( E1_9cells/allE1.at(i)<0.6 && 
         E2_9cells/allE2.at(i)<0.6 )
    {
      continue;
    }

    // if not continue above, it is a useful event to use
    E1.push_back(&(allE1.at(i)));
    EReg1.push_back(&(allEReg1.at(i)));
    Eta1.push_back(&(allEta1.at(i)));
    Phi1.push_back(&(allPhi1.at(i)));
    E2.push_back(&(allE2.at(i)));
    EReg2.push_back(&(allEReg2.at(i)));
    Eta2.push_back(&(allEta2.at(i)));
    Phi2.push_back(&(allPhi2.at(i)));
    nHits1.push_back(&(allnHits1.at(i)));
    HitE1.push_back(&(allHitE1.at(i)));
    HitIX1.push_back(&(allHitIX1.at(i)));
    HitIY1.push_back(&(allHitIY1.at(i)));
    HitIZ1.push_back(&(allHitIZ1.at(i)));
    nHits2.push_back(&(allnHits2.at(i)));
    HitE2.push_back(&(allHitE2.at(i)));
    HitIX2.push_back(&(allHitIX2.at(i)));
    HitIY2.push_back(&(allHitIY2.at(i)));
    HitIZ2.push_back(&(allHitIZ2.at(i)));
  }

  // nEvents
  nEvents = (int)E1.size();
  nSignals = nEvents; // assume no background (fix me)

  // making selection of the 3x3 cells according to the following rules:
  // - if not an electron/event among all the events deposits >10% of the electron
  //   energy into this center cell ix, iy, iz, skip this cell and also all the
  //   other 8 cells around it.
  // - if not an electron/event among all the events deposits >2% of its energy
  //   inside the 8 cells around the center cell, skip this surrounding cell.

  // clean up the output cell position vectors
  ixx.clear();
  iyy.clear();
  izz.clear();

  // check fitting cell at first
  if ( iimaxefrac.at(0)<0.1 ) 
  {
    return 0; // take this as a flag to skip this cell
  }
  else
  {
    // same, the first entry is the fitting cell.
    ixx.push_back(iixx.at(0));
    iyy.push_back(iiyy.at(0));
    izz.push_back(iizz.at(0));
  }

  // check the rest 8 cells;
  for (int icell=1; icell<(int)iixx.size(); icell++)
  {
    // if the maximum cell energy fraction among all events are <2%, do not use this cell
    if (iimaxefrac.at(icell)<0.02) continue;
    // if not use this cell
    ixx.push_back(iixx.at(icell));
    iyy.push_back(iiyy.at(icell));
    izz.push_back(iizz.at(icell));
  }

  //
  return nEvents;

}
//

int SelectEventsInOneScaleBin(int scale_bin, std::string Combine="")
{
  // clear previous vectors
  nEvents = 0;
  nSignals = 0;
  E1.clear();
  EReg1.clear();
  ERegScale1.clear();
  RawSCE1.clear();
  Eta1.clear();
  ScaleBin1.clear();
  UseEle1.clear();
  Phi1.clear();
  E2.clear();
  EReg2.clear();
  ERegScale2.clear();
  RawSCE2.clear();
  Eta2.clear();
  Phi2.clear();
  ScaleBin2.clear();
  UseEle2.clear();

  // protection against not existing vectors
  bool store_it = false;
  if(allE1.size()==allRawSCE1.size())
  {
    store_it = true;
  }

  // loop over all events and select events
  for (int i=0; i<nEventsAll; i++)
  {
    // EB or EE combinatioin check
    if ( Combine=="EBEB" ) // both in EB
    {
      if ( !(fabs(allSCEta1[i])<1.49&&fabs(allSCEta2[i])<1.49) ) continue;
    }
    if ( Combine=="EBEE" ) // one in EB one in EE
    {
      if ( !( (fabs(allSCEta1[i])<1.49&&fabs(allSCEta2[i])>1.49)||(fabs(allSCEta2[i])<1.49&&fabs(allSCEta1[i])>1.49) ) ) continue;
    }
    if ( Combine=="EEEE" ) // both in EE
    {
      if ( !(fabs(allSCEta1[i])>1.49&&fabs(allSCEta2[i])>1.49) ) continue;
    }
    if ( Combine=="EE" ) // any one of the two in EE
    {
      if ( !(fabs(allSCEta1[i])>1.49||fabs(allSCEta2[i])>1.49) ) continue;
    }
    if ( Combine=="EB" ) // any one of the two in EB
    {
      if ( !(fabs(allSCEta1[i])<1.49||fabs(allSCEta2[i])<1.49) ) continue;
    }
    // note, if not any of the string above, this event will always pass this check.

    // check which electron in this eta-ring
    bool takeEle1(false), takeEle2(false);
    if (allScaleBin1.at(i)==scale_bin) takeEle1 = true;
    else takeEle1 = false;
    if (allScaleBin2.at(i)==scale_bin) takeEle2 = true;
    else takeEle2 = false;

    // continue if do not take any one
    if ( (!takeEle1) && (!takeEle2) ) continue;

    // if not continue above, it is a useful event to use
    E1.push_back(&(allE1.at(i)));
    EReg1.push_back(&(allEReg1.at(i)));
    ERegScale1.push_back(&(allERegScale1.at(i)));
    if (store_it) RawSCE1.push_back(&(allRawSCE1.at(i)));
    Eta1.push_back(&(allEta1.at(i)));
    Phi1.push_back(&(allPhi1.at(i)));
    ScaleBin1.push_back(allScaleBin1.at(i));
    UseEle1.push_back(takeEle1);
    E2.push_back(&(allE2.at(i)));
    EReg2.push_back(&(allEReg2.at(i)));
    ERegScale2.push_back(&(allERegScale2.at(i)));
    if (store_it) RawSCE2.push_back(&(allRawSCE2.at(i)));
    Eta2.push_back(&(allEta2.at(i)));
    Phi2.push_back(&(allPhi2.at(i)));
    ScaleBin2.push_back(allScaleBin2.at(i));
    UseEle2.push_back(takeEle2);

  }

  // nEvents
  nEvents = (int)E1.size();
  nSignals = nEvents; // assume no background (fix me)

  return nEvents;


}

///
int SelectEventsForEtaScaleFits(std::string Combine="", int max_events = -1)
{
  // clear previous vectors
  nEvents = 0;
  nSignals = 0;
  E1.clear();
  EReg1.clear();
  ERegScale1.clear();
  RawSCE1.clear();
  Eta1.clear();
  ScaleBin1.clear();
  UseEle1.clear();
  Phi1.clear();
  E2.clear();
  EReg2.clear();
  ERegScale2.clear();
  RawSCE2.clear();
  Eta2.clear();
  Phi2.clear();
  ScaleBin2.clear();
  UseEle2.clear();

  // protection against not existing vectors
  bool store_it = false;
  if(allE1.size()==allRawSCE1.size())
  {
    store_it = true;
  }

  std::cout << "SelectEventsForEtaScaleFits:: store the allRawSCE ? " << store_it << std::endl;

  // loop over all events and select events
  for (int i=0; i<nEventsAll; i++)
  {
    // EB or EE combinatioin check
    if ( Combine=="EBEB" ) // both in EB
    {
      if ( !(fabs(allSCEta1[i])<1.49&&fabs(allSCEta2[i])<1.49) ) continue;
    }
    if ( Combine=="EBEE" ) // one in EB one in EE
    {
      if ( !( (fabs(allSCEta1[i])<1.49&&fabs(allSCEta2[i])>1.49)||(fabs(allSCEta2[i])<1.49&&fabs(allSCEta1[i])>1.49) ) ) continue;
    }
    if ( Combine=="EEEE" ) // both in EE
    {
      if ( !(fabs(allSCEta1[i])>1.49&&fabs(allSCEta2[i])>1.49) ) continue;
    }
    if ( Combine=="EE" ) // any one of the two in EE
    {
      if ( !(fabs(allSCEta1[i])>1.49||fabs(allSCEta2[i])>1.49) ) continue;
    }
    if ( Combine=="EB" ) // any one of the two in EB
    {
      if ( !(fabs(allSCEta1[i])<1.49||fabs(allSCEta2[i])<1.49) ) continue;
    }
    // note, if not any of the string above, this event will always pass this check.

    E1.push_back(&(allE1.at(i)));
    EReg1.push_back(&(allEReg1.at(i)));
    ERegScale1.push_back(&(allERegScale1.at(i)));
    if (store_it) RawSCE1.push_back(&(allRawSCE1.at(i)));
    Eta1.push_back(&(allEta1.at(i)));
    Phi1.push_back(&(allPhi1.at(i)));
    ScaleBin1.push_back(allScaleBin1.at(i));
    UseEle1.push_back(true);
    E2.push_back(&(allE2.at(i)));
    EReg2.push_back(&(allEReg2.at(i)));
    ERegScale2.push_back(&(allERegScale2.at(i)));
    if (store_it) RawSCE2.push_back(&(allRawSCE2.at(i)));
    Eta2.push_back(&(allEta2.at(i)));
    Phi2.push_back(&(allPhi2.at(i)));
    ScaleBin2.push_back(allScaleBin2.at(i));
    UseEle2.push_back(true);
 
    // stop storing events if reached the max events
    if ( max_events!=-1 && i>max_events) break;

  }

  // nEvents
  nEvents = (int)E1.size();
  nSignals = nEvents; // assume no background (fix me)

  return nEvents;
}



// select events in one Eta bin
int SelectEventsInOneEtaBin(double bin_min, double bin_max, std::string Combine="")
{
  // clear previous vectors
  nEvents = 0;
  nSignals = 0;
  E1.clear();
  EReg1.clear();
  Eta1.clear();
  UseEle1.clear();
  Phi1.clear();
  E2.clear();
  EReg2.clear();
  Eta2.clear();
  Phi2.clear();
  UseEle2.clear();

  // loop over all events and select events
  for (int i=0; i<nEventsAll; i++)
  {

    // EB or EE combinatioin check
    if ( Combine=="EBEB" ) // both in EB
    {
      if ( !(fabs(allEta1[i])<1.48&&fabs(allEta2[i])<1.48) ) continue;
    }
    if ( Combine=="EBEE" ) // one in EB one in EE
    {
      if ( !( (fabs(allEta1[i])<1.48&&fabs(allEta2[i])>1.48)||(fabs(allEta2[i])<1.48&&fabs(allEta1[i])>1.48) ) ) continue;
    }
    if ( Combine=="EEEE" ) // both in EE
    {
      if ( !(fabs(allEta1[i])>1.48&&fabs(allEta2[i])>1.48) ) continue;
    }
    if ( Combine=="EE" ) // any one of the two in EE
    {
      if ( !(fabs(allEta1[i])>1.48||fabs(allEta2[i])>1.48) ) continue;
    }
    if ( Combine=="EB" ) // any one of the two in EB
    {
      if ( !(fabs(allEta1[i])<1.48||fabs(allEta2[i])<1.48) ) continue;
    }
    // note, if not any of the string above, this event will always pass this check.

    // check which electron in this eta-ring
    bool takeEle1(false), takeEle2(false);
    if (allEta1.at(i)>bin_min&&allEta1.at(i)<bin_max) takeEle1 = true;
    else takeEle1 = false;
    if (allEta2.at(i)>bin_min&&allEta2.at(i)<bin_max) takeEle2 = true;
    else takeEle2 = false;
 
    // continue if do not take any one
    if ( (!takeEle1) && (!takeEle2) ) continue;

    // if not continue above, it is a useful event to use
    E1.push_back(&(allE1.at(i)));
    EReg1.push_back(&(allEReg1.at(i)));
    Eta1.push_back(&(allEta1.at(i)));
    Phi1.push_back(&(allPhi1.at(i)));
    UseEle1.push_back(takeEle1);
    E2.push_back(&(allE2.at(i)));
    EReg2.push_back(&(allEReg2.at(i)));
    Eta2.push_back(&(allEta2.at(i)));
    Phi2.push_back(&(allPhi2.at(i)));
    UseEle2.push_back(takeEle2);
  }

  // nEvents
  nEvents = (int)E1.size();
  nSignals = nEvents; // assume no background (fix me)
  
  return nEvents;

}

//////////
int AddEtaBinNumberToAllEvents(const std::vector<EtaRingEnergyScale>& EtaScale)
{
  // clear energy scale binning number vectors
  allScaleBin1.clear();
  allScaleBin2.clear();

  // loop over all events and select events
  for (int i=0; i<nEventsAll; i++)
  {
    // findout which bins it belongs to
    int bin1(-1), bin2(-1);
    for (int ibin=0; ibin<(int)EtaScale.size(); ibin++)
    {
      if (GetEtaRing(allSeedIX1.at(i), allSeedIY1.at(i), allSeedIZ1.at(i))==EtaScale.at(ibin).EtaRing) bin1 = ibin;
      if (GetEtaRing(allSeedIX2.at(i), allSeedIY2.at(i), allSeedIZ2.at(i))==EtaScale.at(ibin).EtaRing) bin2 = ibin;
    }

    // give bin number, -1 means no e-scale is going to be applied.
    allScaleBin1.push_back(bin1);
    allScaleBin2.push_back(bin2);

    // check the allScaleBin1 entries are one-to-one matched with other allXX vectors.
    if ( (int)allScaleBin1.size()!=(i+1) || (int)allScaleBin2.size()!=(i+1) ) 
    {
       std::cout << "ERROR:: AddEtaBinNumberToAllEvents:: fail to add one-to-one matched ScaleBin numbers. " << std::endl;
       abort();
    }
  }

  // nEvents
  return nEventsAll;

}



/////////////////
int AddEtaBinNumberToElectrons(const std::vector<EtaRingEnergyScale>& EtaScale, const std::string Combine="", const int nevents_max=-1 )
{
  // clear previous vectors
  nEvents = 0;
  nSignals = 0;
  E1.clear();
  EReg1.clear();
  Eta1.clear();
  Phi1.clear();
  E2.clear();
  EReg2.clear();
  Eta2.clear();
  Phi2.clear();
  // clear energy scale binning number vectors
  ScaleBin1.clear();
  ScaleBin2.clear();


  // loop over all events and select events
  for (int i=0; i<nEventsAll; i++)
  {

    // EB or EE combinatioin check
    if ( Combine=="EBEB" ) // both in EB
    {
      if ( !(fabs(allSCEta1[i])<1.49&&fabs(allSCEta2[i])<1.49) ) continue;
    }
    if ( Combine=="EBEE" ) // one in EB one in EE
    {
      if ( !( (fabs(allSCEta1[i])<1.49&&fabs(allSCEta2[i])>1.49)||(fabs(allSCEta2[i])<1.49&&fabs(allSCEta1[i])>1.49) ) ) continue;
    }
    if ( Combine=="EEEE" ) // both in EE
    {
      if ( !(fabs(allSCEta1[i])>1.49&&fabs(allSCEta2[i])>1.49) ) continue;
    }
    if ( Combine=="EE" ) // any one of the two in EE
    {
      if ( !(fabs(allSCEta1[i])>1.49||fabs(allSCEta2[i])>1.49) ) continue;
    }
    if ( Combine=="EB" ) // any one of the two in EB
    {
      if ( !(fabs(allSCEta1[i])<1.49||fabs(allSCEta2[i])<1.49) ) continue;
    }
    // note, if not any of the string above, this event will always pass this check.

    // findout which bins it belongs to
    int bin1(-1), bin2(-1);
    for (int ibin=0; ibin<(int)EtaScale.size(); ibin++)
    {
      if (GetEtaRing(allSeedIX1.at(i), allSeedIY1.at(i), allSeedIZ1.at(i))==EtaScale.at(ibin).EtaRing) bin1 = ibin; 
      if (GetEtaRing(allSeedIX2.at(i), allSeedIY2.at(i), allSeedIZ2.at(i))==EtaScale.at(ibin).EtaRing) bin2 = ibin; 
    }

    // check if both bin1 and bin2 have NOT been given a value, we simply skip this event
    if (bin1<0&&bin2<0) continue;

    // give bin number, -1 means no e-scale is going to be applied.
    ScaleBin1.push_back(bin1);
    ScaleBin2.push_back(bin2);

    // if not continue above, it is a useful event to use
    E1.push_back(&(allE1.at(i)));
    EReg1.push_back(&(allEReg1.at(i)));
    Eta1.push_back(&(allEta1.at(i)));
    Phi1.push_back(&(allPhi1.at(i)));
    E2.push_back(&(allE2.at(i)));
    EReg2.push_back(&(allEReg2.at(i)));
    Eta2.push_back(&(allEta2.at(i)));
    Phi2.push_back(&(allPhi2.at(i)));

    // break if reached the maximum needed events
    if ( (nevents_max!=-1)&&((int)E1.size()>=nevents_max) ) break; 

  }

  // nEvents
  nEvents = (int)E1.size();
  nSignals = nEvents; // assume no background (fix me)

  return nEvents;

}
////////////////////

int AddEtaBinNumberToElectrons(const std::vector<double>& EtaBins, const std::string Combine="")
{
  // clear previous vectors
  nEvents = 0;
  nSignals = 0;
  E1.clear();
  EReg1.clear();
  Eta1.clear();
  Phi1.clear();
  E2.clear();
  EReg2.clear();
  Eta2.clear();
  Phi2.clear();
  // clear energy scale binning number vectors
  ScaleBin1.clear();
  ScaleBin2.clear();


  // loop over all events and select events
  for (int i=0; i<nEventsAll; i++)
  {

    // EB or EE combinatioin check
    if ( Combine=="EBEB" ) // both in EB
    {
      if ( !(fabs(allEta1[i])<1.48&&fabs(allEta2[i])<1.48) ) continue;
    }
    if ( Combine=="EBEE" ) // one in EB one in EE
    {
      if ( !( (fabs(allEta1[i])<1.48&&fabs(allEta2[i])>1.48)||(fabs(allEta2[i])<1.48&&fabs(allEta1[i])>1.48) ) ) continue;
    }
    if ( Combine=="EEEE" ) // both in EE
    {
      if ( !(fabs(allEta1[i])>1.48&&fabs(allEta2[i])>1.48) ) continue;
    }
    if ( Combine=="EE" ) // any one of the two in EE
    {
      if ( !(fabs(allEta1[i])>1.48||fabs(allEta2[i])>1.48) ) continue;
    }
    if ( Combine=="EB" ) // any one of the two in EB
    {
      if ( !(fabs(allEta1[i])<1.48||fabs(allEta2[i])<1.48) ) continue;
    }
    // note, if not any of the string above, this event will always pass this check.

    // findout which bins it belongs to
    int bin1(-1), bin2(-1); 
    for (int ibin=0; ibin<(int)EtaBins.size()-1; ibin++)
    {
      double bin_min = EtaBins.at(ibin);
      double bin_max = EtaBins.at(ibin+1);
 
      if (allEta1.at(i)>bin_min&&allEta1.at(i)<bin_max) bin1 = ibin;
      if (allEta2.at(i)>bin_min&&allEta2.at(i)<bin_max) bin2 = ibin;
    }

    // check if both bin1 and bin2 have NOT been given a value, we simply skip this event
    if (bin1<0&&bin2<0) continue;

    // give bin number, -1 means no e-scale is going to be applied.
    ScaleBin1.push_back(bin1);
    ScaleBin2.push_back(bin2);

    // if not continue above, it is a useful event to use
    E1.push_back(&(allE1.at(i)));
    EReg1.push_back(&(allEReg1.at(i)));
    Eta1.push_back(&(allEta1.at(i)));
    Phi1.push_back(&(allPhi1.at(i)));
    E2.push_back(&(allE2.at(i)));
    EReg2.push_back(&(allEReg2.at(i)));
    Eta2.push_back(&(allEta2.at(i)));
    Phi2.push_back(&(allPhi2.at(i)));
  }

  // nEvents
  nEvents = (int)E1.size();
  nSignals = nEvents; // assume no background (fix me)

  return nEvents;

}

int AddEtaBinNumberToElectrons(const std::vector<EnergyScale>& EtaScale, const std::string Combine="")
{
  // clear previous vectors
  nEvents = 0;
  nSignals = 0;
  E1.clear();
  EReg1.clear();
  Eta1.clear();
  Phi1.clear();
  E2.clear();
  EReg2.clear();
  Eta2.clear();
  Phi2.clear();
  // clear energy scale binning number vectors
  ScaleBin1.clear();
  ScaleBin2.clear();


  // loop over all events and select events
  for (int i=0; i<nEventsAll; i++)
  {

    // EB or EE combinatioin check
    if ( Combine=="EBEB" ) // both in EB
    {
      if ( !(fabs(allEta1[i])<1.48&&fabs(allEta2[i])<1.48) ) continue;
    }
    if ( Combine=="EBEE" ) // one in EB one in EE
    {
      if ( !( (fabs(allEta1[i])<1.48&&fabs(allEta2[i])>1.48)||(fabs(allEta2[i])<1.48&&fabs(allEta1[i])>1.48) ) ) continue;
    }
    if ( Combine=="EEEE" ) // both in EE
    {
      if ( !(fabs(allEta1[i])>1.48&&fabs(allEta2[i])>1.48) ) continue;
    }
    if ( Combine=="EE" ) // any one of the two in EE
    {
      if ( !(fabs(allEta1[i])>1.48||fabs(allEta2[i])>1.48) ) continue;
    }
    if ( Combine=="EB" ) // any one of the two in EB
    {
      if ( !(fabs(allEta1[i])<1.48||fabs(allEta2[i])<1.48) ) continue;
    }
    // note, if not any of the string above, this event will always pass this check.

    // findout which bins it belongs to
    int bin1(-1), bin2(-1);
    for (int ibin=0; ibin<(int)EtaScale.size(); ibin++)
    {
      if (allEta1.at(i)>EtaScale.at(ibin).min&&allEta1.at(i)<EtaScale.at(ibin).max) bin1 = ibin;
      if (allEta2.at(i)>EtaScale.at(ibin).min&&allEta2.at(i)<EtaScale.at(ibin).max) bin2 = ibin;
    }


    // check if both bin1 and bin2 have NOT been given a value, we simply skip this event
    if (bin1<0&&bin2<0) continue;

    // give bin number, -1 means no e-scale is going to be applied.
    ScaleBin1.push_back(bin1);
    ScaleBin2.push_back(bin2);

    // if not continue above, it is a useful event to use
    E1.push_back(&(allE1.at(i)));
    EReg1.push_back(&(allEReg1.at(i)));
    Eta1.push_back(&(allEta1.at(i)));
    Phi1.push_back(&(allPhi1.at(i)));
    E2.push_back(&(allE2.at(i)));
    EReg2.push_back(&(allEReg2.at(i)));
    Eta2.push_back(&(allEta2.at(i)));
    Phi2.push_back(&(allPhi2.at(i)));
  }

  // nEvents
  nEvents = (int)E1.size();
  nSignals = nEvents; // assume no background (fix me)

  return nEvents;

}


void ApplyEtaScaleToAllEvents(const std::vector<double>& EtaBins,const std::vector<double>& EtaScales)
{
  // loop over all events 
  for (int i=0; i<nEventsAll; i++)
  {
    // findout which bins it belongs to
    int bin1(-1), bin2(-1);
    for (int ibin=0; ibin<(int)EtaBins.size()-1; ibin++)
    {
      double bin_min = EtaBins.at(ibin);
      double bin_max = EtaBins.at(ibin+1);

      if (allEta1.at(i)>bin_min&&allEta1.at(i)<bin_max) bin1 = ibin;
      if (allEta2.at(i)>bin_min&&allEta2.at(i)<bin_max) bin2 = ibin;
    }

    // apply eta scale
    if (bin1>=0) allEReg1.at(i) *= EtaScales.at(bin1);
    if (bin2>=0) allEReg2.at(i) *= EtaScales.at(bin2);

  }

}

//
void ApplyEtaScaleToAllEvents(const std::vector<EnergyScale>& EtaScale)
{
  // loop over all events
  for (int i=0; i<nEventsAll; i++)
  {
    // findout which bins it belongs to
    int bin1(-1), bin2(-1);
    for (int ibin=0; ibin<(int)EtaScale.size(); ibin++)
    {
      if (allEta1.at(i)>EtaScale.at(ibin).min&&allEta1.at(i)<EtaScale.at(ibin).max) bin1 = ibin;
      if (allEta2.at(i)>EtaScale.at(ibin).min&&allEta2.at(i)<EtaScale.at(ibin).max) bin2 = ibin;
    }

    // apply eta scale
    if (bin1>=0) allEReg1.at(i) *= EtaScale.at(bin1).s;
    if (bin2>=0) allEReg2.at(i) *= EtaScale.at(bin2).s;

  }

}

//////////
void ApplyEtaScaleToAllEventsABCD(const std::vector<EnergyScale>& EtaScaleA, 
                                  const std::vector<EnergyScale>& EtaScaleB,
                                  const std::vector<EnergyScale>& EtaScaleC,
                                  const std::vector<EnergyScale>& EtaScaleD)
{
  // ABCD runNum range
  const int Amin(190645), Amax(193621);
  const int Bmin(193834), Bmax(196531);
  const int Cmin(198022), Cmax(203742);
  const int Dmin(203777), Dmax(208686);

  // counts
  int NumA(0), NumB(0), NumC(0), NumD(0), NumAll(0);

  // loop over all events
  for (int i=0; i<nEventsAll; i++)
  {
    // define an empty reference EtaScale vector
    const std::vector<EnergyScale> *EtaScale;

    // check run range
    if (allRunNum.at(i)>=Amin&&allRunNum.at(i)<=Amax) { EtaScale = &EtaScaleA; NumA++;}
    else if (allRunNum.at(i)>=Bmin&&allRunNum.at(i)<=Bmax) { EtaScale = &EtaScaleB; NumB++;}
    else if (allRunNum.at(i)>=Cmin&&allRunNum.at(i)<=Cmax) { EtaScale = &EtaScaleC; NumC++;}
    else if (allRunNum.at(i)>=Dmin&&allRunNum.at(i)<=Dmax) { EtaScale = &EtaScaleD; NumD++;}
    else continue;
    
    // count 
    NumAll++;
    
    // findout which bins it belongs to
    int bin1(-1), bin2(-1);
    for (int ibin=0; ibin<(int)EtaScale->size(); ibin++)
    {
      if (allEta1.at(i)>EtaScale->at(ibin).min&&allEta1.at(i)<EtaScale->at(ibin).max) bin1 = ibin;
      if (allEta2.at(i)>EtaScale->at(ibin).min&&allEta2.at(i)<EtaScale->at(ibin).max) bin2 = ibin;
    }

    // apply eta scale
    if (bin1>=0) allEReg1.at(i) *= EtaScale->at(bin1).s;
    if (bin2>=0) allEReg2.at(i) *= EtaScale->at(bin2).s;

  }

  std::cout << "variables.h:: ApplyEtaScaleToAllEventsABCD(): INFO: " 
        << "NevtsAll: " << NumAll << "; "  
        << "NevtsA: " << NumA << "; "
        << "NevtsB: " << NumB << "; "
        << "NevtsC: " << NumC << "; "
        << "NevtsD: " << NumD  
        << std::endl;
}
///////////////

//////////
void ApplyEtaRingEtaScaleToAllEventsABCD(const std::vector<EtaRingEnergyScale>& EtaScaleA,
                                         const std::vector<EtaRingEnergyScale>& EtaScaleB,
                                         const std::vector<EtaRingEnergyScale>& EtaScaleC,
                                         const std::vector<EtaRingEnergyScale>& EtaScaleD)
{
  // ABCD runNum range
  const int Amin(190645), Amax(193621);
  const int Bmin(193834), Bmax(196531);
  const int Cmin(198022), Cmax(203742);
  const int Dmin(203777), Dmax(208686);

  // counts
  int NumA(0), NumB(0), NumC(0), NumD(0), NumAll(0);

  // loop over all events
  for (int i=0; i<nEventsAll; i++)
  {
    // define an empty reference EtaScale vector
    const std::vector<EtaRingEnergyScale> *EtaScale;

    // check run range
    if (allRunNum.at(i)>=Amin&&allRunNum.at(i)<=Amax) { EtaScale = &EtaScaleA; NumA++;}
    else if (allRunNum.at(i)>=Bmin&&allRunNum.at(i)<=Bmax) { EtaScale = &EtaScaleB; NumB++;}
    else if (allRunNum.at(i)>=Cmin&&allRunNum.at(i)<=Cmax) { EtaScale = &EtaScaleC; NumC++;}
    else if (allRunNum.at(i)>=Dmin&&allRunNum.at(i)<=Dmax) { EtaScale = &EtaScaleD; NumD++;}
    else continue;

    // count
    NumAll++;

    // findout which bins it belongs to
    int bin1(-1), bin2(-1);
    for (int ibin=0; ibin<(int)EtaScale->size(); ibin++)
    {
      if (GetEtaRing(allSeedIX1.at(i), allSeedIY1.at(i), allSeedIZ1.at(i))==EtaScale->at(ibin).EtaRing) bin1 = ibin;
      if (GetEtaRing(allSeedIX2.at(i), allSeedIY2.at(i), allSeedIZ2.at(i))==EtaScale->at(ibin).EtaRing) bin2 = ibin;
    }

    // apply eta scale
    if (bin1>=0) allEReg1.at(i) *= EtaScale->at(bin1).s;
    if (bin2>=0) allEReg2.at(i) *= EtaScale->at(bin2).s;

    // debug
    //if (bin1>=0) std::cout << "EtaScale = " << EtaScale->at(bin1).s << std::endl; 
    //if (bin2>=0) std::cout << "EtaScale = " << EtaScale->at(bin2).s << std::endl; 

  }

  std::cout << "variables.h:: ApplyEtaRingEtaScaleToAllEventsABCD(): INFO: "
        << "NevtsAll: " << NumAll << "; "
        << "NevtsA: " << NumA << "; "
        << "NevtsB: " << NumB << "; "
        << "NevtsC: " << NumC << "; "
        << "NevtsD: " << NumD
        << std::endl;
}
//////////////////

void ApplyEtaRingEtaScaleToSelectedEvents(const std::vector<EtaRingEnergyScale>& EtaScale, const int ibin=-1 )
{
  // this function modifies the E1 and E2 vectors to use them store the (REgression Energy * Eta Scale).
  // check if there are selected events
  int nevents = (int)E1.size();
  if (nevents<=0) 
  {
    std::cout << "ApplyEtaRingEtaScaleToSelectedEvents:: No selected events ." << std::endl;
    abort();
  }
  
  // loop over all events
  for (int i=0; i<nevents; i++)
  {
    // "if" protection below makes sure that the changing of E1 and E2 to store the eta-scaled EReg only 
    //     happens to the eta-rings that not to be fitted this time.  
    // at least be the Reg Energy
    if (ScaleBin1.at(i)>=0.&&ScaleBin1.at(i)!=ibin) *(E1.at(i)) = *(EReg1.at(i));
    if (ScaleBin2.at(i)>=0.&&ScaleBin2.at(i)!=ibin) *(E2.at(i)) = *(EReg2.at(i));

    // apply eta scale, except the ibin that being fitted
    if (ScaleBin1.at(i)>=0.&&ScaleBin1.at(i)!=ibin) (*(E1.at(i))) *= EtaScale.at( ScaleBin1.at(i) ).s;
    if (ScaleBin2.at(i)>=0.&&ScaleBin2.at(i)!=ibin) (*(E2.at(i))) *= EtaScale.at( ScaleBin2.at(i) ).s;

  }

}

//////////////////

void ApplyEtaRingEtaScaleToAllEventsWithNewICs(const std::vector<EtaRingEnergyScale>& EtaScale)
{
  // this function modifies the allE1 and allE2 vectors to use them store : 
  // Enew = Ereg/ErawOld * ErawNew * EtaScale
  //    where the ErawNew is recalculated from the SC hits after applying the New ICs.

  // check if there are selected events
  int nevents = (int)allE1.size();
  if (nevents<=0)
  {
    std::cout << "ApplyEtaRingEtaScaleToAllEventsWithNewICs:: No selected events ." << std::endl;
    abort();
  }

  // check if the New ICs are applied
  if (nevents != (int)allRawSCE1.size() ) 
  {
    std::cout << "ApplyEtaRingEtaScaleToAllEventsWithNewICs:: raw ICs are not applied correctly ." << std::endl;
    abort();
  }

  // loop over all events
  for (int i=0; i<nevents; i++)
  {
    // "if" protection below makes sure that the changing of E1 and E2 to store the eta-scaled EReg only
    //     happens to the eta-rings that not to be fitted this time.
    
    // ele1
    if (allScaleBin1.at(i)>=0.)
    {
      double RegScale = allERegScale1.at(i); 
      double NewEraw = allRawSCE1.at(i);
      allE1.at(i) = RegScale * NewEraw * EtaScale.at( allScaleBin1.at(i) ).s;
    }

    // ele2
    if (allScaleBin2.at(i)>=0.)
    {
      double RegScale = allERegScale2.at(i);
      double NewEraw = allRawSCE2.at(i);
      allE2.at(i) = RegScale * NewEraw * EtaScale.at( allScaleBin2.at(i) ).s;
    }

  }

}



///////////

// select groups of events according to a vector of cells,
// such as a supercluster.
int SelectSubsetEvents(std::vector<std::vector<int> > cells)
{
  // cells to be selected
  if ((int)cells.size()==0)
  {
    return 0;
  }
  // clear previous vectors
  nEvents = 0;
  nSignals = 0;
  E1.clear();
  EReg1.clear();
  Eta1.clear();
  Phi1.clear();
  E2.clear();
  EReg2.clear();
  Eta2.clear();
  Phi2.clear();
  nHits1.clear();
  nHits2.clear();
  HitE1.clear();
  HitE2.clear();
  HitIX1.clear();
  HitIY1.clear();
  HitIZ1.clear();
  HitIX2.clear();
  HitIY2.clear();
  HitIZ2.clear();
  
  // loop over all events and select events
  for (int i=0; i<nEventsAll; i++)
  {
    bool take=false;
    // loop over all hits of electron1
    for (int ii=0; ii<(int)allHitE1.at(i).size(); ii++ )
    {
      // if one hit match, then no need to loop over the rest hits
      if (take) break;
      // loop over all cells to be selected
      for (int icell=0; icell<(int)cells.size(); icell++)
      {
        if((allHitIX1.at(i).at(ii)==cells.at(icell).at(0)) &&
           (allHitIY1.at(i).at(ii)==cells.at(icell).at(1)) && 
           (allHitIZ1.at(i).at(ii)==cells.at(icell).at(2)))
        {
          // if there is even one hit match a cell in selection, take the event
          take = true;
          break;
        }
      }
    }
    // loop over all hits of electron2
    for (int ii=0; ii<(int)allHitE2.at(i).size(); ii++ )
    {
      // if one hit match, then no need to loop over the rest hits
      if (take) break;
      // loop over all cells to be selected
      for (int icell=0; icell<(int)cells.size(); icell++)
      {
        if((allHitIX2.at(i).at(ii)==cells.at(icell).at(0)) &&
           (allHitIY2.at(i).at(ii)==cells.at(icell).at(1)) && 
           (allHitIZ2.at(i).at(ii)==cells.at(icell).at(2)))
        {
          // if there is even one hit match a cell in selection, take the event
          take = true;
          break;
        }
      }
    }
    
    // if do not decide to take this event, continue
    if (!take) continue;
    
    // if not continue above, it is a useful event ot use
    E1.push_back(&(allE1.at(i)));
    EReg1.push_back(&(allEReg1.at(i)));
    Eta1.push_back(&(allEta1.at(i)));
    Phi1.push_back(&(allPhi1.at(i)));
    E2.push_back(&(allE2.at(i)));
    EReg2.push_back(&(allEReg2.at(i)));
    Eta2.push_back(&(allEta2.at(i)));
    Phi2.push_back(&(allPhi2.at(i)));
    nHits1.push_back(&(allnHits1.at(i)));
    HitE1.push_back(&(allHitE1.at(i)));
    HitIX1.push_back(&(allHitIX1.at(i)));
    HitIY1.push_back(&(allHitIY1.at(i)));
    HitIZ1.push_back(&(allHitIZ1.at(i)));
    nHits2.push_back(&(allnHits2.at(i)));
    HitE2.push_back(&(allHitE2.at(i)));
    HitIX2.push_back(&(allHitIX2.at(i)));
    HitIY2.push_back(&(allHitIY2.at(i)));
    HitIZ2.push_back(&(allHitIZ2.at(i)));
  }
  
  // nEvents
  nEvents = (int)E1.size();
  nSignals = nEvents; // assume no background (fix me)
  //
  return nEvents;
}


// select groups of events according to a vector of cells,
// such as a supercluster,
// with a choice of EBEB, EBEE, or EEEE combination
int SelectSubsetEventsWithEBOrEECombine(std::vector<std::vector<int> > cells, const std::string Combine="")
{
  // cells to be selected
  if ((int)cells.size()==0)
  {
    return 0;
  } 
  // clear previous vectors
  nEvents = 0;
  nSignals = 0;
  E1.clear();
  EReg1.clear();
  Eta1.clear();
  Phi1.clear();
  E2.clear();
  EReg2.clear();
  Eta2.clear();
  Phi2.clear();
  nHits1.clear();
  nHits2.clear();
  HitE1.clear();
  HitE2.clear();
  HitIX1.clear();
  HitIY1.clear();
  HitIZ1.clear();
  HitIX2.clear();
  HitIY2.clear();
  HitIZ2.clear();

  // loop over all events and select events
  for (int i=0; i<nEventsAll; i++)
  {
    // EB or EE combinatioin check
    if ( Combine=="EBEB" ) // both in EB
    {
      if ( !(fabs(allEta1[i])<1.48&&fabs(allEta2[i])<1.48) ) continue;
    }
    if ( Combine=="EBEE" ) // one in EB one in EE
    {
      if ( !( (fabs(allEta1[i])<1.48&&fabs(allEta2[i])>1.48)||(fabs(allEta2[i])<1.48&&fabs(allEta1[i])>1.48) ) ) continue;
    }
    if ( Combine=="EEEE" ) // both in EE
    {
      if ( !(fabs(allEta1[i])>1.48&&fabs(allEta2[i])>1.48) ) continue;
    }
    if ( Combine=="EE" ) // any one of the two in EE
    {
      if ( !(fabs(allEta1[i])>1.48||fabs(allEta2[i])>1.48) ) continue;
    }
    if ( Combine=="EB" ) // any one of the two in EB
    {
      if ( !(fabs(allEta1[i])<1.48||fabs(allEta2[i])<1.48) ) continue;
    }


    bool take=false;
    // loop over all hits of electron1
    for (int ii=0; ii<(int)allHitE1.at(i).size(); ii++ )
    {
      // if one hit match, then no need to loop over the rest hits
      if (take) break;
      // loop over all cells to be selected
      for (int icell=0; icell<(int)cells.size(); icell++)
      {
        if((allHitIX1.at(i).at(ii)==cells.at(icell).at(0)) &&
           (allHitIY1.at(i).at(ii)==cells.at(icell).at(1)) &&
           (allHitIZ1.at(i).at(ii)==cells.at(icell).at(2)))
        {
          // if there is even one hit match a cell in selection, take the event
          take = true;
          break;
        }
      }
    }
    // loop over all hits of electron2
    for (int ii=0; ii<(int)allHitE2.at(i).size(); ii++ )
    {
      // if one hit match, then no need to loop over the rest hits
      if (take) break;
      // loop over all cells to be selected
      for (int icell=0; icell<(int)cells.size(); icell++)
      {
        if((allHitIX2.at(i).at(ii)==cells.at(icell).at(0)) &&
           (allHitIY2.at(i).at(ii)==cells.at(icell).at(1)) &&
           (allHitIZ2.at(i).at(ii)==cells.at(icell).at(2)))
        {
          // if there is even one hit match a cell in selection, take the event
          take = true;
          break;
        }
      }
    }

    // if do not decide to take this event, continue
    if (!take) continue;

    // if not continue above, it is a useful event ot use
    E1.push_back(&(allE1.at(i)));
    EReg1.push_back(&(allEReg1.at(i)));
    Eta1.push_back(&(allEta1.at(i)));
    Phi1.push_back(&(allPhi1.at(i)));
    E2.push_back(&(allE2.at(i)));
    EReg2.push_back(&(allEReg2.at(i)));
    Eta2.push_back(&(allEta2.at(i)));
    Phi2.push_back(&(allPhi2.at(i)));
    nHits1.push_back(&(allnHits1.at(i)));
    HitE1.push_back(&(allHitE1.at(i)));
    HitIX1.push_back(&(allHitIX1.at(i)));
    HitIY1.push_back(&(allHitIY1.at(i)));
    HitIZ1.push_back(&(allHitIZ1.at(i)));
    nHits2.push_back(&(allnHits2.at(i)));
    HitE2.push_back(&(allHitE2.at(i)));
    HitIX2.push_back(&(allHitIX2.at(i)));
    HitIY2.push_back(&(allHitIY2.at(i)));
    HitIZ2.push_back(&(allHitIZ2.at(i)));

  }

  // nEvents
  nEvents = (int)E1.size();
  nSignals = nEvents; // assume no background (fix me)
  //
  return nEvents;

}


// cells in 1.83<eta<2.17
// a band between 25 to 35 crystals apart from the center.
std::vector<std::vector<int> > GetCellsEta1p83To2p17()
{
  std::vector<std::vector<int> > cells;
  
  // loop over all cells and select those in the region
  for (int iz=-1; iz<=1; iz=iz+2 )
  {
    for (int ix=1; ix<=100; ix++)
    {
      for (int iy=1; iy<=100; iy++)
      {
        // R between 25 to 35 crystals
        // thus R=sqrt(xx*xx+yy*yy)
        // xx = (ix-0.5)-50.0
        // yy = (iy-0.5)-50.0
        double xx = (double(ix)-0.5)-50.0;
        double yy = (double(iy)-0.5)-50.0;
        double R = sqrt(xx*xx+yy*yy);
        if (R<=35&&R>=25)
        {
          std::vector<int> acell;
          acell.push_back(ix);
          acell.push_back(iy);
          acell.push_back(iz);
          cells.push_back(acell);
        }
      }
    }
  }
  return cells;
}

std::vector<std::vector<int> > GetAllCellsInEEP()
{
  std::vector<std::vector<int> > cells;
  
  int ix=0;
  int iy=0;
  int iz=+1;
  
  // print cells from ix left to right
  for (ix=1; ix<=100; ix++)
  {
    for (iy=1; iy<=100; iy++)
    {
      // a list of exclusions
      
      // outer
      // left top
      if (ix<4&&iy>60) continue;
      if (ix<6&&iy>65) continue;
      if (ix<9&&iy>75) continue;
      if (ix<14&&iy>80) continue;
      if (ix<16&&iy>85) continue;
      if (ix<21&&iy>87) continue;
      if (ix<26&&iy>92) continue;
      if (ix<36&&iy>95) continue;
      if (ix<41&&iy>97) continue;
      // left bottom
      if (ix<4&&iy<41) continue;
      if (ix<6&&iy<36) continue;
      if (ix<9&&iy<26) continue;
      if (ix<14&&iy<21) continue;
      if (ix<16&&iy<16) continue;
      if (ix<21&&iy<14) continue;
      if (ix<26&&iy<9) continue;
      if (ix<36&&iy<6) continue;
      if (ix<41&&iy<4) continue;
      // right top
      if (ix>60&&iy>97) continue;
      if (ix>65&&iy>95) continue;
      if (ix>75&&iy>92) continue;
      if (ix>80&&iy>87) continue;
      if (ix>85&&iy>85) continue;
      if (ix>87&&iy>80) continue;
      if (ix>92&&iy>75) continue;
      if (ix>95&&iy>65) continue;
      if (ix>97&&iy>60) continue;
      // right bottom
      if (ix>60&&iy<4) continue;
      if (ix>65&&iy<6) continue;
      if (ix>75&&iy<9) continue;
      if (ix>80&&iy<14) continue;
      if (ix>85&&iy<16) continue;
      if (ix>87&&iy<21) continue;
      if (ix>92&&iy<26) continue;
      if (ix>95&&iy<36) continue;
      if (ix>97&&iy<41) continue;

      // inner
      if (iy==40&&ix>45&&ix<56) continue;
      if (iy==41&&ix>43&&ix<58) continue;
      if (iy==42&&ix>42&&ix<59) continue;
      if (iy==43&&ix>41&&ix<60) continue;
      if (iy==44&&ix>40&&ix<61) continue;
      if (iy==45&&ix>40&&ix<61) continue;
      if (iy>45&&iy<56&&ix>39&&ix<62) continue;
      if (iy==56&&ix>40&&ix<61) continue;
      if (iy==57&&ix>40&&ix<61) continue;
      if (iy==58&&ix>41&&ix<60) continue;
      if (iy==59&&ix>42&&ix<59) continue;
      if (iy==60&&ix>43&&ix<58) continue;
      if (iy==61&&ix>45&&ix<56) continue;
      
      std::vector<int> acell;
      acell.push_back(ix);
      acell.push_back(iy);
      acell.push_back(iz);
      cells.push_back(acell);
    }
  }

  //return
  return cells;
  
}

std::vector<std::vector<int> > GetAllCellsInEEN()
{
  std::vector<std::vector<int> > cells;
  
  int ix=0;
  int iy=0;
  int iz=-1;
  
  // print cells from ix left to right
  
  for (ix=1; ix<=100; ix++)
  {
    for (iy=1; iy<=100; iy++)
    {
      // a list of exclusions
      
      // outer
      // left top
      if (ix<4&&iy>60) continue;
      if (ix<6&&iy>65) continue;
      if (ix<9&&iy>75) continue;
      if (ix<14&&iy>80) continue;
      if (ix<16&&iy>85) continue;
      if (ix<21&&iy>87) continue;
      if (ix<26&&iy>92) continue;
      if (ix<36&&iy>95) continue;
      if (ix<41&&iy>97) continue;
      // left bottom
      if (ix<4&&iy<41) continue;
      if (ix<6&&iy<36) continue;
      if (ix<9&&iy<26) continue;
      if (ix<14&&iy<21) continue;
      if (ix<16&&iy<16) continue;
      if (ix<21&&iy<14) continue;
      if (ix<26&&iy<9) continue;
      if (ix<36&&iy<6) continue;
      if (ix<41&&iy<4) continue;
      // right top
      if (ix>60&&iy>97) continue;
      if (ix>65&&iy>95) continue;
      if (ix>75&&iy>92) continue;
      if (ix>80&&iy>87) continue;
      if (ix>85&&iy>85) continue;
      if (ix>87&&iy>80) continue;
      if (ix>92&&iy>75) continue;
      if (ix>95&&iy>65) continue;
      if (ix>97&&iy>60) continue;
      // right bottom
      if (ix>60&&iy<4) continue;
      if (ix>65&&iy<6) continue;
      if (ix>75&&iy<9) continue;
      if (ix>80&&iy<14) continue;
      if (ix>85&&iy<16) continue;
      if (ix>87&&iy<21) continue;
      if (ix>92&&iy<26) continue;
      if (ix>95&&iy<36) continue;
      if (ix>97&&iy<41) continue;

      // inner
      if (iy==40&&ix>45&&ix<56) continue;
      if (iy==41&&ix>43&&ix<58) continue;
      if (iy==42&&ix>42&&ix<59) continue;
      if (iy==43&&ix>41&&ix<60) continue;
      if (iy==44&&ix>40&&ix<61) continue;
      if (iy==45&&ix>40&&ix<61) continue;
      if (iy>45&&iy<56&&ix>39&&ix<62) continue;
      if (iy==56&&ix>40&&ix<61) continue;
      if (iy==57&&ix>40&&ix<61) continue;
      if (iy==58&&ix>41&&ix<60) continue;
      if (iy==59&&ix>42&&ix<59) continue;
      if (iy==60&&ix>43&&ix<58) continue;
      if (iy==61&&ix>45&&ix<56) continue;
      
      std::vector<int> acell;
      acell.push_back(ix);
      acell.push_back(iy);
      acell.push_back(iz);
      cells.push_back(acell);
    }
  }

  //return
  return cells;
  
}

std::vector<std::vector<int> > GetAllCellsInEE()
{
  std::vector<std::vector<int> > cells;
  
  int ix=0;
  int iy=0;
  int iz=-1;
  
  for (iz=-1; iz<=+1; iz=iz+2)
  {
    // print cells from ix left to right
    for (ix=1; ix<=100; ix++)
    {
      for (iy=1; iy<=100; iy++)
      {
        // a list of exclusions
      
        // outer
        // left top
        if (ix<4&&iy>60) continue;
        if (ix<6&&iy>65) continue;
        if (ix<9&&iy>75) continue;
        if (ix<14&&iy>80) continue;
        if (ix<16&&iy>85) continue;
        if (ix<21&&iy>87) continue;
        if (ix<26&&iy>92) continue;
        if (ix<36&&iy>95) continue;
        if (ix<41&&iy>97) continue;
        // left bottom
        if (ix<4&&iy<41) continue;
        if (ix<6&&iy<36) continue;
        if (ix<9&&iy<26) continue;
        if (ix<14&&iy<21) continue;
        if (ix<16&&iy<16) continue;
        if (ix<21&&iy<14) continue; 
        if (ix<26&&iy<9) continue;
        if (ix<36&&iy<6) continue;
        if (ix<41&&iy<4) continue;
        // right top
        if (ix>60&&iy>97) continue;
        if (ix>65&&iy>95) continue;
        if (ix>75&&iy>92) continue;
        if (ix>80&&iy>87) continue;
        if (ix>85&&iy>85) continue;
        if (ix>87&&iy>80) continue;
        if (ix>92&&iy>75) continue;
        if (ix>95&&iy>65) continue;
        if (ix>97&&iy>60) continue;
        // right bottom
        if (ix>60&&iy<4) continue;
        if (ix>65&&iy<6) continue;
        if (ix>75&&iy<9) continue;
        if (ix>80&&iy<14) continue;
        if (ix>85&&iy<16) continue;
        if (ix>87&&iy<21) continue;
        if (ix>92&&iy<26) continue;
        if (ix>95&&iy<36) continue;
        if (ix>97&&iy<41) continue;

        // inner
        if (iy==40&&ix>45&&ix<56) continue;
        if (iy==41&&ix>43&&ix<58) continue;
        if (iy==42&&ix>42&&ix<59) continue;
        if (iy==43&&ix>41&&ix<60) continue;
        if (iy==44&&ix>40&&ix<61) continue;
        if (iy==45&&ix>40&&ix<61) continue;
        if (iy>45&&iy<56&&ix>39&&ix<62) continue;
        if (iy==56&&ix>40&&ix<61) continue;
        if (iy==57&&ix>40&&ix<61) continue;
        if (iy==58&&ix>41&&ix<60) continue;
        if (iy==59&&ix>42&&ix<59) continue;
        if (iy==60&&ix>43&&ix<58) continue;
        if (iy==61&&ix>45&&ix<56) continue;
      
        std::vector<int> acell;
        acell.push_back(ix);
        acell.push_back(iy);
        acell.push_back(iz);
        cells.push_back(acell);
      }
    }
  }
  //return
  return cells;
  
}

std::vector<std::vector<int> > GetAllCellsInEB()
{
  std::vector<std::vector<int> > cells;
  
  int ix=0;  // iEta
  int iy=0;  // iPhi
  int iz=0;  // 0 for EB

  // print cells from ix (iEta) left to right
  for (ix=-85; ix<=+85; ix++)
  {
    // ix (iEta) not to be 0, no iEta=0
    if (ix==0) continue;
     
    // loop over iy (iPhi) 
    for (iy=1; iy<=360; iy++)
    {
      std::vector<int> acell;
      acell.push_back(ix);
      acell.push_back(iy);
      acell.push_back(iz);
      cells.push_back(acell);
    }
  }  

  //return
  return cells;
  
}

std::vector<std::vector<int> > GetAllCellsFromCalibTable(const char* filename)
{
  std::vector<std::vector<int> > cells;
  std::ifstream myfile(filename);
  std::string line;
  int idx, ix, iy, iz, fixed, nfits;
  double c, cerr;
  if (myfile.is_open())
  {
    while (getline(myfile,line))
    {
      calibRecord calib;
      std::stringstream sline(line);
      sline >> idx
             >> ix
             >> iy
             >> iz
             >> c
             >> cerr
             >> fixed
             >> nfits ;
      std::vector<int> acell;
      acell.push_back(ix);
      acell.push_back(iy);
      acell.push_back(iz);
      cells.push_back(acell);
    }
    myfile.close();
  }
  
  //return
  return cells;
  
}

std::vector<EtaRingEnergyScale> GetEmptyEtaRingEtaScaleBins()
{

    // Eta bins
    std::vector<EtaRingEnergyScale> EtaScale;

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

    return EtaScale;
}


std::map<int, std::map<int, std::map<int, calibRecord> > > GetCalibTableMapFromFile(const char* filename = "calibTableRef_in.dat")
{

  std::map<int, std::map<int, std::map<int, calibRecord> > > aCalibTableMap;

  std::ifstream myfile(filename);
  std::string line;
  if (myfile.is_open())
  {
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
          
      aCalibTableMap[calib.ix][calib.iy][calib.iz] = calib;

    }
    myfile.close();
  }
  else 
  {
    std::cout << "GetCalibTableMapFromFile:: fail to open file " << filename << std::endl;
    abort(); 
  }
  
  return aCalibTableMap;

}

