from posixpath import join
import sys
import logging
import argparse
import xml.etree.ElementTree as xml
#import configparser
import os.path
from colors import *



def create_job_log_directory(era, process, channel) : 
  #create the directory tree for job logging files
  os.system("mkdir -p " + os.path.join(os.getenv('SAMPLEPRODUCTION_JOBSUB_DIR'), "jobs", era))
  os.system("mkdir -p " + os.path.join(os.getenv('SAMPLEPRODUCTION_JOBSUB_DIR'), "jobs", era, process))
  os.system("mkdir -p " + os.path.join(os.getenv('SAMPLEPRODUCTION_JOBSUB_DIR'), "jobs", era, process, channel))

def create_jobsub_file(era, process, channel) : 
  #open original jobsub file
  jobsub_path = os.path.join(os.getenv('SAMPLEPRODUCTION_JOBSUB_DIR'), "jobsub.sh")
  jobsub_content = open(jobsub_path, "r").read()
  #modify orginal jobsub file
  jobsub_content = jobsub_content.replace("@ERA@", era)
  jobsub_content = jobsub_content.replace("@PROCESS@", process)
  jobsub_content = jobsub_content.replace("@CHANNEL@", channel)
  #create new jobsub file
  jobsub_mod_path = os.path.join(os.getenv('SAMPLEPRODUCTION_JOBSUB_DIR'), "jobs", era, process, channel, "jobsub.sh")
  jobsub_mod = open(jobsub_mod_path, "w")
  jobsub_mod.write(jobsub_content)
  #allow execution of jobsub file
  os.system("chmod +x " + jobsub_mod_path)
  ##
  #open original jobconfig file
  jobconfig_path = os.path.join(os.getenv('SAMPLEPRODUCTION_JOBSUB_DIR'), "jobconfig.sub")
  jobconfig_content = open(jobconfig_path, "r").read()
  #modify original jobconfig file
  condor_logging_path = os.path.join(os.getenv('SAMPLEPRODUCTION_JOBSUB_DIR'), "jobs", era, process, channel)
  jobconfig_content = jobconfig_content.replace("@EXECUTABLE_PATH@", jobsub_mod_path)
  jobconfig_content = jobconfig_content.replace("@ERROR_PATH@", condor_logging_path)
  jobconfig_content = jobconfig_content.replace("@OUTPUT_PATH@", condor_logging_path)
  jobconfig_content = jobconfig_content.replace("@LOG_PATH@", condor_logging_path)
  #create new jobconfig file
  jobconfig_modified = open(os.path.join(os.getenv('SAMPLEPRODUCTION_JOBSUB_DIR'), "jobs", era, process, channel, "jobconfig.sub"), "w")
  jobconfig_modified.write(jobconfig_content)

def launch_job(era, process, channel) : 
  #launch condor job submission command
  failure = os.system("condor_submit -file " + os.path.join(os.getenv('SAMPLEPRODUCTION_JOBSUB_DIR'), "jobs", era, process, channel, "jobconfig.sub") )
  if not failure :
    print(tcolors.GREEN + "Successfuly submited job for " + era + ", " + process + ", " + channel + tcolors.RESET)
  else :
    print(tcolors.RED + "Failed submitting job for " + era + ", " + process + ", " + channel + tcolors.RESET)
  

if (__name__ == "__main__") :
  #parsing xml file to have access to all configuration information
  xml_file = xml.parse(os.path.join(os.getenv('SAMPLEPRODUCTION_BASE_DIR'), "settings/Selection_TauPair.xml"))
  run = xml_file.getroot()

  #chosen run list in dictionary
  run_list = {}

  ########################
  ###### CHOOSE ERA ######
  ########################
  print("")
  print(tcolors.BLUE + "Choose Era : " + tcolors.RESET)
  for era in run.iter('Era') :
      print(era.attrib['date'])
  era_list = str(raw_input(tcolors.GREEN + "Era choice : " + tcolors.RESET)).strip().split()

  ########################
  #### CHOOSE PROCESS ####
  ########################
  for era in run.iter('Era') : 
    if era.attrib['date'] not in era_list : 
      continue
    print("")
    print(tcolors.BLUE + "Choose Process for " + era.attrib['date'] + " : " + tcolors.RESET)
    for process in era.iter('Process') : 
      print(process.attrib['name'])
    process_list = str(raw_input(tcolors.GREEN + "Process choice for " + era.attrib['date'] + " : " + tcolors.RESET)).strip().split()
    run_list[era.attrib['date']] = process_list

  ##############################
  ##### LAUNCH CONDOR JOBS #####
  ##############################

  for era in run.iter('Era') : #loop over eras in xml
    era_date = era.attrib['date']
    if era_date not in run_list.keys() : #check if era is chosen
      continue
    for process in era.iter("Process") : #loop over process for the chosen era
      process_name = process.attrib['name']
      if process_name not in run_list[era_date] : #check if process is chosen
        continue
      for channel in process.find("Data").iter("Channel") :
        channel_name = channel.attrib['name']
        create_job_log_directory(era_date, process_name, channel_name)
        create_jobsub_file(era_date, process_name, channel_name)
        launch_job(era_date, process_name, channel_name)
