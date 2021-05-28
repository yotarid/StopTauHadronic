#include "../include/Input.h"
#include "../include/Output.h"
#include "../include/Configuration.h"

int main()
{
  std::string inFile = "root://dcache-cms-xrootd.desy.de//pnfs/desy.de/cms/tier2/store/user/sobhatta/Tau/crab_Tau_Run2018A-17Sep2018-v1_MINIAOD/210401_095406/0000/custom_1.root";
  in::Input input(inFile);

  conf::Configuration conf("settings/Selection_TauPair.xml", "2017");
  std::cout << "XML settings file" << conf.GetFilePath() << std::endl;
  std::cout << "Era : " << conf.GetEra() << std::endl;

  std::string process = "process0";
  std::cout << "Process : " << process << std::endl;
  std::cout << "\t input dirs :" << std::endl;
  for(auto dir : conf.GetInputDirList(process))
    std::cout << "\t\t input dir : " << dir << std::endl;

  std::cout << "\t output file : " << conf.GetOutputFilePath(process) << std::endl;

  std::cout << "\t selection cuts : " << std::endl;
  std::cout << "\t\t tau pT : " << +conf.GetCutTauPt(process) << std::endl;
  std::cout << "\t\t tau eta : " << +conf.GetCutTauEta(process) << std::endl;
  std::cout << "\t\t tau dZ : " << +conf.GetCutTaudZ(process) << std::endl;
  std::cout << "\t\t tau dXY : " << +conf.GetCutTaudXY(process) << std::endl;
  std::cout << "\t\t tau deltaR : " << +conf.GetCutTaudeltaR(process) << std::endl;
  std::cout << "\t\t tau dR : " << +conf.GetCutTaudR(process) << std::endl;

  process = "process1";
  std::cout << "Process : " << process << std::endl;
  std::cout << "\t input dirs :" << std::endl;
  for(auto dir : conf.GetInputDirList(process))
    std::cout << "\t\t input dir : " << dir << std::endl;

  std::cout << "\t output file : " << conf.GetOutputFilePath(process) << std::endl;

  std::cout << "\t selection cuts : " << std::endl;
  std::cout << "\t\t tau pT : " << +conf.GetCutTauPt(process) << std::endl;
  std::cout << "\t\t tau eta : " << +conf.GetCutTauEta(process) << std::endl;
  std::cout << "\t\t tau dZ : " << +conf.GetCutTaudZ(process) << std::endl;
  std::cout << "\t\t tau dXY : " << +conf.GetCutTaudXY(process) << std::endl;
  std::cout << "\t\t tau deltaR : " << +conf.GetCutTaudeltaR(process) << std::endl;
  std::cout << "\t\t tau dR : " << +conf.GetCutTaudR(process) << std::endl;


  return 0;
}
