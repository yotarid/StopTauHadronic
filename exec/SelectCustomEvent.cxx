#include "../include/Input.h"
#include "../include/Output.h"
#include "../include/Configuration.h"

#include "../extern/argvparser/argvparser.h"
#include "../extern/easylogging/easylogging++.h"

#include <chrono>

#include <CLHEP/Vector/LorentzVector.h>

INITIALIZE_EASYLOGGINGPP

using namespace CommandLineProcessing;
typedef std::vector<std::unique_ptr<obj::Tau>> TauVector;

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

  std::unique_ptr<out::Output> output = std::make_unique<out::Output>(era, process, channel);
  output->Initialise(conf.GetOutputFileName(process, channel) + outfileExt);
  //
  std::unique_ptr<in::Input> input = std::make_unique<in::Input>(era, process, channel, conf.GetDataFileName(process, channel));
  std::string inFile;
  std::shared_ptr<out::OUTEvent> outEvent = output->GetEvent();
  while(std::getline(input->GetDataFile(), inFile))
  {
    input->Initialise(inFile);
    for(int iEvent = 0; iEvent < input->GetRECOEventN(); iEvent++)
    {
      std::shared_ptr<in::INRECOEvent> inRECOEvent = input->GetNewRECOEvent(iEvent);
      obj::TauPair tauPair = inRECOEvent->GetSelectedTauPair(selCuts);
      if((tauPair.leadTau == nullptr) || (tauPair.subleadTau == nullptr)) continue;
      outEvent->LoadNewEvent(std::move(tauPair), 
                             inRECOEvent->GetMETE(),
                             inRECOEvent->GetMETPhi(),
                             0,
                             inRECOEvent->GetmT2(tauPair.leadTau->Get4Momentum(), tauPair.subleadTau->Get4Momentum()));
    }
    input->Finalise();
  }
  output->Finalise();
  input->GetDataFile().close();

  return 0;
}
