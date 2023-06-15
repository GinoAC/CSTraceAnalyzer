//This class defines the base class for an 
//analysis module that can extend the existing
//analysis infrastructure. Any additional subclasses
//should inherit from this.

#ifndef ANALYSIS_MODULE
#define ANALYSIS_MODULE

template<typename T>
class analysis_module{

public:
  analysis_module(){} 

  virtual void add_inst(){}
  virtual void module_operate(){}
  virtual void text_output(){}
  virtual void json_output(){}
  virtual void graph_output(){}
};

#endif
