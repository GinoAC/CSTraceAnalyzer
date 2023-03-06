//This class defines the base class for an 
//analysis module that can extend the existing
//analysis infrastructure. Any additional subclasses
//should inherit from this.

#ifndef ANALYSIS_MODULE
#define ANALYSIS_MODULE

template<typename T>
class analysis_module{

public:
  analysis_module(); 
  //~analysis_module();

  void operate(T instr);
  void text_output();
  void json_output();
  void graph_output();
};
#endif
