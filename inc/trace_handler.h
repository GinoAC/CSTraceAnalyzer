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


#ifndef TRACEREADER_H
#define TRACEREADER_H

#include <string>
#include <memory>

#include "instruction.h"

class trace_handler
{
protected:
  FILE* trace_file = NULL;
  std::string cmd_fmtstr;
  std::string decomp_program;
  std::string trace_name;

public:
  trace_handler(const trace_handler& other) = delete;
  trace_handler(std::string _ts);
  ~trace_handler();
  void open(std::string trace_string);
  void close();

  template <typename T>
  instruction read_single_instr();

  virtual instruction get() = 0;
};

std::unique_ptr<trace_handler> get_trace_handler(std::string fname);

template <typename T>
class input_trace_handler : public trace_handler
{
  instruction last_instr;
  bool initialized = false;

public:
  input_trace_handler(std::string _tn) : trace_handler(_tn) {}

  instruction get()
  {
    instruction trace_read_instr = read_single_instr<input_instr>();

    if (!initialized) {
      last_instr = trace_read_instr;
      initialized = true;
    }

    last_instr.branch_target = trace_read_instr.ip;
    instruction retval = last_instr;

    last_instr = trace_read_instr;
    return retval;
  }
};
#endif
