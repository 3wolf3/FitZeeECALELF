{
  // EE Eta Ring
  std::string _defEtaRingEE = "eering.dat";
  int _eering_eta[150][150];

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

  // print
  std::cout << "{ \n";
  for (int i1=0; i1<150; i1++)
  {
    std::cout << "  {" ;
    for (int i2=0; i2<150; i2++)
    {
      if (i2!=0) std::cout << ",";
      std::cout << _eering_eta[i1][i2] ;
    }
    std::cout << "}," << std::endl;
  }
  std::cout << "};" << std::endl;


}
