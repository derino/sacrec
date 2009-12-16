#ifndef PIPELINEADDER_H
#define PIPELINEADDER_H

#include "Pipeline.h"
#include "util.h"
#include "native/Fork.h"

#include "Source1.h"
#include "Display.h"

using namespace sacre;

class PipelineFork : public Pipeline
{
 public:
  PipelineFork(std::string);
};

PipelineFork::PipelineFork(std::string name) : Pipeline(name)
{
  Source1* s = new Source1("Source1");
  addComponent(s);

  Fork< Token<int>, 2>* f = new Fork< Token<int>, 2>("Fork1x2");
  addComponent(f);

  Display* d1 = new Display("Display1");
  Display* d2 = new Display("Display2");
  addComponent(d1);
  addComponent(d2);

  connect( s->outPort< Token<int> >("out"), f->inPort< Token<int> >("in") );
  connect( f->outPort< Token<int> >("out1"), d1->inPort< Token<int> >("in") );
  connect( f->outPort< Token<int> >("out2"), d2->inPort< Token<int> >("in") );
}

#endif
