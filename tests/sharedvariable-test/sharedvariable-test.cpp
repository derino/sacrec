#include <iostream>
#include <pthread.h>

#include "util.h"
#include "SharedVariable.h"
#include "IntToken.h"

#include "Source1.h"
#include "Source2.h"
#include "Adder.h"
#include "Display.h"

using namespace sacre;

template <typename T>
void dump(std::map<std::string, Channel<T>*> const& m)
{
  for(typename std::map<std::string, Channel<T>*>::const_iterator i(m.begin()), j(m.end()); i != j; ++i)
    std::cout << '[' << i->first << "] = " << (i->second)->getName() << " ";// << (i->second)->getData() << '\n';
}

int main ()
{
  Source1 s1("Source 1");
  Source2 s2("Source 2");
  Adder a("Adder");
  Display d("Display");

  /*
  connect(s1["out"], a["in1"]);
  //connect(s1.operator[]<IntToken>("out"), a.operator[]<IntToken>("in1") );
  connect(s2["out"], a["in2"]);
  connect(a["out"], d["in"]);
  */

  connect( s1.outPort<int>("out"), a.inPort<int>("in1") );
  connect( s2.outPort<int>("out"), a.inPort<int>("in2") );
  connect( a.outPort<int>("out"), d.inPort<int>("in") );

  //connect(s1["sharedcount"], s2["sharedcount"], a["sharedcount"], d["sharedcount"]);
  //SharedVariable<void*>* sv = new SharedVariable<void*>("sharedcount");
  //sv->write(0); // sv inherits from BlockingChannel. has to be initialized because every comp first reads and then increments its value. otherwise everybody waits until its live.
  // update: SV doesn't inherit from BC so it's OK w/o above initial write().

  //connect(s1["sharedcount"], sv);
  //connect(s2["sharedcount"], sv);
  //connect(a["sharedcount"], sv);
  //connect(d["sharedcount"], sv);

  std::cout << "starting" << std::endl;
  s1.start();
  s2.start();
  a.start();
  d.start();
  
  return 0;
}
