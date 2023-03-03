#include <iostream>
#include <getopt.h>
#include <string.h>
#include <signal.h>
#include <memory>
#include <assert.h>

#include "trace_handler.h"
#include "instruction.h"
#include "analyzer.h"

int main(int argc, char* argv[]){

  bool skip = false;
  int64_t start = 0;
  int64_t end = 0; 
  uint64_t current_instr_num = 0;
 
  static struct option long_options[] = {{"trace", required_argument, 0, 't'}};
  std::string tracename = "";

  if(argc <= 1){
    printf("Must include trace name...\n");
    assert(false);
  }

  int c;
  while ((c = getopt_long_only(argc, argv, "w:i:hc", long_options, NULL)) != -1) {
    switch (c) {
      case 't':
        tracename = optarg; 
        break;
      case 's':
        skip = atoi(optarg);
        break;
      case 'a':
        start = atoi(optarg);
        break;
      default:
        abort();
    }
  }

  if(tracename.empty()){
    printf("Must specify trace name...\n");
  }

  std::unique_ptr<trace_handler> trace = get_trace_handler(tracename);

  analyzer<instruction> lyzer;

  //add instruction for the analysis
  
  //Read instruction
  lyzer.add_instruction<instruction>(trace->get());

  //Perform analysis

  return 0;
}
