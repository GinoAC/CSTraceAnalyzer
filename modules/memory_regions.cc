
#include "memory_regions.h"
uint64_t unique_instr;

struct m_region{
  uint64_t start = 0;
  uint64_t size = 0;
};

std::map<uint64_t, m_region> ip_regions;
std::map<uint64_t, m_region> data_regions;

void memory_regions::module_operate() const{
	printf("Test\n");
}

//template <typename T>
void memory_regions::add_ip(){ printf("\n"); };
void memory_regions::add_data(){ printf("\n"); };

void memory_regions::sound_off(){printf("I'M HERE\n");}
