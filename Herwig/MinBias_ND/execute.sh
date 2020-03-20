#!/bin/bash

for i in {1..9..1}
do
	qsub -q $1 /home/ceskajak/Ups/Herwig/MinBias_ND/runs/run00$i/MinBias_ND00$i.sh
done

for i in {10..99..1}
do
	qsub -q $1 /home/ceskajak/Ups/Herwig/MinBias_ND/runs/run0$i/MinBias_ND0$i.sh
done

for i in {100..250..1}
do
	qsub -q $1 /home/ceskajak/Ups/Herwig/MinBias_ND/runs/run$i/MinBias_ND$i.sh
done
