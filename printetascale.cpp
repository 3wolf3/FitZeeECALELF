// Author Hengne Li  2014
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <stdio.h>

typedef struct
{
  int EtaRing;
  double s; // scale
  double serr; // error of scale
} EtaRingEnergyScale;

// EE Eta Ring
std::string _defEtaRingEE = "eering.dat";
int _eering_eta[150][150];

void initEEEtaRingTable();
int GetEtaRing(int ix, int iy, int iz);

////
int main(int argc, char* argv[])
{
  if (argc<3)
  {
    std::cout << argv[0] << " <etaScale.dat> <etaScaleCalibFormat.txt>"
              << std::endl;
    return 1;
  }

  char name[1000];

  const char* filename = argv[1];
  const char* filename_out = argv[2];
  
  std::cout << "Read file : " << filename << std::endl;
  std::cout << "Write eta scale file to : " << filename_out << std::endl;


  // init eering data
  initEEEtaRingTable();

  // define eta scale vector
  std::vector<EtaRingEnergyScale> EtaRingEtaScaleRef;

  // read in input eta scale file
  std::ifstream myfile;
  myfile.open(filename);
  if (myfile.is_open())
  {
    std::string line;
    EtaRingEnergyScale scale;
    while (getline(myfile,line))
    {
      std::stringstream sline(line);
      sline >> scale.EtaRing
          >> scale.s
          >> scale.serr;
      EtaRingEtaScaleRef.push_back(scale);
    }
    myfile.close();
  }
 
  // init an empty IC table
  std::ifstream emptyTable("emptyXtable.dat");
  // print all crystals
  std::ofstream myfile_out(filename_out);


  if (emptyTable.is_open()&&myfile_out.is_open())
  {
    int ix, iy, iz;
    double c, cerr;
    int nlines=0;
    std::string line;
    while (getline(emptyTable,line))
    {
      std::stringstream sline(line);
      sline >> ix >> iy >> iz
      >> c >> cerr;
      nlines++;
      int EtaRing = GetEtaRing(ix, iy, iz);
      if (EtaRing>-500)
      { 
        for (int ii=0; ii<(int)EtaRingEtaScaleRef.size(); ii++)
        {
          if (EtaRing==EtaRingEtaScaleRef.at(ii).EtaRing)
          {
            c = EtaRingEtaScaleRef.at(ii).s;
            cerr = EtaRingEtaScaleRef.at(ii).serr;
          }
        }
      }
      else 
      {
        c = -1.0;
        cerr = 999.0;
      }
      
      myfile_out << ix << " " << iy << " " << iz << " "
          << c << " " << cerr << std::endl;
    }
    emptyTable.close();
    myfile_out.close();
    std::cout << "N ICs = " << nlines << std::endl;
  }


  
  return 0;

}


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


