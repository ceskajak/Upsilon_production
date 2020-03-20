#!/bin/bash

mkdir runs
cd runs

echo run folder generated

for i in {1..9..1}
do
	mkdir "run00$i"
	cp ../src/Browser.so run00$i
	cp ../src/LHC_MB_all.run run00$i
	cp ../src/rivet_MinBias.sh rivet_MinBias00$i.sh
	line=`sed -n "${i}p" ../src/seeds_MB_all.dat`
	sed -i "s/test/$line/g" rivet_MinBias00$i.sh
	sed -i "s,cd .,cd /home/ceskajak/Ups/Herwig/rivet_MinBias_all_CR/runs/run00$i/,g" rivet_MinBias00$i.sh
	sed -i "s/error00/error00$i/g" rivet_MinBias00$i.sh
	mv rivet_MinBias00$i.sh run00$i

	echo run00$i generated
done

for i in {10..99..1}
do
	mkdir "run0$i"
	cp ../src/Browser.so run0$i
	cp ../src/LHC_MB_all.run run0$i
	cp ../src/rivet_MinBias.sh rivet_MinBias0$i.sh
	line=`sed -n "${i}p" ../src/seeds_MB_all.dat`
	sed -i "s/test/$line/g" rivet_MinBias0$i.sh
	sed -i "s,cd .,cd /home/ceskajak/Ups/Herwig/rivet_MinBias_all_CR/runs/run0$i/,g" rivet_MinBias0$i.sh
	sed -i "s/error00/error0$i/g" rivet_MinBias0$i.sh
	mv rivet_MinBias0$i.sh run0$i

	echo run0$i generated
done

for i in {100..250..1}
do
	mkdir "run$i"
	cp ../src/Browser.so run$i
	cp ../src/LHC_MB_all.run run$i
	cp ../src/rivet_MinBias.sh rivet_MinBias$i.sh
	line=`sed -n "${i}p" ../src/seeds_MB_all.dat`
	sed -i "s/test/$line/g" rivet_MinBias$i.sh
	sed -i "s,cd .,cd /home/ceskajak/Ups/Herwig/rivet_MinBias_all_CR/runs/run$i/,g" rivet_MinBias$i.sh
	sed -i "s/error00/error$i/g" rivet_MinBias$i.sh
	mv rivet_MinBias$i.sh run$i

	echo run$i generated
done
