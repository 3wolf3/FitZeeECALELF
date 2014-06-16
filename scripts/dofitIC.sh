#!/bin/sh


list="
config/fitzee.config.MC_V8Elec_Mode781_Method7_AB_MC_3_EEN 
config/fitzee.config.MC_V8Elec_Mode781_Method7_AB_MC_3_EEP 
config/fitzee.config.MC_V8Elec_Mode781_Method7_C_MC_3_EEN 
config/fitzee.config.MC_V8Elec_Mode781_Method7_C_MC_3_EEP 
config/fitzee.config.MC_V8Elec_Mode781_Method7_D_MC_3_EEN 
config/fitzee.config.MC_V8Elec_Mode781_Method7_D_MC_3_EEP 
"

for config in $list;
do
  echo "fit $confg" 
  ./fitzee.exe $config &> $config.log 
done 
