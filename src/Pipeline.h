#ifndef PIPELINE_H
#define PIPELINE_H

#include "log4cxx/logger.h"
using namespace log4cxx;

#include <cstdlib>
#include <string>
#include <map>

#include "Composite.h"



namespace sacre
{
  
  class Pipeline : public Composite
  {
  public:
    Pipeline(std::string);
    ~Pipeline();
    void run();
  };
  
  
  Pipeline::Pipeline(std::string _name): Composite(_name)
    {
      //isComposite = true;
    }

  Pipeline::~Pipeline()
    {
      LOG4CXX_DEBUG(Logger::getLogger("sacrec"), 
		    "Pipeline" << name << " is destructed."
		    );
    
    }
  
  void Pipeline::run()
  {
    start();
    
    if( pthread_join( getThread(), NULL) == 0 )
      LOG4CXX_DEBUG(Logger::getLogger("sacrec"), 
		    "Thread of Pipeline " << name << " has finished succesfully."
		    );
  }

}
#endif
