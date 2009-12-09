// include log4cxx header files.
#include "log4cxx/logger.h"
#include "log4cxx/propertyconfigurator.h"
#include "log4cxx/helpers/exception.h"
using namespace log4cxx;

#include <iostream>
#include <pthread.h>

#include "util.h"
#include "Source1.h"
#include "Source2.h"
#include "Adder.h"
#include "Display.h"

using namespace sacre;

int main ()
{
  // Set up a simple configuration that logs on the console.
  PropertyConfigurator::configure("log4cxx.properties");
 
 

  Source1 s1("Source 1");
  Source2 s2("Source 2");
  Adder a("Adder");
  Display d("Display");

  connect( s1.outPort<int>("out"), a.inPort<int>("in1") );
  connect( s2.outPort<int>("out"), a.inPort<int>("in2") );
  connect( a.outPort<int>("out"), d.inPort<int>("in") );

  //dump<int>(a.inPorts);

  s1.start();
  s2.start();
  a.start();
  d.start();


  if( pthread_join( s1.getThread(), NULL) == 0 )
    LOG4CXX_DEBUG(Logger::getLogger("application"), 
		  "Component " << s1.getName() << "'s thread finished succesfully."
		  );

  if( pthread_join( s2.getThread(), NULL) == 0 )
    LOG4CXX_DEBUG(Logger::getLogger("application"), 
		  "Component " << s2.getName() << "'s thread finished succesfully."
		  );

  if( pthread_join( a.getThread(), NULL) == 0 )
    LOG4CXX_DEBUG(Logger::getLogger("application"), 
		  "Component " << a.getName() << "'s thread finished succesfully."
		  );

  if( pthread_join( d.getThread(), NULL) == 0 )
    LOG4CXX_DEBUG(Logger::getLogger("application"), 
		  "Component " << d.getName() << "'s thread finished succesfully."
		  );


  
  // Pipeline p = new Pipeline();
  // p->add(s1);
  // p->add(s2);
  // p->add(a);
  // p->add(d);
  // p->run();

  return 0;
}
