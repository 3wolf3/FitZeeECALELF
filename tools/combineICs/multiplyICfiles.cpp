
// Author Hengne Li @ CERN 2014

#include <icrecord.hpp>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <stdio.h>
#include <cmath>

// make product of two IC files

////
int main(int argc, char* argv[])
{
  if (argc<4)
  {
    std::cout << argv[0] << "<icfile1.txt> <icfile2.txt> <output_icfile.txt>"
              << std::endl;
    return 1;
  }

  char name[1000];

  std::cout << "IC file1 : " << argv[1] << std::endl;
  std::cout << "IC file2 : " << argv[2] << std::endl;
  std::cout << "Product  : " << argv[3] << std::endl;

  std::ifstream infile1(argv[1]);
  std::ifstream infile2(argv[2]);
  std::ofstream outfile(argv[3]);

  std::vector<icrecord> inictable1;
  std::map<int, std::map<int, std::map<int, icrecord> > > inictable2;
  std::vector<icrecord> outictable;

  std::string line;
  
  // read in first file
  if (infile1.is_open())
  {
    inictable1.clear();
    while (getline(infile1,line))
    {
      icrecord ic;
      std::stringstream sline(line);
      sline >> ic.ix >> ic.iy >> ic.iz >> ic.c >> ic.cerr;
      inictable1.push_back(ic);
    }
    infile1.close();
  }

  // read in second file
  if (infile2.is_open())
  {
    inictable2.clear();
    while (getline(infile2,line))
    {
      icrecord ic;
      std::stringstream sline(line);
      sline >> ic.ix >> ic.iy >> ic.iz >> ic.c >> ic.cerr;
      inictable2[ic.ix][ic.iy][ic.iz] = ic;
    }
    infile2.close();
  }
 
  // check if the two ic
  // make product
  for (int i=0; i<(int)inictable1.size(); i++)
  {
    icrecord ic1 = inictable1.at(i);
    icrecord ic2 = inictable2[ic1.ix][ic1.iy][ic1.iz];
    icrecord oic;

    oic.ix = ic1.ix; oic.iy = ic1.iy; oic.iz = ic1.iz;

    if (ic1.c>=0&&ic2.c>=0)
    {
      oic.c = ic1.c * ic2.c;
      oic.cerr = sqrt(ic2.c*ic2.c*ic1.cerr*ic1.cerr+ic1.c*ic1.c*ic2.cerr*ic2.cerr);
    }
    else if (ic1.c>=0&&ic2.c<0)
    {
      oic.c = ic1.c;
      oic.cerr = ic1.cerr;
    }
    else if (ic1.c<0&&ic2.c>=0)
    {
      oic.c = ic2.c;
      oic.cerr = ic2.cerr;
    }
    else
    {
      oic.c = 1.0;
      oic.cerr = 0.0;
    }

    outictable.push_back(oic);

  }

  // print to output file
  if (outfile.is_open())
  {
    for (int i=0; i<(int)outictable.size(); i++)
    {
      icrecord ic = outictable.at(i);
      outfile << ic.ix << " " << ic.iy << " " << ic.iz << " " << ic.c << " " << ic.cerr << std::endl;
    }
    outfile.close();
  }

  return 0;

}


