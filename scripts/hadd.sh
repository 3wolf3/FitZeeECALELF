#!/bin/sh


#for Run in A B C D ;
#do
#  hadd NtupleComb_DoubleElectron-ZSkim-RUN2012${Run}-22Jan-v1.root Ntuple_DoubleElectron-ZSkim-RUN2012${Run}-22Jan-v1.root ExtraNtuple_DoubleElectron-ZSkim-RUN2012${Run}-22Jan-v1.root  &> "${Run}.log" &
#done

hadd NtupleComb_DoubleElectron-ShervinZSkimPath-RUN2012A-22Jan-v1.root \
     DoubleElectron-ZSkimPath-RUN2012A-22Jan-v1-190645-193621.root \
     extraCalibTree-DoubleElectron-ZSkimPath-RUN2012A-22Jan-v1-190645-193621.root

hadd NtupleComb_DoubleElectron-ShervinZSkimPath-RUN2012B-22Jan-v1.root \
     DoubleElectron-ZSkimPath-RUN2012B-22Jan-v1-193834-196531.root \
     extraCalibTree-DoubleElectron-ZSkimPath-RUN2012B-22Jan-v1-193834-196531.root

hadd NtupleComb_DoubleElectron-ShervinZSkimPath-RUN2012C-22Jan-v1.root \
     DoubleElectron-ZSkimPath-RUN2012C-22Jan-v1-198022-203742.root \
     extraCalibTree-DoubleElectron-ZSkimPath-RUN2012C-22Jan-v1-198022-203742.root

hadd NtupleComb_DoubleElectron-ShervinZSkimPath-RUN2012D-22Jan-v1.root \
     DoubleElectron-ZSkimPath-RUN2012D-22Jan-v1-203777-208686.root \
     extraCalibTree-DoubleElectron-ZSkimPath-RUN2012C-22Jan-v1-198022-203742.root


