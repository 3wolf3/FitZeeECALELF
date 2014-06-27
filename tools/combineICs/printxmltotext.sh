#!/bin/sh

files="FT_R_53_V21/EcalIntercalibConstants_2012ABCD_offline_*.xml"

for file in $files;
do
  file1="`dirname $file`/`basename $file .xml`.txt";
  file2="`dirname $file`/`basename $file .xml`_Relative.txt";
 
  ./printxmltotext.exe $file $file1 1  
 
  cat $file1 | awk {'print $1" "$2" "$3" "$4'} > file1.txt
  cat $file2 | awk {'print $1" "$2" "$3" "$4'} > file2.txt
  echo "$file1: `diff file1.txt file2.txt`" 
 
done
