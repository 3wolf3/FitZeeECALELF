#!/bin/sh

logfile=$1
outfile=$2

grep "EtaBin\[" ${logfile} | awk {'print $2" "$4" "$6'} |sed "s/(//g" | sed "s/)//g" | sed "s/<Eta</ /g" > ${outfile}
