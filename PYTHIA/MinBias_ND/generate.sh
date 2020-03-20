#!/bin/bash

mkdir runs
cd runs

echo run folder generated

for i in {0..9..1}
do
	mkdir "run00$i"
	cp ../src/MinBias_ND.cmnd run00$i
	cp ../src/MinBias_ND.cc run00$i
	cp ../src/MinBias_ND.sh run00$i/MinBias_ND00$i.sh
	cd run00$i
	sed -i "s/MinBias_ND.root/MinBias_ND00$i.root/g" MinBias_ND.cc
	sed -i "s/error/error00$i/g" MinBias_ND00$i.sh
	sed -i "s/RUN_NO/run00$i/g" MinBias_ND00$i.sh
	/home/ceskajak/scripts/compile.sh
	cd ..
	
	echo run00$i generated
done

for i in {10..99..1}
do
	mkdir "run0$i"
	cp ../src/MinBias_ND.cmnd run0$i
	cp ../src/MinBias_ND.cc run0$i
	cp ../src/MinBias_ND.sh run0$i/MinBias_ND0$i.sh
	cd run0$i
	sed -i "s/MinBias_ND.root/MinBias_ND0$i.root/g" MinBias_ND.cc
	sed -i "s/error/error0$i/g" MinBias_ND0$i.sh
	sed -i "s/RUN_NO/run0$i/g" MinBias_ND0$i.sh
	/home/ceskajak/scripts/compile.sh
	cd ..
	
	echo run0$i generated
done
