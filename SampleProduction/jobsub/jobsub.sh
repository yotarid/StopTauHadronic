DIR="/nfs/dust/cms/user/yotarid/SUSY/CMSSW_10_5_0/src/StopTauHadronic/SampleProduction/jobsub"
PROXY="/nfs/dust/cms/user/yotarid/proxies/x509up_u35340"

cd $DIR

export SCRAM_ARCH=slc6_amd64_gcc530
export CPATH=$CPATH:$DIR

export X509_USER_PROXY=$PROXY

source /cvmfs/cms.cern.ch/cmsset_default.sh

eval `scramv1 runtime -sh`

$DIR/../bin/SelectCustomEvent -f $DIR/../settings/Selection_TauPair_TEST.xml -e 2017 -p TTbarMC