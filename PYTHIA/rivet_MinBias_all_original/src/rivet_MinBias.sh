#!/bin/bash
#PBS -l nodes=1:ppn=1
#PBS -e ./error

cd /home/ceskajak/Ups/PYTHIA/rivet_MinBias_all_original/runs/RUN_NO
source /data2/vyuka/ssd/setup_ROOT6.08.06.sh
source /home/ceskajak/Herwig-7.2.0/bin/activate
source /home/ceskajak/scripts/setup_Pythia8244.sh
./RunPythia 
