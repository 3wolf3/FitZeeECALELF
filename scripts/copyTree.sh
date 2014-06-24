#!/bin/sh

tag="EEN"
sele="etaSCEle[1]<-2.2&&recoFlagsEle[1]==-1"

date
infile="NtupleComb_DoubleElectron-ShervinZSkimPath-RUN2012A-22Jan-v1.root"
outfile="NtupleComb_DoubleElectron-ShervinZSkimPath-RUN2012A-22Jan-v1_${tag}.root"
copyTree.exe $infile $outfile -1 $sele &> ${outfile}.log &
date

date
infile="NtupleComb_DoubleElectron-ShervinZSkimPath-RUN2012B-22Jan-v1.root"
outfile="NtupleComb_DoubleElectron-ShervinZSkimPath-RUN2012B-22Jan-v1_${tag}.root"
copyTree.exe $infile $outfile -1 $sele &> ${outfile}.log &
date

date
infile="NtupleComb_DoubleElectron-ShervinZSkimPath-RUN2012C-22Jan-v1.root"
outfile="NtupleComb_DoubleElectron-ShervinZSkimPath-RUN2012C-22Jan-v1_${tag}.root"
copyTree.exe $infile $outfile -1 $sele &> ${outfile}.log &
date

date
infile="NtupleComb_DoubleElectron-ShervinZSkimPath-RUN2012D-22Jan-v1.root"
outfile="NtupleComb_DoubleElectron-ShervinZSkimPath-RUN2012D-22Jan-v1_${tag}.root"
copyTree.exe $infile $outfile -1 $sele &> ${outfile}.log &
date

tag="EEP"
sele="etaSCEle[1]>2.2&&recoFlagsEle[1]==-1"

date
infile="NtupleComb_DoubleElectron-ShervinZSkimPath-RUN2012A-22Jan-v1.root"
outfile="NtupleComb_DoubleElectron-ShervinZSkimPath-RUN2012A-22Jan-v1_${tag}.root"
copyTree.exe $infile $outfile -1 $sele &> ${outfile}.log &
date

date
infile="NtupleComb_DoubleElectron-ShervinZSkimPath-RUN2012B-22Jan-v1.root"
outfile="NtupleComb_DoubleElectron-ShervinZSkimPath-RUN2012B-22Jan-v1_${tag}.root"
copyTree.exe $infile $outfile -1 $sele &> ${outfile}.log &
date

date
infile="NtupleComb_DoubleElectron-ShervinZSkimPath-RUN2012C-22Jan-v1.root"
outfile="NtupleComb_DoubleElectron-ShervinZSkimPath-RUN2012C-22Jan-v1_${tag}.root"
copyTree.exe $infile $outfile -1 $sele &> ${outfile}.log &
date

date
infile="NtupleComb_DoubleElectron-ShervinZSkimPath-RUN2012D-22Jan-v1.root"
outfile="NtupleComb_DoubleElectron-ShervinZSkimPath-RUN2012D-22Jan-v1_${tag}.root"
copyTree.exe $infile $outfile -1 $sele &> ${outfile}.log &
date


