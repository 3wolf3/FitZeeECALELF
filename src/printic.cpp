#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <stdio.h>

// Author Hengne Li @ UVa CERN 2014

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

////
int main(int argc, char* argv[])
{
  if (argc<3)
  {
    std::cout << argv[0] << "<HengneICFormat.dat> <CalibFormat.txt>"
              << std::endl;
    return 1;
  }

  char name[1000];

  const char* filename = argv[1];
  const char* filename_out = argv[2];
  
  std::cout << "Read Hengne's IC file : " << filename << std::endl;
  std::cout << "Write to standard IC file : " << filename_out << std::endl;

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
      bool found(false);
      for (int ii=0; ii<(int)mycalibTable.size(); ii++)
      {
        if (ix==mycalibTable.at(ii).ix && 
            iy==mycalibTable.at(ii).iy &&
            iz==mycalibTable.at(ii).iz)
        {
          found=true;
          c = mycalibTable.at(ii).c;
          cerr = mycalibTable.at(ii).cerr;
        }
      }

      if (!found) 
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


