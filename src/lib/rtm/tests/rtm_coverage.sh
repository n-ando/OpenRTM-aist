#!/bin/sh

compileOKDir_list="CORBA_IORUtil ConnectorListener CorbaConsumer NVUtil NumberingPolicy ObjectManager OutPortProvider PeriodicECSharedComposite RTCUtil RingBuffer SdoOrganization SdoService StateMachine"

#compileOKDir_list="CORBA_IORUtil"

Tests="Tests"

#echo "--------cd src/lib/rtm/tests--------"
#cd OpenRTM-aist/src/lib/rtm/tests

COVERAGE_DIR=../Coverage

if [ -e $COVERAGE_DIR ]; then
    rm -rf $COVERAGE_DIR
fi

echo "--------mkdir ../Coverage--------"
mkdir $COVERAGE_DIR

makeOKDirCoverage2rtm () {
    for dir in $*; do
	cd $dir
	pwd
	runCmd=$dir$Tests
	cat ./Coverage/$runCmd.info >> ../../Coverage/allcoverage.info
	cd ../
	pwd
    done
    cd ../Coverage
    pwd
    echo "--------genhtml -o . allcoverage.info--------"
    genhtml -o . allcoverage.info
}

makeOKDirCoverage2rtm $compileOKDir_list


