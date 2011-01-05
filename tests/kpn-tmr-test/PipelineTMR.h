#ifndef PIPELINETMR_H
#define PIPELINETMR_H

#include "Pipeline.h"
#include "util.h"
#include "native/Fork.h"
#include "native/MajorityVoter.h"

#include "native/util/Source.h"
#include "native/util/Display.h"
#include "native/util/Multiply.h"
#include "native/util/FaultyMultiply.h"

using namespace sacre;

class PipelineTMR : public Pipeline
{
 public:
  PipelineTMR(std::string);
};

PipelineTMR::PipelineTMR(std::string name) : Pipeline(name)
{
  Source* s = new Source("Source1");
  addComponent(s);

  Fork< Token<int>, 3>* f = new Fork< Token<int>, 3>("Fork1x3");
  addComponent(f);

  Multiply* m1 = new Multiply("Multiply1");
  addComponent(m1);

  FaultyMultiply* m2 = new FaultyMultiply("FaultyMultiply2");
  addComponent(m2);

  Multiply* m3 = new Multiply("Multiply3");
  addComponent(m3);

  MajorityVoter< Token<int> >* mv = new MajorityVoter< Token<int> >("MajorityVoter1");
  addComponent(mv);

  Display* d = new Display("Display");
  addComponent(d);

  connect( s->outPort< Token<int> >("out"), f->inPort< Token<int> >("in") );
  connect( f->outPort< Token<int> >("out1"), m1->inPort< Token<int> >("in") );
  connect( f->outPort< Token<int> >("out2"), m2->inPort< Token<int> >("in") );
  connect( f->outPort< Token<int> >("out3"), m3->inPort< Token<int> >("in") );

  connect( m1->outPort< Token<int> >("out"), mv->inPort< Token<int> >("in1") );
  connect( m2->outPort< Token<int> >("out"), mv->inPort< Token<int> >("in2") );
  connect( m3->outPort< Token<int> >("out"), mv->inPort< Token<int> >("in3") );

  connect( mv->outPort< Token<int> >("out"), d->inPort< Token<int> >("in") );
}

#endif
