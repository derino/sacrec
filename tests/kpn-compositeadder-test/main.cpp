// include log4cxx header files.
#include "log4cxx/logger.h"
#include "log4cxx/propertyconfigurator.h"
#include "log4cxx/helpers/exception.h"
using namespace log4cxx;

#include <iostream>
#include <pthread.h>

#include "util.h"

#include "CompositeAdder.h"
#include "Display.h"

using namespace sacre;

int main ()
{
  // Set up a simple configuration that logs on the console.
  PropertyConfigurator::configure("log4cxx.properties");

  CompositeAdder ca("CompositeAdder");
  Display d("Display");

  connect( ca.outPort<int>("out"), d.inPort<int>("in") );

  //dump<int>(a.inPorts);

  ca.start();
  d.start();


  if( pthread_join( ca.getThread(), NULL) == 0 )
    LOG4CXX_DEBUG(Logger::getLogger("application"), 
		  "Component " << ca.getName() << "'s thread finished succesfully."
		  );

  if( pthread_join( d.getThread(), NULL) == 0 )
    LOG4CXX_DEBUG(Logger::getLogger("application"), 
		  "Component " << d.getName() << "'s thread finished succesfully."
		  );

  return 0;
}
