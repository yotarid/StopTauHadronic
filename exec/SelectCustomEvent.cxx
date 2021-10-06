#include "../include/Input.h"
#include "../include/Output.h"
#include "../include/Configuration.h"

#include "../extern/argvparser/argvparser.h"
#include "../extern/easylogging/easylogging++.h"

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

  out::Output output(era, process, channel, conf.GetOutputFileName(process, channel) + outfileExt);
  output.InitialiseOutput();
  //
  in::Input input(era, process, channel, conf.GetDataFileName(process, channel));
  std::string inFile;
  while(std::getline(input.GetDataFile(), inFile))
  {
    input.InitialiseInput(inFile);
    for(int iEvent = 0; iEvent < input.GetRecoNEvents(); iEvent++)
    {
      //Load branch contents 
      if(!input.LoadNewEvent(iEvent)) continue;
      if(input.GetRecoTauN() < 2) continue;

      //Select Tau pair
      std::vector<int> recoTauPair = input.GetRecoTauPair(conf.GetSelCuts(process));
      if(recoTauPair.size() != 2) continue;

      //Fill output event
      for(int i = 0; i < 2; i++) 
      {
        int iTau = (i == 0) ? 1 : 2;
        int iTauIdx = recoTauPair[i];
        //
        output.SetRecoTauE(iTau, input.GetRecoTauE(iTauIdx));
        output.SetRecoTauPx(iTau, input.GetRecoTauPx(iTauIdx));
        output.SetRecoTauPy(iTau, input.GetRecoTauPy(iTauIdx));
        output.SetRecoTauPz(iTau, input.GetRecoTauPz(iTauIdx));
        output.SetRecoTauPt(iTau, input.GetRecoTauPt(iTauIdx));
        output.SetRecoTaudXY(iTau, input.GetRecoTaudXY(iTauIdx));
        output.SetRecoTaudZ(iTau, input.GetRecoTaudZ(iTauIdx));
        output.SetRecoTauDeepTauIDvsJet(iTau, conf.GetSelCuts(process).deepTauID);
        output.SetRecoTauDeepTauIDvsEl(iTau, conf.GetSelCuts(process).deepTauID);
        output.SetRecoTauDeepTauIDvsMu(iTau, conf.GetSelCuts(process).deepTauID);
        output.SetRecoTauDecayMode(iTau, input.GetRecoTauDecayMode(iTauIdx));
      }
      output.SetRecoTauPairMETE(input.GetRecoMETE());
      output.SetRecoTauPairMETPhi(input.GetRecoMETPhi());
      output.SetRecoTauPairmT2(input.GetRecoTauPairmT2(recoTauPair));
      output.SetRecoTauPairHT(input.GetRecoTauPairHT(recoTauPair));
      //
      output.LoadNewEvent();
    }
    input.FinaliseInput();
  }
  output.FinaliseOutput();
  input.GetDataFile().close();



  return 0;
}