#!/bin/bash
#PBS -l nodes=1:ppn=1
#PBS -e ./error

cd /home/ceskajak/Ups/PYTHIA/MinBias_all_CR1/runs/RUN_NO
source /data2/vyuka/ssd/setup_ROOT6.08.06.sh
source /data2/vyuka/ssd/setup_Pythia8240.sh
./RunPythia 
