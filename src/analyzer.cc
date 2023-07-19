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
#include "analyzer.h"
#include "memory_regions.h"

void analyzer::add_instruction(instruction instr){
	current_instruction = instr;
  for(auto a : modules){
    a->add_inst(instr);
  }
}

void analyzer::add_module(analysis_module *mod){
	modules.push_back(new module_wrapper(mod));
}

void analyzer::operate(){
	for(auto a : modules){
		a->module_operate();
  }
}

void analyzer::text_output(){
  for(auto a : modules){
    a->text_output();
  }
}

void analyzer::json_output(){}
void analyzer::graph_output(){}

