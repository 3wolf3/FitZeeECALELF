#!/bin/sh

tag="_EEN"
sele="etaSCEle[1]<-2.2&&recoFlagsEle[1]==-1"

infile="root://eoscms//eos/cms/store/group/alca_ecalcalib/ecalelf/heli/ntuple/NtupleComb_DoubleElectron-ZSkim-RUN2012A-22Jan-v1.root"

outfile="root://eoscms//eos/cms/store/group/alca_ecalcalib/ecalelf/heli/ntuple/NtupleComb_DoubleElectron-ZSkim-RUN2012A-22Jan-v1_${tag}.root"


data

copyTree.exe $infile $outfile -1 $sele

date


