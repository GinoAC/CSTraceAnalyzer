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

class memory_regions : public analysis_module
{
public:
  uint64_t unique_instr;

  struct m_region{
    uint64_t start = 0;
    uint64_t seen_vect = 0;
    uint64_t access = 0;
  };

  std::vector<m_region> ip_regions;
  std::vector<m_region> data_regions;

  memory_regions(){
  }

	void sound_off();

  void module_operate() override;
  void add_inst(instruction inst) override; 
  void text_output() override;
  void json_output() override;
  void graph_output() override;
 
  void add_memory(std::vector<m_region> &region, uint64_t addr);
};
#endif
