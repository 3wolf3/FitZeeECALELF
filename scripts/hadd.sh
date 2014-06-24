#!/bin/sh


for Run in A B C D ;
do
  hadd NtupleComb_DoubleElectron-ZSkim-RUN2012${Run}-22Jan-v1.root Ntuple_DoubleElectron-ZSkim-RUN2012${Run}-22Jan-v1.root ExtraNtuple_DoubleElectron-ZSkim-RUN2012${Run}-22Jan-v1.root  &> "${Run}.log" &
done
