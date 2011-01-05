#ifndef PIPELINESCED_H
#define PIPELINESCED_H

#include "Pipeline.h"
#include "util.h"
#include "native/SCEDRouter.h"
#include "native/SCEDMerger.h"

#include "native/util/Source.h"
#include "native/util/Display.h"
#include "native/util/Multiply.h"
#include "native/util/FaultyMultiply.h"

using namespace sacre;

class PipelineSCED : public Pipeline
{
 public:
  PipelineSCED(std::string);
};

PipelineSCED::PipelineSCED(std::string name) : Pipeline(name)
{
  Source* s = new Source("Source1");
  addComponent(s);

  SCEDRouter< Token<int>, 4>* f = new SCEDRouter< Token<int>, 4>("SCEDRouter1x4");
  addComponent(f);

  Multiply* m1 = new Multiply("Multiply1");
  addComponent(m1);

  //FaultyMultiply* m2 = new FaultyMultiply("Multiply2");
  //addComponent(m2);
  Multiply* m2 = new Multiply("Multiply2");
  addComponent(m2);

  Multiply* m3 = new Multiply("Multiply3");
  addComponent(m3);

  //Multiply* m4 = new Multiply("Multiply4(Redundant)");
  //addComponent(m4);
  FaultyMultiply* m4 = new FaultyMultiply("Multiply4(Redundant)");
  addComponent(m4);

  SCEDMerger< Token<int>, 4>* mv = new SCEDMerger< Token<int>, 4>("SCEDMerger4x1");
  addComponent(mv);

  Display* d = new Display("Display");
  addComponent(d);

  connect( s->outPort< Token<int> >("out"), f->inPort< Token<int> >("in") );
  connect( f->outPort< Token<int> >("out1"), m1->inPort< Token<int> >("in") );
  connect( f->outPort< Token<int> >("out2"), m2->inPort< Token<int> >("in") );
  connect( f->outPort< Token<int> >("out3"), m3->inPort< Token<int> >("in") );
  connect( f->outPort< Token<int> >("out4"), m4->inPort< Token<int> >("in") );

  connect( m1->outPort< Token<int> >("out"), mv->inPort< Token<int> >("in1") );
  connect( m2->outPort< Token<int> >("out"), mv->inPort< Token<int> >("in2") );
  connect( m3->outPort< Token<int> >("out"), mv->inPort< Token<int> >("in3") );
  connect( m4->outPort< Token<int> >("out"), mv->inPort< Token<int> >("in4") );

  connect( mv->outPort< Token<int> >("out"), d->inPort< Token<int> >("in") );
}

#endif
