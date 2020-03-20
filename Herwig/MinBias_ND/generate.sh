#!/bin/bash

mkdir runs
cd runs

echo run folder generated

for i in {1..9..1}
do
	mkdir "run00$i"
	cp ../src/Browser.so run00$i
	cp ../src/LHC_MB_ND.run run00$i
	cp ../src/MinBias_ND.sh MinBias_ND00$i.sh
	line=`sed -n "${i}p" ../src/seeds_MB_ND.dat`
	sed -i "s/test/$line/g" MinBias_ND00$i.sh
	sed -i "s,cd .,cd /home/ceskajak/Ups/Herwig/MinBias_ND/runs/run00$i/,g" MinBias_ND00$i.sh
	sed -i "s/error00/error00$i/g" MinBias_ND00$i.sh
	mv MinBias_ND00$i.sh run00$i

	echo run00$i generated
done

for i in {10..99..1}
do
	mkdir "run0$i"
	cp ../src/Browser.so run0$i
	cp ../src/LHC_MB_ND.run run0$i
	cp ../src/MinBias_ND.sh MinBias_ND0$i.sh
	line=`sed -n "${i}p" ../src/seeds_MB_ND.dat`
	sed -i "s/test/$line/g" MinBias_ND0$i.sh
	sed -i "s,cd .,cd /home/ceskajak/Ups/Herwig/MinBias_ND/runs/run0$i/,g" MinBias_ND0$i.sh
	sed -i "s/error00/error0$i/g" MinBias_ND0$i.sh
	mv MinBias_ND0$i.sh run0$i

	echo run0$i generated
done

for i in {100..250..1}
do
	mkdir "run$i"
	cp ../src/Browser.so run$i
	cp ../src/LHC_MB_ND.run run$i
	cp ../src/MinBias_ND.sh MinBias_ND$i.sh
	line=`sed -n "${i}p" ../src/seeds_MB_ND.dat`
	sed -i "s/test/$line/g" MinBias_ND$i.sh
	sed -i "s,cd .,cd /home/ceskajak/Ups/Herwig/MinBias_ND/runs/run$i/,g" MinBias_ND$i.sh
	sed -i "s/error00/error$i/g" MinBias_ND$i.sh
	mv MinBias_ND$i.sh run$i

	echo run$i generated
done
