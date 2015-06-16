
// Author Hengne Li @ UVA and CERN

#include "TROOT.h"
#include "TChain.h"
#include "TTree.h"


// variables for ROOT Tree
//Declaration of leaves types
   Int_t           runNumber;
   ULong64_t       eventNumber;
   Int_t           lumiBlock;
   UInt_t          runTime;
   Float_t         mcGenWeight;
   Char_t          HLTfire;
   Int_t           nPU[1];
   Float_t         rho;
   Int_t           nPV;
   Int_t           eleID[3];
   Int_t           chargeEle[3];
   Float_t         etaSCEle[3];
   Float_t         phiSCEle[3];
   Float_t         etaEle[3];
   Float_t         phiEle[3];
   Int_t           classificationEle[3];
   Int_t           recoFlagsEle[3];
   Float_t         PtEle[3];
   Float_t         fbremEle[3];
   Float_t         seedXSCEle[3];
   Float_t         seedYSCEle[3];
   Float_t         seedEnergySCEle[3];
   Float_t         seedLCSCEle[3];
   Float_t         avgLCSCEle[3];
   UChar_t         gainEle[3];
   Float_t         energyMCEle[3];
   Float_t         energySCEle[3];
   Float_t         rawEnergySCEle[3];
   Float_t         esEnergySCEle[3];
   Float_t         energySCEle_corr[3];
   Float_t         R9Ele[3];
   Float_t         e5x5SCEle[3];
   Float_t         pModeGsfEle[3];
   Float_t         pAtVtxGsfEle[3];
   Float_t         pNormalizedChi2Ele[3];
   Float_t         trackMomentumErrorEle[3];
   Float_t         invMass;
   Float_t         invMass_SC;
   Float_t         invMass_e5x5;
   Float_t         invMass_rawSC;
   Float_t         invMass_rawSC_esSC;
   Float_t         invMass_SC_corr;
   Float_t         invMass_MC;
   Float_t         invMass_mumu;
   Float_t         etaMCEle[3];
   Float_t         phiMCEle[3];
   Int_t           nHitsSCEle[3];


// extra tree
//Declaration of leaves types
   ULong64_t       runTime1;
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
void SetTreeBranch(TTree* tree)
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
   tree->SetBranchAddress("R9Ele",R9Ele);
   tree->SetBranchAddress("e5x5SCEle",e5x5SCEle);
   tree->SetBranchAddress("pModeGsfEle",pModeGsfEle);
   tree->SetBranchAddress("pAtVtxGsfEle",pAtVtxGsfEle);
   tree->SetBranchAddress("pNormalizedChi2Ele",pNormalizedChi2Ele);
   tree->SetBranchAddress("trackMomentumErrorEle",trackMomentumErrorEle);
   tree->SetBranchAddress("invMass",&invMass);
   tree->SetBranchAddress("invMass_SC",&invMass_SC);
   tree->SetBranchAddress("invMass_e5x5",&invMass_e5x5);
   tree->SetBranchAddress("invMass_rawSC",&invMass_rawSC);
   tree->SetBranchAddress("invMass_rawSC_esSC",&invMass_rawSC_esSC);
   tree->SetBranchAddress("invMass_SC_corr",&invMass_SC_corr);
   tree->SetBranchAddress("invMass_MC",&invMass_MC);
   tree->SetBranchAddress("invMass_mumu",&invMass_mumu);
   tree->SetBranchAddress("etaMCEle",etaMCEle);
   tree->SetBranchAddress("phiMCEle",phiMCEle);
   tree->SetBranchAddress("nHitsSCEle",nHitsSCEle);

}

// set tree branches
void SetExtraTreeBranch(TTree* extraCalibTree){

   // Set branch addresses.
   extraCalibTree->SetBranchAddress("runNumber",&runNumber);
   extraCalibTree->SetBranchAddress("eventNumber",&eventNumber);
   extraCalibTree->SetBranchAddress("lumiBlock",&lumiBlock);
   extraCalibTree->SetBranchAddress("runTime",&runTime1);
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


