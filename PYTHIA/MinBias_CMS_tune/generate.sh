#!/bin/bash

mkdir runs
cd runs

echo run folder generated

for i in {0..9..1}
do
	mkdir "run00$i"
	cp ../src/MinBias_all.cmnd run00$i
	cp ../src/MinBias_all.cc run00$i
	cp ../src/MinBias_all.sh run00$i/MinBias_all00$i.sh
	cd run00$i
	sed -i "s/MinBias_all.root/MinBias_all00$i.root/g" MinBias_all.cc
	sed -i "s/error/error00$i/g" MinBias_all00$i.sh
	sed -i "s/RUN_NO/run00$i/g" MinBias_all00$i.sh
	/home/ceskajak/scripts/compile.sh
	cd ..
	
	echo run00$i generated
done

for i in {10..99..1}
do
	mkdir "run0$i"
	cp ../src/MinBias_all.cmnd run0$i
	cp ../src/MinBias_all.cc run0$i
	cp ../src/MinBias_all.sh run0$i/MinBias_all0$i.sh
	cd run0$i
	sed -i "s/MinBias_all.root/MinBias_all0$i.root/g" MinBias_all.cc
	sed -i "s/error/error0$i/g" MinBias_all0$i.sh
	sed -i "s/RUN_NO/run0$i/g" MinBias_all0$i.sh
	/home/ceskajak/scripts/compile.sh
	cd ..
	
	echo run0$i generated
done
