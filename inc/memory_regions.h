#ifndef MEM_REGIONS 
#define MEM_REGIONS

#include <algorithm>
#include <cstdint>
#include <functional>
#include <iostream>
#include <limits>
#include <vector>
#include <map>

#include "analysis_module.h"
#include "instruction.h"

class memory_regions : public analysis_module<instruction>
{
public:
//
//  struct m_region{
//    uint64_t start = 0;
//    uint64_t size = 0;
//  };
//
//  std::map<uint64_t, m_region> ip_regions;
//  std::map<uint64_t, m_region> data_regions;
//
//  memory_regions(){
//  
//  }
//
//  void operate(T instr);
//  void add_ip(uint64_t);
//  void add_data(uint64_t);
};
#endif
