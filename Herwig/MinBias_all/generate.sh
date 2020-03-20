#!/bin/bash

mkdir runs
cd runs

echo run folder generated

for i in {1..9..1}
do
	mkdir "run00$i"
	cp ../src/Browser.so run00$i
	cp ../src/LHC_MB_all.run run00$i
	cp ../src/MinBias_all.sh MinBias_all00$i.sh
	line=`sed -n "${i}p" ../src/seeds_MB_all.dat`
	sed -i "s/test/$line/g" MinBias_all00$i.sh
	sed -i "s,cd .,cd /home/ceskajak/Ups/Herwig/MinBias_all/runs/run00$i/,g" MinBias_all00$i.sh
	sed -i "s/error00/error00$i/g" MinBias_all00$i.sh
	mv MinBias_all00$i.sh run00$i

	echo run00$i generated
done

for i in {10..99..1}
do
	mkdir "run0$i"
	cp ../src/Browser.so run0$i
	cp ../src/LHC_MB_all.run run0$i
	cp ../src/MinBias_all.sh MinBias_all0$i.sh
	line=`sed -n "${i}p" ../src/seeds_MB_all.dat`
	sed -i "s/test/$line/g" MinBias_all0$i.sh
	sed -i "s,cd .,cd /home/ceskajak/Ups/Herwig/MinBias_all/runs/run0$i/,g" MinBias_all0$i.sh
	sed -i "s/error00/error0$i/g" MinBias_all0$i.sh
	mv MinBias_all0$i.sh run0$i

	echo run0$i generated
done

for i in {100..250..1}
do
	mkdir "run$i"
	cp ../src/Browser.so run$i
	cp ../src/LHC_MB_all.run run$i
	cp ../src/MinBias_all.sh MinBias_all$i.sh
	line=`sed -n "${i}p" ../src/seeds_MB_all.dat`
	sed -i "s/test/$line/g" MinBias_all$i.sh
	sed -i "s,cd .,cd /home/ceskajak/Ups/Herwig/MinBias_all/runs/run$i/,g" MinBias_all$i.sh
	sed -i "s/error00/error$i/g" MinBias_all$i.sh
	mv MinBias_all$i.sh run$i

	echo run$i generated
done
