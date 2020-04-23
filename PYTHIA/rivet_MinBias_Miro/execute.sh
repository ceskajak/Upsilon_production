#!/bin/bash

for i in {0..9..1}
do
	qsub -q $1 /home/ceskajak/Ups/PYTHIA/rivet_MinBias_Miro/runs/run00$i/rivet_MinBias00$i.sh
done

for i in {10..99..1}
do
	qsub -q $1 /home/ceskajak/Ups/PYTHIA/rivet_MinBias_Miro/runs/run0$i/rivet_MinBias0$i.sh
done

