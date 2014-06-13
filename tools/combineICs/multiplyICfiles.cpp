
// Author Hengne Li @ CERN 2014

#include <icrecord.hpp>
#include <iostream>
#include <fstream>
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

  // read in first file to ictable
  std::vector<icrecord> inictable1 = getVectorICTableFromFile(argv[1]);

  // read in second file to ictable
  std::map<int, std::map<int, std::map<int, icrecord> > > inictable2 = getMapICTableFromFile(argv[2]);

  // output ic table
  std::vector<icrecord> outictable;

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
      oic.cerr = 9999.0;
    }

    outictable.push_back(oic);

  }

  // print to output file
  std::ofstream outfile(argv[3]);
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


