#!/bin/sh


INPUTFILE="ntuple_DYJets-Summer12-START53-HighEtaSkim-runDependent-Extra-V4-2012ABC-EEN.root"
REFFILE="calibTable_out_HighEta_ABC_MC_EEN.dat"
OUTPUTFILE="drawMee_out_ABC_MC_EEN.root"
METHOD=72
EVENODD=0
SCALE="etascale_ABC_mc.dat;etascale_ABC_mc.dat;etascale_ABC_mc.dat;etascale_D_mc.dat"
REG="RegV8"
 
./drawMee.exe \
  $INPUTFILE \
  $REFFILE \
  $OUTPUTFILE \
  -1 \
  $METHOD \
  1.0 \
  $EVENODD \
  $SCALE \
  $REG 

 



