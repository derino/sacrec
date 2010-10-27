// include log4cxx header files.                                                                                                               
#include "log4cxx/logger.h"
#include "log4cxx/propertyconfigurator.h"
#include "log4cxx/helpers/exception.h"
using namespace log4cxx;

#include "PipelineJpeg.h"


using namespace sacre;

int main()
{
  // Set up a simple configuration that logs on the console.                                                        
 PropertyConfigurator::configure("log4cxx.properties");

 PipelineJpeg pj("Jpeg pipeline");
 pj.run();
 
 return 0;
}

