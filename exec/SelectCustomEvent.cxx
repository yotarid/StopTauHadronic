#include "../include/inout/Input.h"
#include "../include/inout/Output.h"
#include "../include/conf/Configuration.h"

#include "../extern/argvparser/argvparser.h"
#include "../extern/easylogging/easylogging++.h"

#include <chrono>

#include <CLHEP/Vector/LorentzVector.h>

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
  //
  cmd.defineOption("file", "Run description file", ArgvParser::OptionRequiresValue);
  cmd.defineOptionAlternative("file", "f");
  //
  cmd.defineOption("era", "Run era [2016, 2017, 2018]", ArgvParser::OptionRequiresValue);
  cmd.defineOptionAlternative("era", "e");
  //
  cmd.defineOption("process", "Run process [see available in XML settings file]", ArgvParser::OptionRequiresValue);
  cmd.defineOptionAlternative("process", "p");
  //
  cmd.defineOption("channel", "Run channel [see available in XML settings file]", ArgvParser::OptionRequiresValue);
  cmd.defineOptionAlternative("channel", "c");
  //
  cmd.defineOption("extension", "Output file extension. Empty if not passed", ArgvParser::OptionRequiresValue);
  cmd.defineOptionAlternative("extension", "x");

  int result = cmd.parse(argc, argv);
  if(result != ArgvParser::NoParserError)
  {
      LOG(INFO) << cmd.parseErrorDescription(result) << RESET;
      exit(1);
  }

  std::string configFile = cmd.foundOption("file") ? cmd.optionValue("file") : "";
  std::string era = cmd.foundOption("era") ? cmd.optionValue("era") : "";
  std::string process = cmd.foundOption("process") ? cmd.optionValue("process") : "";
  std::string channel = cmd.foundOption("channel") ? cmd.optionValue("channel") : "";
  std::string outfileExt = cmd.foundOption("extension") ? cmd.optionValue("extension") : "";

  conf::Configuration conf(configFile, era);
  conf::SelCuts selCuts = conf.GetSelCuts(process);

  out::Output output = out::Output(era, process, channel);
  output.Initialise(conf.GetOutputFileName(process, channel) + outfileExt);
  //
  in::Input input = in::Input(era, process, channel, conf.IsSignal(process), conf.GetDataFileName(process, channel));
  std::string inFile;
  std::shared_ptr<out::OutEvent> outEvent = output.GetEvent();
  while(std::getline(input.GetDataFile(), inFile))
  {
    input.Initialise(inFile);
    std::shared_ptr<in::GlobalEvent> globalEvent = input.GetGlobalEvent();
    int eventN = globalEvent->GetRecoEvent()->GetEventN();
    for(int iEvent = 0; iEvent < eventN; iEvent++)
    {
      globalEvent->LoadEvent(iEvent);

      obj::TauPair tauPair = globalEvent->GetTauPair(selCuts);
      if((tauPair.leadTau == nullptr) || (tauPair.subleadTau == nullptr) || (tauPair.isGenMatched == false)) continue;
      outEvent->LoadNewEvent(tauPair, 
                            globalEvent->GetRecoEvent()->GetMETE(),
                            globalEvent->GetRecoEvent()->GetMETPhi(),
                            0,
                            globalEvent->GetRecoEvent()->GetmT2(tauPair.leadTau->Get4Momentum(), tauPair.subleadTau->Get4Momentum()));
    }
    input.Finalise();
  }
  output.Finalise();
  input.GetDataFile().close();

  return 0;
}

