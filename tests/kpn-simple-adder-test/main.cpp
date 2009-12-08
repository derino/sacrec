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
  Source1 s1("Source 1");
  Source2 s2("Source 2");
  Adder a("Adder");
  Display d("Display");

  connect( s1.outPort<int>("out"), a.inPort<int>("in1") );
  connect( s2.outPort<int>("out"), a.inPort<int>("in2") );
  connect( a.outPort<int>("out"), d.inPort<int>("in") );

  //dump<int>(a.inPorts);

  std::cout << "starting" << std::endl;
  s1.start();
  s2.start();
  a.start();
  d.start();


  if( pthread_join( s1.getThread(), NULL) == 0 )
    std::cout << "Component " << s1.getName() << "'s thread finished succesfully." << std::endl;

  if( pthread_join( s2.getThread(), NULL) == 0 )
    std::cout << "Component " << s2.getName() << "'s thread finished succesfully." << std::endl;

  if( pthread_join( a.getThread(), NULL) == 0 )
    std::cout << "Component " << a.getName() << "'s thread finished succesfully." << std::endl;

  if( pthread_join( d.getThread(), NULL) == 0 )
    std::cout << "Component " << d.getName() << "'s thread finished succesfully." << std::endl;

  
  // Pipeline p = new Pipeline();
  // p->add(s1);
  // p->add(s2);
  // p->add(a);
  // p->add(d);
  // p->run();

  return 0;
}
