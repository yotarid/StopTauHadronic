#include "../include/Input.h"
#include "../include/Output.h"
#include "../include/Configuration.h"

#include "../utils/argvparser.h"
#include "../utils/easylogging++.h"

INITIALIZE_EASYLOGGINGPP

using namespace CommandLineProcessing;

int main(int argc, char* argv[])
{
  el::Configurations logConfig(std::string(std::getenv("SAMPLEPRODUCTION_BASE_DIR")) + "/settings/logger.conf");
  el::Loggers::reconfigureAllLoggers(logConfig);

  ArgvParser cmd;  

  cmd.addErrorCode(0, "Success");
  cmd.addErrorCode(1, "Error");
  // options
  cmd.setHelpOption("h", "help", "Print this help page");

  int result = cmd.parse(argc, argv);
  if(result != ArgvParser::NoParserError)
  {
      LOG(INFO) << cmd.parseErrorDescription(result);
      exit(1);
  }

  conf::Configuration conf("settings/Selection_TauPair.xml", "2017");
  std::cout << "XML settings file" << conf.GetFilePath() << std::endl;
  std::cout << "Era : " << conf.GetEra() << std::endl;

  std::string process = "TTbarMC";
  std::cout << "Process : " << process << std::endl;
  std::cout << "\t input dirs :" << std::endl;
  for(auto dir : conf.GetDataFileList(process))
    std::cout << "\t\t input dir : " << dir << std::endl;

  std::cout << "\t output file : " << conf.GetOutputFileName(process) << std::endl;
  out::Output output(conf.GetOutputFileName(process), conf.GetEra(), process);

  std::cout << "\t selection cuts : " << std::endl;
  std::cout << "\t\t tau pT : " << +conf.GetCutTauPt(process) << std::endl;
  std::cout << "\t\t tau eta : " << +conf.GetCutTauEta(process) << std::endl;
  std::cout << "\t\t tau dZ : " << +conf.GetCutTaudZ(process) << std::endl;
  std::cout << "\t\t tau dXY : " << +conf.GetCutTaudXY(process) << std::endl;
  std::cout << "\t\t tau deltaR : " << +conf.GetCutTaudeltaR(process) << std::endl;
  std::cout << "\t\t tau dR : " << +conf.GetCutTaudR(process) << std::endl;

  std::string dataFilePath = "data/TTToHadronic_TuneCP5_13TeV-powheg-pythia8_Fall17/TTToHadronic_TuneCP5_13TeV-powheg-pythia8_Fall17_custom.txt";
  //std::string dataFile = "root://dcache-cms-xrootd.desy.de//pnfs/desy.de/cms/tier2/store/user/sobhatta/Tau/crab_Tau_Run2018A-17Sep2018-v1_MINIAOD/210401_095406/0000/custom_1.root";
  in::Input input(process, dataFilePath);
  if(input.GetDataFile().is_open()) LOG(INFO) << BOLDYELLOW << "HELLO" << RESET;
 
  return 0;
}
