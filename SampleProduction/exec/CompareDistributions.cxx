#include "../utils/argvparser.h"
#include "../utils/easylogging++.h"

INITIALIZE_EASYLOGGINGPP

using namespace CommandLineProcessing;

int main (int argc, char* argv[])
{
  el::Configurations logConfig(std::string(std::getenv("SAMPLEPRODUCTION_BASE_DIR")) + "/settings/logger.conf");
  el::Loggers::reconfigureAllLoggers(logConfig);

  ArgvParser cmd;  

  cmd.addErrorCode(0, "Success");
  cmd.addErrorCode(1, "Error");
  // options
  cmd.setHelpOption("h", "help", "Print this help page");
  //
  cmd.defineOption("file1", "Output file 1", ArgvParser::OptionRequiresValue);
  cmd.defineOptionAlternative("file1", "f1");
  //
  cmd.defineOption("file2", "Output file 2", ArgvParser::OptionRequiresValue);
  cmd.defineOptionAlternative("file2", "f2");

  int result = cmd.parse(argc, argv);
  if(result != ArgvParser::NoParserError)
  {
      LOG(INFO) << cmd.parseErrorDescription(result) << RESET;
      exit(1);
  }

  std::string file1 = cmd.foundOption("file1") ? cmd.optionValue("file1") : "";
  std::string file1 = cmd.foundOption("file2") ? cmd.optionValue("file2") : "";

  return 0;
}