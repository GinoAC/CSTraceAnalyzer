//This class defines the base class for an 
//analysis module that can extend the existing
//analysis infrastructure. Any additional subclasses
//should inherit from this.

#ifndef ANALYSIS_MODULE
#define ANALYSIS_MODULE

#include "instruction.h"

class analysis_module{

public:
  analysis_module(){} 

  virtual void add_inst(instruction inst)   = 0;
  virtual void module_operate()   = 0;
  virtual void text_output()   = 0;
  virtual void json_output()   = 0;
  virtual void graph_output()   = 0;
};


template<typename M>
class module_wrapper : public analysis_module
{
   M *m_mod;

public:
  module_wrapper(  M *mod) : m_mod(mod){}

  //void module_operate()   override {printf("Meow\n");}
  void module_operate()   override {m_mod->module_operate();}
  void add_inst(instruction inst)   override {m_mod->add_inst(inst);}
  void text_output()   override {m_mod->text_output();}
  void json_output()   override {m_mod->json_output();}
  void graph_output()   override {m_mod->graph_output();}
};
#endif
