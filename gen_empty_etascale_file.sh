#!/bin/sh

outfile=$1

if [ -e $outfile ]; then 
  rm $outfile
fi

for id in `seq -124 1 -1`;
do 
  echo "$id 1.0 0.000001 " >> $outfile
done
for id in `seq 1 1 124`;
do
  echo "$id 1.0 0.000001 " >> $outfile
done
