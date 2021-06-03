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
echo "Sourcing thisroot.sh"
source ${THISROOTSH}

####################
# SampleProduction #
####################
export SAMPLEPRODUCTION_BASE_DIR=$(pwd)
export SAMPLEPRODUCTION_OUT_DIR=$(pwd)/output
export SAMPLEPRODUCTION_DATA_DIR=$(pwd)/data

##########
# System #
##########
export PATH=$SAMPLEPRODUCTION_BASE_DIR/bin:$PATH 
export LD_LIBRARY_PATH=:$LD_LIBRARY_PATH 

###################
# CMS Environment #
###################
echo "Running cmsenv"
cmsenv
echo "Loading CMSSW"
module use -a /afs/desy.de/group/cms/modulefiles/
module load cmssw

echo "==== DONE ===="
