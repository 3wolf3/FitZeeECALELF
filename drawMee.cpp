#include "TFile.h"
#include "drawMee.h"

int _nbins = 240;
double _scale = 1.0; //1.04141815; //1.040002;
int _oddeven = 0; // 0: both, 1: Odd, 2: Even

char etascale_ref[3000];
char etascale_refA[3000];
char etascale_refB[3000];
char etascale_refC[3000];
char etascale_refD[3000];

std::string regVersion = "RegV8";

int main(int argc, char* argv[])
{
  if (argc<4)
  {
    std::cout << argv[0] << " <input_tree_file.root> <calib_table_file.dat> <output_file.root> <max_n_events> <method> <overall_scale> <OddEven> <eta_scale_file> \\n"
     << "       <regVersion> "
    << std::endl;
    return 0;
  }
  
  std::string inrootfilename(argv[1]);
  std::string calibtablename(argv[2]);
  std::string outrootfilename(argv[3]);
 
  int maxevt = -1;
  if (argc>4)
  {
    maxevt = atoi(argv[4]);
  }
  
  int method=31;
  if (argc>5)
  {
    method = atoi(argv[5]);
  }
  
  if (argc>6)
  {
    _scale = atof(argv[6]);
  }

  if (argc>7)
  {
    _oddeven = atoi(argv[7]);
  }

  if (argc>8)
  {
    sprintf(etascale_ref, "%s", argv[8]);
  }

  if (argc>9)
  {
    regVersion = std::string(argv[9]);
  }

  // check
  if (method==7)
  {
    if (argc<=8)
    {
      std::cout << "Missing etascale reference file. Please run " << argv[0] << " to print usage information. " << std::endl;
      return 1;
    }
  }

  if (method==71||method==72)
  {
    if (argc<=8)
    {
      std::cout << "Missing etascale reference file. Please run " << argv[0] << " to print usage information. " << std::endl;
      return 1;
    }
    else
    {
      std::string s(argv[8]);
      std::string delimiter = ";";
      std::vector<std::string> ss;
      size_t pos = 0;
      std::string token;
      while ((pos = s.find(delimiter)) != std::string::npos) {
        token = s.substr(0, pos);
        s.erase(0, pos + delimiter.length());
        ss.push_back(token);
      }
      ss.push_back(s);

      sprintf(etascale_refA, "%s", ss.at(0).c_str());
      sprintf(etascale_refB, "%s", ss.at(1).c_str());
      sprintf(etascale_refC, "%s", ss.at(2).c_str());
      sprintf(etascale_refD, "%s", ss.at(3).c_str());

    }

  }


  std::cout << "Input file: " << inrootfilename << std::endl;
  std::cout << "Calib Table file: " << calibtablename << std::endl;
  std::cout << "ouput file: " << outrootfilename << std::endl;
  std::cout << "max events: " << maxevt << std::endl;
  std::cout << "method: " << method << std::endl;
  std::cout << "scale: " << _scale << std::endl;
  std::cout << "RegVersion: " << regVersion << std::endl;
  std::cout << "Both/Odd/Even: " << _oddeven << std::endl;
  if (method==7) std::cout << "  EtaScale Reference File = " << etascale_ref << std::endl;
  if (method==71||method==72)
  {
    std::cout << "  EtaScale Reference File A = " << etascale_refA << std::endl;
    std::cout << "  EtaScale Reference File B = " << etascale_refB << std::endl;
    std::cout << "  EtaScale Reference File C = " << etascale_refC << std::endl;
    std::cout << "  EtaScale Reference File D = " << etascale_refD << std::endl;
  }

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
  TFile* fout = new TFile(outrootfilename.c_str(), "recreate");

  // calibTable
  std::vector<calibRecord> calibTable = getCalibTableFromFile(calibtablename.c_str());
  
  std::vector<EnergyScale> EtaScaleRef;
  if (method==7)
  {
    // read reference scales
    std::ifstream reffile(etascale_ref);
    if (reffile.is_open())
    {
      std::string line;
      EnergyScale scale;
      while (getline(reffile,line))
      {
        std::stringstream sline(line);
        sline >> scale.min
            >> scale.max
            >> scale.s
            >> scale.serr;
        EtaScaleRef.push_back(scale);
      }
      reffile.close();
    }
  }

  std::vector<EnergyScale> EtaScaleRefA;
  std::vector<EnergyScale> EtaScaleRefB;
  std::vector<EnergyScale> EtaScaleRefC;
  std::vector<EnergyScale> EtaScaleRefD;
  if (method==71)
  {
    // read reference scales
    // A
    std::ifstream reffileA(etascale_refA);
    if (reffileA.is_open())
    {
      std::string line;
      EnergyScale scale;
      while (getline(reffileA,line))
      {
        std::stringstream sline(line);
        sline >> scale.min
            >> scale.max
            >> scale.s
            >> scale.serr;
        EtaScaleRefA.push_back(scale);
      }
      reffileA.close();
    }
    // B
    std::ifstream reffileB(etascale_refB);
    if (reffileB.is_open())
    {
      std::string line;
      EnergyScale scale;
      while (getline(reffileB,line))
      {
        std::stringstream sline(line);
        sline >> scale.min
            >> scale.max
            >> scale.s
            >> scale.serr;
        EtaScaleRefB.push_back(scale);
      }
      reffileB.close();
    }
    // C
    std::ifstream reffileC(etascale_refC);
    if (reffileC.is_open())
    {
      std::string line;
      EnergyScale scale;
      while (getline(reffileC,line))
      {
        std::stringstream sline(line);
        sline >> scale.min
            >> scale.max
            >> scale.s
            >> scale.serr;
        EtaScaleRefC.push_back(scale);
      }
      reffileC.close();
    }
    // D
    std::ifstream reffileD(etascale_refD);
    if (reffileD.is_open())
    {
      std::string line;
      EnergyScale scale;
      while (getline(reffileD,line))
      {
        std::stringstream sline(line);
        sline >> scale.min
            >> scale.max
            >> scale.s
            >> scale.serr;
        EtaScaleRefD.push_back(scale);
      }
      reffileD.close();
    }
  }

  // method 72
  std::vector<EtaRingEnergyScale> EtaRingEtaScaleRefA;
  std::vector<EtaRingEnergyScale> EtaRingEtaScaleRefB;
  std::vector<EtaRingEnergyScale> EtaRingEtaScaleRefC;
  std::vector<EtaRingEnergyScale> EtaRingEtaScaleRefD;
  if (method==72)
  {
    // init EtaRing table
    initEEEtaRingTable();
    // read reference scales
    // A
    std::ifstream reffileA(etascale_refA);
    if (reffileA.is_open())
    {
      std::string line;
      EtaRingEnergyScale scale;
      while (getline(reffileA,line))
      {
        std::stringstream sline(line);
        sline >> scale.EtaRing
            >> scale.s
            >> scale.serr;
        EtaRingEtaScaleRefA.push_back(scale);
      }
      reffileA.close();
    }
    // B
    std::ifstream reffileB(etascale_refB);
    if (reffileB.is_open())
    {
      std::string line;
      EtaRingEnergyScale scale;
      while (getline(reffileB,line))
      {
        std::stringstream sline(line);
        sline >> scale.EtaRing
            >> scale.s
            >> scale.serr;
        EtaRingEtaScaleRefB.push_back(scale);
      }
      reffileB.close();
    }
    // C
    std::ifstream reffileC(etascale_refC);
    if (reffileC.is_open())
    {
      std::string line;
      EtaRingEnergyScale scale;
      while (getline(reffileC,line))
      {
        std::stringstream sline(line);
        sline >> scale.EtaRing
            >> scale.s
            >> scale.serr;
        EtaRingEtaScaleRefC.push_back(scale);
      }
      reffileC.close();
    }
    // D
    std::ifstream reffileD(etascale_refD);
    if (reffileD.is_open())
    {
      std::string line;
      EtaRingEnergyScale scale;
      while (getline(reffileD,line))
      {
        std::stringstream sline(line);
        sline >> scale.EtaRing
            >> scale.s
            >> scale.serr;
        EtaRingEtaScaleRefD.push_back(scale);
      }
      reffileD.close();
    }
  }

  // Get Original Mee Hist
  TH1D* h0 = (TH1D*)getTH1DOriginalMee(tree, "hMeeOrg", _nbins, maxevt, 1.0, _oddeven);
  h0->SetMarkerColor(2);
  h0->SetLineColor(2);
  
  // Get Mee Hist with Energy Reg. + EtaScale + Re-Calib
  TH1D* h5;
  if (method==7) 
  {
    h5 = (TH1D*)getTH1DMeeWithEtaScale(tree, extree, calibTable, EtaScaleRef, "hMeeEtaScale", _nbins, maxevt, method, 1.0);
  }
  else if (method==71) 
  {
    h5 = (TH1D*)getTH1DMeeWithEtaScaleABCD(tree, extree, calibTable, EtaScaleRefA, EtaScaleRefB, EtaScaleRefC, EtaScaleRefD, "hMeeRegElecEtaScaleReCalib", _nbins, maxevt, method, 1.0, _oddeven);
  }
  else if (method==72)
  {
    h5 = (TH1D*)getTH1DMeeWithEtaRingEtaScaleABCD(tree, extree, calibTable, 
                 EtaRingEtaScaleRefA, EtaRingEtaScaleRefB, EtaRingEtaScaleRefC, EtaRingEtaScaleRefD, 
                 "hMeeRegElecEtaScaleReCalib", _nbins, maxevt, method, 1.0, _oddeven, regVersion);
  }  
  h5->SetMarkerColor(4);
  h5->SetLineColor(4);
  // Get Mee Hist using Original Energy regression
  TH1D* h3 = (TH1D*)getTH1DMeeRegElec(tree, "hMeeRegElec", _nbins, maxevt, 1.0, _oddeven, regVersion);
  h3->SetMarkerColor(6);
  h3->SetLineColor(6);

  // Get Mee Hist using Energy Reg. + EtaScale
  TH1D* h4;
  if (method==7)
  {
    h4 = (TH1D*)getTH1DMeeRegV8ElecWithEtaScale(tree, EtaScaleRef, "hMeeRegV8ElecEtaScale", _nbins, maxevt, 1.0);
  }
  else if (method==71)
  {
    h4 = (TH1D*)getTH1DMeeRegElecWithEtaScaleABCD(tree, EtaScaleRefA, EtaScaleRefB, EtaScaleRefC, EtaScaleRefD, "hMeeRegElecEtaScale", _nbins, maxevt, 1.0, _oddeven, regVersion);
  }
  else if (method==72)
  {
    h4 = (TH1D*)getTH1DMeeRegElecWithEtaRingEtaScaleABCD(tree, 
                 EtaRingEtaScaleRefA, EtaRingEtaScaleRefB, EtaRingEtaScaleRefC, EtaRingEtaScaleRefD,
                 "hMeeRegElecEtaScale", _nbins, maxevt, 1.0, _oddeven, regVersion);
  }
  h4->SetMarkerColor(8);
  h4->SetLineColor(8);
 
  // Get Mee Hist
  TH1D* h1 = (TH1D*)getTH1DMee(tree, extree, calibTable, "hMee", _nbins, maxevt, 23, 1.0, _oddeven);
  h1->SetMarkerColor(9);
  h1->SetLineColor(9);
 
  // print
  //std::cout << "nEvents: " << h1->GetEntries() << std::endl;
  
  // write the hist to out root file
  fout->cd();
  h0->Write();
  //h01->Write();
  h1->Write();
  //h2->Write();
  h3->Write();
  h4->Write();
  h5->Write();

  // delete the chain no more need it
  tree->Delete();
  
  // close
  fout->Close();
  
  //
  return 0;
}
