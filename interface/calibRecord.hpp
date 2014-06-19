// Author Hengne Li  UVa CERN 2014

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <map>

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

calibRecord CalibRecord(int idx, int ix, int iy, int iz, double c, double cerr, int fixed, int nfits)
{
  calibRecord record = {idx, ix, iy, iz, c, cerr, fixed, nfits};
  return record;
}

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

std::vector<calibRecord> getVectorCalibTableFromFile(const char* filename)
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


std::map<int, std::map<int, std::map<int, calibRecord> > > getMapCalibTableFromFile(const char* filename)
{
  std::map<int, std::map<int, std::map<int, calibRecord> > > mycalibTable;
  std::ifstream myfile(filename);
  std::string line;
  if (myfile.is_open())
  {
    mycalibTable.clear();
    while (getline(myfile,line))
    {
      calibRecord ic;
      std::stringstream sline(line);
      sline >> ic.idx
      >> ic.ix
      >> ic.iy
      >> ic.iz
      >> ic.c
      >> ic.cerr
      >> ic.fixed
      >> ic.nfits ;
      mycalibTable[ic.ix][ic.iy][ic.iz] = ic;
    }
    myfile.close();
  }

  return mycalibTable;
}




void printVectorCalibTableToFile(const std::vector<calibRecord>& calibTable, const char* filename = "calibTable_out.dat")
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


void printVectorCalibTableToScreen(const std::vector<calibRecord>& calibTable)
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


double getCalibConstFromVectorCalibTable(int ix, int iy, int iz, const std::vector<calibRecord>& calibTable)
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

double GetCalibConstFromMapCalibTable(const int& ix, const int& iy, const int& iz,
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




