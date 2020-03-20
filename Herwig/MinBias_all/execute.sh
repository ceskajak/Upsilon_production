#!/bin/bash

for i in {1..9..1}
do
	qsub -q $1 /home/ceskajak/Ups/Herwig/MinBias_all/runs/run00$i/MinBias_all00$i.sh
done

for i in {10..99..1}
do
	qsub -q $1 /home/ceskajak/Ups/Herwig/MinBias_all/runs/run0$i/MinBias_all0$i.sh
done

for i in {100..250..1}
do
	qsub -q $1 /home/ceskajak/Ups/Herwig/MinBias_all/runs/run$i/MinBias_all$i.sh
done
