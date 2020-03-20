#!/bin/bash

for i in {1..9..1}
do
	qsub -q $1 /home/ceskajak/Ups/Herwig/rivet_MinBias_all_CR/runs/run00$i/rivet_MinBias00$i.sh
done

for i in {10..99..1}
do
	qsub -q $1 /home/ceskajak/Ups/Herwig/rivet_MinBias_all_CR/runs/run0$i/rivet_MinBias0$i.sh
done

for i in {100..250..1}
do
	qsub -q $1 /home/ceskajak/Ups/Herwig/rivet_MinBias_all_CR/runs/run$i/rivet_MinBias$i.sh
done
