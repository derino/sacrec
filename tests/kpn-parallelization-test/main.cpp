// include log4cxx header files.
#include "log4cxx/logger.h"
#include "log4cxx/propertyconfigurator.h"
#include "log4cxx/helpers/exception.h"
using namespace log4cxx;

#include <iostream>
#include <pthread.h>

#include "util.h"

#include "PipelineParallelization.h"

using namespace sacre;

int main ()
{
  // Set up a simple configuration that logs on the console.
  PropertyConfigurator::configure("log4cxx.properties");

  PipelineParallelization pf("fork pipeline");
  pf.run();

  //dump<int>(a.inPorts);
  return 0;
}
