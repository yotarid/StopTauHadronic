#include "../include/Input.h"
#include "../include/Output.h"
#include "../include/Configuration.h"

#include "../utils/argvparser.h"
#include "../utils/easylogging++.h"

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

  int result = cmd.parse(argc, argv);
  if(result != ArgvParser::NoParserError)
  {
      LOG(INFO) << cmd.parseErrorDescription(result) << RESET;
      exit(1);
  }

  std::string configFile = cmd.foundOption("file") ? cmd.optionValue("file") : "";
  std::string era = cmd.foundOption("era") ? cmd.optionValue("era") : "";
  std::string process = cmd.foundOption("process") ? cmd.optionValue("process") : "";

  conf::Configuration conf(configFile, era);

  out::Output output(conf.GetOutputFileName(process), era, process);
  output.InitialiseOutput();

  for(auto dataFile : conf.GetDataFileList(process))
  {
    in::Input input(process, dataFile);
    std::string inFile;
    while(std::getline(input.GetDataFile(), inFile))
    {
      input.InitialiseInput(inFile);
      for(int iEvent = 0; iEvent < input.GetRecoNEvents(); iEvent++)
      {
        //Load branch contents 
        if(!input.LoadNewEvent(iEvent)) continue;
        if(input.GetRecoTauN() < 2) continue;

        //Get list of Taus passing selection criteria
        std::vector<int> recoTauSelected = input.GetRecoTauSelected(conf.GetSelCuts(process)); 
        if(recoTauSelected.size() < 2) continue;

        //Select Tau pair
        std::pair<int, int> recoTauPair = input.GetRecoTauPair(conf.GetSelCuts(process), recoTauSelected);
        if(recoTauPair.first == -1 || recoTauPair.second == -1) continue;

        output.SetRecoTauPairMETE(input.GetRecoMETE());
        output.SetRecoTauPairMETPhi(input.GetRecoMETPhi());

        output.SetRecoTauE(1, input.GetRecoTauE(recoTauPair.first));
        output.SetRecoTauPx(1, input.GetRecoTauPx(recoTauPair.first));
        output.SetRecoTauPy(1, input.GetRecoTauPy(recoTauPair.first));
        output.SetRecoTauPz(1, input.GetRecoTauPz(recoTauPair.first));
        output.SetRecoTaudXY(1, input.GetRecoTaudXY(recoTauPair.first));
        output.SetRecoTaudZ(1, input.GetRecoTaudZ(recoTauPair.first));
        output.SetRecoTauDeepTauIDvsJet(1, "Tight");
        output.SetRecoTauDeepTauIDvsEl(1, "Tight");
        output.SetRecoTauDeepTauIDvsMu(1, "Tight");
        output.SetRecoTauDecayMode(1, input.GetRecoTauDecayMode(recoTauPair.first));

        output.SetRecoTauE(2, input.GetRecoTauE(recoTauPair.second));
        output.SetRecoTauPx(2, input.GetRecoTauPx(recoTauPair.second));
        output.SetRecoTauPy(2, input.GetRecoTauPy(recoTauPair.second));
        output.SetRecoTauPz(2, input.GetRecoTauPz(recoTauPair.second));
        output.SetRecoTaudXY(2, input.GetRecoTaudXY(recoTauPair.second));
        output.SetRecoTaudZ(2, input.GetRecoTaudZ(recoTauPair.second));
        output.SetRecoTauDeepTauIDvsJet(2, "Tight");
        output.SetRecoTauDeepTauIDvsEl(2, "Tight");
        output.SetRecoTauDeepTauIDvsMu(2, "Tight");
        output.SetRecoTauDecayMode(2, input.GetRecoTauDecayMode(recoTauPair.second));

        output.SetRecoTauPairmT2(input.GetRecoTauPairmT2(recoTauPair));
        output.SetRecoTauPairHT(input.GetRecoTauPairHT(recoTauPair));

        output.LoadNewEvent();
      }
      input.FinaliseInput();
    }
    input.GetDataFile().close();
  }



  return 0;
}