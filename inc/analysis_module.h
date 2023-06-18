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


template<typename M>
class module_wrap : public analysis_module<instruction>
{
  const M *m_mod;
public:
  module_wrap(const M *mod) : m_mod(mod){}
  
  void add_inst() const {m_mod->add_inst();}
  void module_operate() const {m_mod->module_operate();}
  void text_output() const {m_mod->text_output();}
  void json_output() const {m_mod->json_output();}
  void graph_output() const {m_mod->graph_output();}
};
#endif
