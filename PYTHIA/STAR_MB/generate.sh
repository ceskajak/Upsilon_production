#!/bin/bash

mkdir runs
cd runs

echo run folder generated

for i in {0..9..1}
do
	mkdir "run00$i"
	cp ../src/rivet_MinBias.cmnd run00$i
	cp ../src/rivet_MinBias.cc run00$i
	cp ../src/rivet_MinBias.sh run00$i/rivet_MinBias00$i.sh
	cd run00$i
	sed -i "s/rivet_MinBias.root/rivet_MinBias00$i.root/g" rivet_MinBias.cc
	sed -i "s/output.yoda/pythia00$i.yoda/g" rivet_MinBias.cc
	sed -i "s/error/error00$i/g" rivet_MinBias00$i.sh
	sed -i "s/RUN_NO/run00$i/g" rivet_MinBias00$i.sh
	/home/ceskajak/scripts/rivet_compile.sh
	cd ..
	
	echo run00$i generated
done

for i in {10..99..1}
do
	mkdir "run0$i"
	cp ../src/rivet_MinBias.cmnd run0$i
	cp ../src/rivet_MinBias.cc run0$i
	cp ../src/rivet_MinBias.sh run0$i/rivet_MinBias0$i.sh
	cd run0$i
	sed -i "s/rivet_MinBias.root/rivet_MinBias0$i.root/g" rivet_MinBias.cc
	sed -i "s/output.yoda/pythia0$i.yoda/g" rivet_MinBias.cc
	sed -i "s/error/error0$i/g" rivet_MinBias0$i.sh
	sed -i "s/RUN_NO/run0$i/g" rivet_MinBias0$i.sh
	/home/ceskajak/scripts/rivet_compile.sh
	cd ..
	
	echo run0$i generated
done
