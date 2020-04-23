#!/bin/bash

for i in {0..9..1}
do
	qsub -q $1 /home/ceskajak/Ups/PYTHIA/MinBias_CMS_new/runs/run00$i/MinBias_all00$i.sh
done

for i in {10..99..1}
do
	qsub -q $1 /home/ceskajak/Ups/PYTHIA/MinBias_CMS_new/runs/run0$i/MinBias_all0$i.sh
done

