#!/bin/sh

NTIMES="Data_1"
REGVERSION="V8Elec"
MODE=78
METHOD=7
DOEVENODD="0"

ETASCALEREF="etascale_V8Elec_Mode74_Method7_A_1.dat"
QUEUE=cmscaf1nw
#cmscaf1nd
#cmscaf1nw
 
RUN="A"
INFILE="ntuple_DoubleElectron-HighEtaSkim-RUN2012A-22Jan-v1-Extra.root"
bsub -R "pool>20000" -q ${QUEUE} -J fitEtaScale_${REGVERSION}_${RUN}_${MODE}_${METHOD} dofitEtaScale.sh ${REGVERSION} ${RUN} ${MODE} ${METHOD} ${NTIMES} ${ETASCALEREF} ${DOEVENODD} ${INFILE}

RUN="B"
INFILE="ntuple_DoubleElectron-HighEtaSkim-RUN2012B-22Jan-v1-Extra.root"
bsub -R "pool>20000" -q ${QUEUE} -J fitEtaScale_${REGVERSION}_${RUN}_${MODE}_${METHOD} dofitEtaScale.sh ${REGVERSION} ${RUN} ${MODE} ${METHOD} ${NTIMES} ${ETASCALEREF} ${DOEVENODD} ${INFILE}

RUN="C"
INFILE="ntuple_DoubleElectron-HighEtaSkim-RUN2012C-22Jan-v1-Extra.root"
bsub -R "pool>20000" -q ${QUEUE} -J fitEtaScale_${REGVERSION}_${RUN}_${MODE}_${METHOD} dofitEtaScale.sh ${REGVERSION} ${RUN} ${MODE} ${METHOD} ${NTIMES} ${ETASCALEREF} ${DOEVENODD} ${INFILE}

RUN="D"
INFILE="ntuple_DoubleElectron-HighEtaSkim-RUN2012D-22Jan-v1-Extra.root"
bsub -R "pool>20000" -q ${QUEUE} -J fitEtaScale_${REGVERSION}_${RUN}_${MODE}_${METHOD} dofitEtaScale.sh ${REGVERSION} ${RUN} ${MODE} ${METHOD} ${NTIMES} ${ETASCALEREF} ${DOEVENODD} ${INFILE}

#RUN="AB"
#INFILE="ntuple_DYJets-Summer12-START53-HighEtaSkim-runDependent-Extra-V4-2012AB.root"
#bsub -R "pool>20000" -q ${QUEUE} -J fitEtaScale_${REGVERSION}_${RUN}_${MODE}_${METHOD} dofitEtaScale.sh ${REGVERSION} ${RUN} ${MODE} ${METHOD} ${NTIMES} ${ETASCALEREF} ${DOEVENODD} ${INFILE}

#RUN="C"
#INFILE="ntuple_DYJets-Summer12-START53-HighEtaSkim-runDependent-Extra-V4-2012C.root"
#bsub -R "pool>20000" -q ${QUEUE} -J fitEtaScale_${REGVERSION}_${RUN}_${MODE}_${METHOD} dofitEtaScale.sh ${REGVERSION} ${RUN} ${MODE} ${METHOD} ${NTIMES} ${ETASCALEREF} ${DOEVENODD} ${INFILE}

#RUN="D"
#INFILE="ntuple_DYJets-Summer12-START53-HighEtaSkim-runDependent-Extra-V4-2012D.root"
#bsub -R "pool>20000" -q ${QUEUE} -J fitEtaScale_${REGVERSION}_${RUN}_${MODE}_${METHOD} dofitEtaScale.sh ${REGVERSION} ${RUN} ${MODE} ${METHOD} ${NTIMES} ${ETASCALEREF} ${DOEVENODD} ${INFILE}



