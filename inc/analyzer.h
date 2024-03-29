
#ifndef ANALYZER_H
#define ANALYZER_H

#include <algorithm>
#include <array>
#include <cstdint>
#include <functional>
#include <iostream>
#include <limits>
#include <vector>
#include <string.h>

#include "analysis_module.h"
#include "modules.h"
#include "instruction.h"
#include "trace_handler.h"

template <typename T>
class analyzer{

private:

  std::vector<analysis_module<T>> modules;
  uint64_t instr_unique_id = 0;
  T current_instruction;
  int64_t start = 0, end = 0;

public:

  analyzer() {};

  void set_window(int64_t _start, int64_t _end){
    start = _start;
    end = _end;
  }

  void add_instruction(T instr);

  //Adds a new module to the analyzer 
  void add_module(analysis_module<T> mod);

  //Operate function that iterates through the modules and 
  //calls their operate function
  void operate();

  //Calls each module to perform analysis after the trace
  //is finished being read
  void post_completition_analysis();  
};

typedef analyzer<instruction>    analyzer_instr;

#endif
