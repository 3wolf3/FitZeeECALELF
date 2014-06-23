#!/bin/sh

tag="EEP"
sele="etaSCEle[1]>2.2&&recoFlagsEle[1]==-1"

#infile="root://eoscms//eos/cms/store/group/alca_ecalcalib/ecalelf/heli/ntuple/NtupleComb_DoubleElectron-ZSkim-RUN2012B-22Jan-v1.root"
infile="NtupleComb_DoubleElectron-ZSkim-RUN2012C-22Jan-v1.root"
#outfile="root://eoscms//eos/cms/store/group/alca_ecalcalib/ecalelf/heli/ntuple/NtupleComb_DoubleElectron-ZSkim-RUN2012B-22Jan-v1_${tag}.root"
outfile="NtupleComb_DoubleElectron-ZSkim-RUN2012C-22Jan-v1_${tag}.root"

date

copyTree.exe $infile $outfile -1 $sele

date


