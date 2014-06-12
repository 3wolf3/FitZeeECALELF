// Authors: Hengne Li of UVa at CERN in 2014   

#include <rapidxml.hpp>
#include <rapidxml_print.hpp>
#include <rapidxml_utils.hpp>
#include <fstream>
#include <iostream>
#include <string>
#include <stdlib.h>

int main(int argc, char* argv[])
{
  if( argc<3 )
  {
    std::cout << argv[0] << " input_xml_ic_file output_text_ic_file" << std::endl;
    return 0;
  }

  bool doxml=false;

  rapidxml::file<> infile(argv[1]);
  rapidxml::xml_document<> input;
  input.parse<0>(infile.data());

  rapidxml::xml_node<> *node0 = input.first_node("EcalFloatCondObjectContainer");

  for (rapidxml::xml_node<> *node = node0->first_node("cell");
       node; node = node->next_sibling("cell"))
  {

    int ix,iy,iz;
    double ic;

    if (doxml) std::cout << "<cell" ;
    for (rapidxml::xml_attribute<> *attr = node->first_attribute();
         attr; attr = attr->next_attribute())
    {
      if (std::string(attr->name())==std::string("iEta")) { ix = atoi(attr->value()); iz = 0;}
      if (std::string(attr->name())==std::string("iPhi")) { iy = atoi(attr->value()); iz = 0;}
      if (std::string(attr->name())==std::string("ix")) { ix = atoi(attr->value());}
      if (std::string(attr->name())==std::string("iy")) { iy = atoi(attr->value());}
      if (std::string(attr->name())==std::string("zside")) { iz = atoi(attr->value());}

      if (doxml) std::cout << " " << attr->name() << "=\"" << attr->value() << "\"" ;
    }

    if (doxml) std::cout << ">\n" ;

    rapidxml::xml_node<> *val = node->first_node("Value");
    ic = atof(val->value()); 
    if (doxml) std::cout << "   <Value>" << val->value() << "</Value>\n" ;
    if (doxml) std::cout << "</cell>" << std::endl;

    if (!doxml) std::cout << ix << " " << iy << " " << iz << " " << ic << " " << " 0.0" << std::endl;

  }
  
}
