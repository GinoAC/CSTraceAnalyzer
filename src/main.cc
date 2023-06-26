#include <iostream>
#include <getopt.h>
#include <string.h>
#include <signal.h>
#include <memory>
#include <assert.h>

#include "trace_handler.h"
#include "instruction.h"
#include "analyzer.h"

#include "memory_regions.h"
//#include "user_defined_modules.h"

#include <CLI.hpp>
//#include <ftxui/screen/screen.hpp>

int main(int argc, char* argv[]){
  
  CLI::App app{"A trace analyzer"};

  int64_t start = 0;
  int64_t end = 0; 
  int64_t heartbeat = 0;
  int64_t current_instr_num = 0;
  std::string tracename;

  app.add_option("-t, --trace", tracename, "The paths to the traces.");
  app.add_option("-s,--start", start, "Instruction number to start analysis.");
  app.add_option("-e, --end", end, "Instruction number to end analysis.");
  app.add_option("--heartbeat", heartbeat, "Enables showing the heartbeat");
 
  analyzer lyzer;
  
  //Add your analysis module options here (TODO: Automate configuration)
  bool mem_region = false; 
  app.add_flag("-m, --memory-regions", mem_region, "Displays instruction and data memory regions.");
 
  CLI11_PARSE(app, argc, argv);

  if(tracename.empty()){
    printf("Must specify trace name...\n");
    return 0;
  }else{
    std::fill_n(std::ostreambuf_iterator<char>(std::cout), 50, '=');
    printf("\n");
    printf("Opening trace: %s\n", tracename.c_str());
    std::fill_n(std::ostreambuf_iterator<char>(std::cout), 50, '=');
    printf("\n");
  }
   
  //Add modules here (TODO: Automate configuration)
  if(mem_region){
    memory_regions mr;
    lyzer.add_module(new memory_regions());
  }

  //Create the trace handler
  std::unique_ptr<trace_handler> trace = get_trace_handler(tracename);

  printf("Reading trace...\n");
  std::fill_n(std::ostreambuf_iterator<char>(std::cout), 50, '=');
  printf("\n");

  while(!trace->is_complete()){

    //Read and pass an instruction to the underlying analysis modules
    lyzer.add_instruction(trace->get());
    current_instr_num++;

    if(heartbeat > 0 && current_instr_num % heartbeat == 0)
      printf("Heartbeat - Instruction Number : %ld\n", current_instr_num);

    if(current_instr_num >= start){
      if(current_instr_num == start){
        std::fill_n(std::ostreambuf_iterator<char>(std::cout), 50, '=');
        printf("\nStarting analysis during trace reading...\n");
        std::fill_n(std::ostreambuf_iterator<char>(std::cout), 50, '=');
        printf("\n");
      }
    }

    if(end != 0 && current_instr_num > end){
      std::fill_n(std::ostreambuf_iterator<char>(std::cout), 50, '=');
      printf("\nEnding trace analysis...\n");
      std::fill_n(std::ostreambuf_iterator<char>(std::cout), 50, '=');
      printf("\n");
      break;
    }

    //operate based on latest instruction read in
    lyzer.operate();
  }

  //Perform any post-trace analysis
  printf("Performing post trace-reading analysis...\n");

  return 0;
}
