FitZeeECALELF
=============

A package to do the ECAL calibration using Zee events.


Initialize a working area and compare the package:

######
release=CMSSW_7_4_5
export SCRAM_ARCH=slc6_amd64_gcc491
alias cmsenv='eval `scramv1 runtime -sh`'
alias cmsrel='scramv1 project CMSSW'

scram project $release
cd $release/src
cmsenv

#git clone https://github.com/VirginiaCMS/FitZeeECALELF.git
git clone https://github.com/3wolf3/FitZeeECALELF
cd FitZeeECALELF
gmake all




