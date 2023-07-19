
#include "memory_regions.h"
uint64_t unique_instr;

bool check_r_address(uint64_t in, memory_regions::m_region region){
  uint64_t mask = region.seen_vect;
  uint64_t count = 0;
  if(in == region.start)
    return true;
  while(mask > 0){
    if(mask & 1 && in == (region.start + (1 << count)))
      return true;
    mask >>= 1;
    count++;
  }
  return false;
}

void memory_regions::add_memory(std::vector<m_region> &region, uint64_t addr){
  //Look to see if a memory region for this IP exists
  auto found = std::find_if(region.begin(), region.end(), [addr](auto &x){return ((x.start >> 12) << 12) == ((addr >> 12) << 12);});
  //printf("Region exists %d %llx\n", found != region.end(), (addr >> 12) << 12);
  if(found != region.end()){
    found->access += 1;
    uint64_t mask = 1 << ((addr - found->start) + 1);
    if(!(found->seen_vect & mask))
      found->seen_vect |= mask;
    return;
  }

  //create a new region
  memory_regions::m_region r;
  r.start = (addr >> 12) << 12;
  r.seen_vect = 1 << ((addr - r.start) + 1);
  r.access = 1;
  region.push_back(r);
  //printf("added new region og %llx base %llx start %llx offset %llx\n", addr, (addr >> 12) << 12, r.start, r.seen_vect);
  found = std::find_if(region.begin(), region.end(), [addr](auto &x){return ((x.start >> 12) << 12) == ((addr >> 12) << 12);});
  //printf("Added? %d\n", found != region.end());

  return;
}

void memory_regions::module_operate()  {
}

void memory_regions::add_inst(instruction inst)  {
  add_memory(ip_regions, inst.ip);
  if(inst.destination_memory.size() != 0){
    for(auto a : inst.destination_memory)
      add_memory(data_regions, a);
  }
  if(inst.source_memory.size() != 0){
    for(auto a : inst.source_memory)
      add_memory(data_regions, a);
  }
}

void memory_regions::text_output() {
  sort(data_regions.begin(), data_regions.end(), [](auto &x, auto &y){return x.start < y.start;});
  sort(ip_regions.begin(), ip_regions.end(), [](auto &x, auto &y){return x.start < y.start;});
  printf("Instruction Memory\n");
  printf("Page Accesses, Page Number, Instr Map\n");
  for(auto a : ip_regions){
    printf("%10-lld %10-llx", a.access, a.start >> 12);
    uint64_t mask = a.seen_vect;
    uint64_t count = 0;
    while(count < 64){
      if(mask & 1)
        printf("1");
      else
        printf("=");
      mask >>= 1;
      count++;
    } 
    printf("\n");
  }

  printf("Data Memory\n");
  printf("Page Accesses, Page Number, Data Map\n");
  for(auto a : data_regions){
    printf("%10-lld %10-llx %10-", a.access, a.start >> 12);
    uint64_t mask = a.seen_vect;
    uint64_t count = 0;
    while(count < 64){
      if(mask & 1)
        printf("1");
      else
        printf("=");
      mask >>= 1;
      count++;
    } 
    printf("\n");
  }
}

void memory_regions::json_output() {}
void memory_regions::graph_output() {}

