PROXY="/nfs/dust/cms/user/yotarid/proxies/x509up_u35340"

export SCRAM_ARCH=slc6_amd64_gcc530
export CPATH=$CPATH:$SAMPLEPRODUCTION_JOBSUB_DIR

export X509_USER_PROXY=$PROXY

source /cvmfs/cms.cern.ch/cmsset_default.sh

eval `scramv1 runtime -sh`

$SAMPLEPRODUCTION_BASE_DIR/bin/SelectCustomEvent -f $SAMPLEPRODUCTION_BASE_DIR/settings/Selection_TauPair.xml -e @ERA@ -p @PROCESS@ -c @CHANNEL@ -x @EXTENSION@