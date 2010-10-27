#ifndef COMPOSITEADDER_H
#define COMPOSITEADDER_H

#include "Composite.h"
#include "util.h"

#include "Source1.h"
#include "Source2.h"
#include "Adder.h"

using namespace sacre;

class CompositeAdder : public Composite
{
 public:
  CompositeAdder(std::string);
};

CompositeAdder::CompositeAdder(std::string name) : Composite(name)
{
  Source1* s1 = new Source1("Source1");
  Source2* s2 = new Source2("Source2");
  Adder* a = new Adder("Adder");
  addComponent(s1);
  addComponent(s2);
  addComponent(a);
  addOutPort< Token<int> >("out", a->outPort< Token<int> >("out"));

  connect( s1->outPort< Token<int> >("out"), a->inPort< Token<int> >("in1") );
  connect( s2->outPort< Token<int> >("out"), a->inPort< Token<int> >("in2") );
}

#endif
