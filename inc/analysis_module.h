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

  virtual void add_inst() const = 0;
  virtual void module_operate() const = 0;
  virtual void text_output() const = 0;
  virtual void json_output() const = 0;
  virtual void graph_output() const = 0;
};


template<typename M>
class module_wrapper : public analysis_module
{
  const M *m_mod;

public:
  module_wrapper(const M *mod) : m_mod(mod){}

  void module_operate() const {return m_mod->module_operate();}
  void add_inst() const {return m_mod->add_inst();}
  void text_output() const {return m_mod->text_output();}
  void json_output() const {return m_mod->json_output();}
  void graph_output() const {return m_mod->graph_output();}
};
#endif
