#!/bin/sh


for period in  2012AB 2012C 2012D;
do
  newICfile="ZeeHighEta/calibTable_out_HighEta_withEtaScale_MODE782_WithNewIC_Data_${period}_stdICs.dat" ;
  #newEtaScalefile="ZeeHighEta/fitzeescale_out_MODE782_WithNewIC_DataOvMC_${period}_stdICs.dat"
  newEtaScalefile="ZeeHighEta/fitzeescale_out_MODE782_WithNewIC_MC_${period}_stdIC.dat"

  Runs="";
  if [ ${period} == 2012AB ]; then 
    Runs="1 191691 191860 193622 193834 194223 194691 195396 195400 195963 ";
  elif [ ${period} == 2012C ]; then
    Runs="196532 198202 199011 199022 199804 200473 200601 201278 201825 202084 202530 ";
  elif [ ${period} == 2012D ]; then
    Runs="203768 205806 206066 207099 208296 ";
  fi
  echo "$period $Runs";

  for run in $Runs;
  do
    oldICfile="FT_R_53_V21/EcalIntercalibConstants_2012ABCD_offline_${run}_Relative.txt";
    prodICfile="`dirname $oldICfile`/`basename $oldICfile _Relative.txt`_ProdNewIC.txt";
    prodEtaScalefile="`dirname $oldICfile`/`basename $oldICfile _Relative.txt`_ProdNewIC_EtaScale.txt";
    prodICEtaScaleNormfile="`dirname $oldICfile`/`basename $oldICfile _Relative.txt`_ProdNewIC_EtaScaleNorm.txt";
    combIOVfile="`dirname $oldICfile`/`basename $oldICfile _Relative.txt`_NewICEtaScale.txt";
    combIOVXMLfile="`dirname $oldICfile`/`basename $oldICfile _Relative.txt`_NewICEtaScale.xml";
    

    #ls $oldICfile $newICfile $newEtaScalefile $prodICfile $prodEtaScalefile $prodICEtaScaleNormfile $combIOVfile

    # make product
    ./multiplyICfiles.exe ${oldICfile} ${newICfile} ${prodICfile} ;

    # calculate etascale
    ./calEtaScaleFromICfile.exe ${prodICfile}
  
    # apply etascale back to the prodICfile to normalize old etascale
    ./multiplyICfiles.exe ${prodICfile} ${prodEtaScalefile} ${prodICEtaScaleNormfile}

    # calculate etascale again to check 
    ./calEtaScaleFromICfile.exe ${prodICEtaScaleNormfile}

    # mutiply new etascale
    ./multiplyICfiles.exe ${prodICEtaScaleNormfile} ${newEtaScalefile} ${combIOVfile} 

    # check again the eta-scale, to see if it can reproduce the MC eta-scale
    ./calEtaScaleFromICfile.exe ${combIOVfile}

    # print to xml
    ./printxmltotext.exe ${combIOVfile} ${combIOVXMLfile} 2


  done
  
done





