###################
# CMS Environment #
###################
echo "Running cmsenv"
cmsenv
echo "Loading CMSSW"
module use -a /afs/desy.de/group/cms/modulefiles/
module load cmssw

#########
# CLHEP #
#########
echo "Sourcing CLHEP"
CLHEPINITISH=/cvmfs/cms.cern.ch/slc6_amd64_gcc530/external/clhep/2.3.4.2/etc/profile.d/init.sh
source ${CLHEPINITISH}
export CLHEP_INCLUDE=/cvmfs/cms.cern.ch/slc6_amd64_gcc530/external/clhep/2.3.4.2/include/
export CLHEP_LIB=/cvmfs/cms.cern.ch/slc6_amd64_gcc530/external/clhep/2.3.4.2/lib

#########
# BOOST #
#########
export BOOST_INCLUDE=/usr/include
export BOOST_LIB=/usr/lib64

########
# ROOT #
########
if ! command -v root &> /dev/null; then
  echo "ERROR -- CERN ROOT is not available; please install it before using SampleProduction (see README)"
  return 1
fi

THISROOTSH=${ROOTSYS}/bin/thisroot.sh
sleep 1
echo "Sourcing ROOT"
source ${THISROOTSH}

####################
# SampleProduction #
####################
export SAMPLEPRODUCTION_BASE_DIR=$(pwd)
export SAMPLEPRODUCTION_OUT_DIR=$(pwd)/output
export SAMPLEPRODUCTION_DATA_DIR=$(pwd)/data
export SAMPLEPRODUCTION_JOBSUB_DIR=$(pwd)/jobsub

##########
# System #
##########
export PATH=$SAMPLEPRODUCTION_BASE_DIR/bin:$PATH 
export LD_LIBRARY_PATH=${CLHEP_LIB}:$LD_LIBRARY_PATH 

echo "==== DONE ===="
