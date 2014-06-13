// Authors: Hengne Li of UVa at CERN in 2014   
// print xml IC file to text file
#include <rapidxml.hpp>
#include <rapidxml_print.hpp>
#include <rapidxml_utils.hpp>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <stdlib.h>

int main(int argc, char* argv[])
{
  if( argc<3 )
  {
    std::cout << argv[0] << " input_ic_file output_ic_file option\n"
              << "       option: 1: xml to text; 2: text to xml " << std::endl;
    return 0;
  }

  int option = atoi(argv[3]);

  if (option==1) // xml to text
  {
    rapidxml::file<> infile(argv[1]);
    rapidxml::xml_document<> input;
    input.parse<0>(infile.data());

    std::ofstream outfile(argv[2]);

    rapidxml::xml_node<> *node0 = input.first_node("EcalFloatCondObjectContainer");

    for (rapidxml::xml_node<> *node = node0->first_node("cell");
         node; node = node->next_sibling("cell"))
    {
      int ix,iy,iz;
      double ic;
      for (rapidxml::xml_attribute<> *attr = node->first_attribute();
           attr; attr = attr->next_attribute())
      {
        if (std::string(attr->name())==std::string("iEta")) { ix = atoi(attr->value()); iz = 0;}
        if (std::string(attr->name())==std::string("iPhi")) { iy = atoi(attr->value()); iz = 0;}
        if (std::string(attr->name())==std::string("ix")) { ix = atoi(attr->value());}
        if (std::string(attr->name())==std::string("iy")) { iy = atoi(attr->value());}
        if (std::string(attr->name())==std::string("zside")) { iz = atoi(attr->value());}
      }

      rapidxml::xml_node<> *val = node->first_node("Value");
      ic = atof(val->value());

      if (outfile.is_open()) 
      {
        outfile << ix << " " << iy << " " << iz << " " << ic << " " << " 0.0" << std::endl;
      }

    }

    outfile.close();

  }
  else if (option==2) // text to xml 
  {
    std::ifstream infile(argv[1]);
    std::ofstream outfile(argv[2]);
    std::string line;

    if (outfile.is_open())
    {
      outfile << "<EcalFloatCondObjectContainer>" << std::endl;

      outfile << "  <EcalCondHeader>" << std::endl;
      outfile << "    <method></method>" << std::endl;
      outfile << "    <version></version>" << std::endl;
      outfile << "    <datasource></datasource>" << std::endl;
      outfile << "    <since>0</since>" << std::endl;
      outfile << "    <tag></tag>" << std::endl;
      outfile << "    <date></date>" << std::endl;
      outfile << "  </EcalCondHeader>" << std::endl;

    }

    int ix,iy,iz;
    double ic, icerr;

    if (infile.is_open()&&outfile.is_open())
    {
      while (getline(infile,line))
      {
        std::stringstream sline(line);
        sline >> ix >> iy >> iz >> ic >> icerr;

        outfile << "  <cell ";
        if (iz==0) 
        {
          outfile << "iEta=\"" << ix << "\" iPhi=\"" << iy << "\">" << std::endl;
        }
        else // iz==1 or -1
        {
          outfile << "ix=\"" << ix << "\" iy=\"" << iy << "\" zside=\"" << iz << "\">" << std::endl;
        }
        
        outfile << "    <Value>" << ic << "</Value>" << std::endl;
        outfile << "  </cell>" << std::endl;

      } // while getline

      outfile << "</EcalFloatCondObjectContainer>" << std::endl;

      infile.close();
      outfile.close();

    }// if (infile open, outfile open)   

  } //else if txt to xml
  else 
  {
    std::cout << "Error no such a option " << option << std::endl;
  }

  return 0;

}
