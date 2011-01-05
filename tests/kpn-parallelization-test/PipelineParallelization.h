#ifndef PIPELINEPARALLELIZATION_H
#define PIPELINEPARALLELIZATION_H

#include "Pipeline.h"
#include "util.h"
#include "native/Router.h"
#include "native/Merger.h"

#include "native/util/Source.h"
#include "native/util/Display.h"
#include "native/util/Multiply.h"

using namespace sacre;

class PipelineParallelization : public Pipeline
{
 public:
  PipelineParallelization(std::string);
};

PipelineParallelization::PipelineParallelization(std::string name) : Pipeline(name)
{
  Source* s = new Source("Source1");
  addComponent(s);

  Router< Token<int>, 3>* f = new Router< Token<int>, 3>("Router1x3");
  addComponent(f);

  Multiply* m1 = new Multiply("Multiply1");
  addComponent(m1);

  Multiply* m2 = new Multiply("Multiply2");
  addComponent(m2);

  Multiply* m3 = new Multiply("Multiply3");
  addComponent(m3);

  Merger< Token<int>, 3>* mv = new Merger< Token<int>, 3>("Merger1");
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
