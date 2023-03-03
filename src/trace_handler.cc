/*
 *    Copyright 2023 The CSTraceAnalyzer Contributors
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

//Note: This file is derivied from the ChampSim simulator's codebase
//
//

#include "trace_handler.h"

#include <cassert>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <string>
#include <memory>

trace_handler::trace_handler(std::string _ts) : trace_name(_ts)
{
  std::string last_dot = trace_name.substr(trace_name.find_last_of("."));

  if (trace_name.substr(0, 4) == "http") {
    // Check file exists
    char testfile_command[4096];
    sprintf(testfile_command, "wget -q --spider %s", trace_name.c_str());
    FILE* testfile = popen(testfile_command, "r");
    if (pclose(testfile)) {
      std::cerr << "TRACE FILE NOT FOUND" << std::endl;
      assert(0);
    }
    cmd_fmtstr = "wget -qO- -o /dev/null %2$s | %1$s -dc";
  } else {
    std::ifstream testfile(trace_name);
    if (!testfile.good()) {
      std::cerr << "TRACE FILE NOT FOUND" << std::endl;
      assert(0);
    }
    cmd_fmtstr = "%1$s -dc %2$s";
  }

  if (last_dot[1] == 'g') // gzip format
    decomp_program = "gzip";
  else if (last_dot[1] == 'x') // xz
    decomp_program = "xz";
  else {
    std::cout << "ChampSim does not support traces other than gz or xz compression!" << std::endl;
    assert(0);
  }

  open(trace_name);
}

trace_handler::~trace_handler() { close(); }

template <typename T>
instruction trace_handler::read_single_instr()
{
  T trace_read_instr;

  while (!fread(&trace_read_instr, sizeof(T), 1, trace_file)) {
    // reached end of file for this trace
    std::cout << "*** Reached end of trace: " << trace_name << std::endl;

    // close the trace file and re-open it
    close();
    open(trace_name);
  }

  // copy the instruction into the performance model's instruction format
  instruction retval(trace_read_instr);
  return retval;
}

void trace_handler::open(std::string trace_string)
{
  char gunzip_command[4096];
  sprintf(gunzip_command, cmd_fmtstr.c_str(), decomp_program.c_str(), trace_string.c_str());
  trace_file = popen(gunzip_command, "r");
  if (trace_file == NULL) {
    std::cerr << std::endl << "*** CANNOT OPEN TRACE FILE: " << trace_string << " ***" << std::endl;
    assert(0);
  }
}

void trace_handler::close()
{
  if (trace_file != NULL) {
    pclose(trace_file);
  }
}

std::unique_ptr<trace_handler> get_trace_handler(std::string fname)
{
    return std::make_unique<input_trace_handler<input_instr>>(fname);
}
