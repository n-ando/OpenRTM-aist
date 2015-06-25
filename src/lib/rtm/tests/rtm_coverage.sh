#!/bin/sh
#

Tests="Tests"

COVERAGE_DIR=../Coverage

if [ -e $COVERAGE_DIR ]; then
    rm -rf $COVERAGE_DIR
fi

echo "--------mkdir ../Coverage--------"
mkdir $COVERAGE_DIR

makeOKDirCoverage2rtm () {
    for dir in `ls -l | awk '$1 ~ /d/{print $9}'`; do
	cd $dir
	pwd
	runCmd=$dir$Tests
	if [ -e ./Coverage ]; then
	    cat ./Coverage/$runCmd.info >> ../../Coverage/allcoverage.info
	fi
	cd ../
	pwd
    done
    cd ../Coverage
    pwd
    echo "--------genhtml -o . allcoverage.info--------"
    genhtml -o . allcoverage.info
}

makeOKDirCoverage2rtm
