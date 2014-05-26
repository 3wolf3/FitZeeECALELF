#!/bin/sh

g++ -o calculateEtaScaleFromICs.exe calculateEtaScaleFromICs.cc \
      -pthread -m64 \
      -I${ROOTSYS}/include \
      -I./  -L${ROOTSYS}/lib \
      -lCore -lCint -lRIO -lNet -lHist -lGraf -lGraf3d \
      -lGpad -lTree -lRint -lPostscript -lMatrix -lPhysics \
      -lMathCore -lThread -lMinuit -lMinuit2 -lpthread \
      -lTreePlayer \
      -Wl,-rpath,${ROOTSYS}/lib -lm -ldl

./calculateEtaScaleFromICs.exe
