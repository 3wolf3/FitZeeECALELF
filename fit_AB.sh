#!/bin/sh

MODE=78
ROOTFILEIN=ntuple_DYJets-Summer12-START53-HighEtaSkim-runDependent-Extra-V4-2012AB_10k.root
ROOTFILEOUT=fitzeescale_out_AB.root
METHOD=7
GAUSRESO=1.5;
REGVERSION=V8Elec
DEBUG=1
DOEVENODD=0
ETASCALEREF=""

./fitzeescale.exe ${MODE} \
               ${ROOTFILEIN} \
               ${ROOTFILEOUT} \
               0.9999 \
               ${METHOD} ${GAUSRESO} \
               ${REGVERSION} \
               ${DEBUG} \
               ${DOEVENODD} \
               ${ETASCALEREF}
