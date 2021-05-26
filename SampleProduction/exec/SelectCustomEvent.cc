#include "../include/Input.h"
#include "../include/Output.h"
#include "../include/Configuration.h"

int main()
{
  std::string inFile = "/nfs/dust/cms/user/yotarid/SUSY/CMSSW_10_5_0/src/StopPairToTau_analysis/stopPair/sourceFiles/Tau_Run2018A-17Sep2018-v1_MINIAOD/Tau_Run2018A-17Sep2018-v1_MINIAOD_custom.txt";
  in::Input input(inFile);
  return 0;
}
