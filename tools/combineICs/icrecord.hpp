// author Hengne Li @ CERN 2014
#include <vector>
#include <map>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <sstream>

// utilities for handling calibration constants following the standard format.

typedef struct
{
  int ix;  // cell ix
  int iy;  // cell iy
  int iz;  // cell iz
  double c; // calibration constant
  double cerr; // error of calibratioin constant
} icrecord;


std::vector<icrecord> getVectorICTableFromFile(const char* filename)
{
  std::vector<icrecord> ictable;
  std::ifstream myfile(filename);
  std::string line;
  if (myfile.is_open())
  {
    ictable.clear();
    while (getline(myfile,line))
    {
      icrecord calib;
      std::stringstream sline(line);
      sline >> calib.ix
             >> calib.iy
             >> calib.iz
             >> calib.c
             >> calib.cerr;
      ictable.push_back(calib);
    }
    myfile.close();
  }
  return ictable;
}

std::map<int, std::map<int, std::map<int, icrecord> > > getMapICTableFromFile(const char* filename)
{
  std::map<int, std::map<int, std::map<int, icrecord> > > ictable;
  std::ifstream myfile(filename);
  std::string line;
  if (myfile.is_open())
  {
    ictable.clear();
    while (getline(myfile,line))
    {
      icrecord ic;
      std::stringstream sline(line);
      sline >> ic.ix >> ic.iy >> ic.iz >> ic.c >> ic.cerr;
      ictable[ic.ix][ic.iy][ic.iz] = ic;
    }
    myfile.close();
  }

  return ictable;
}


