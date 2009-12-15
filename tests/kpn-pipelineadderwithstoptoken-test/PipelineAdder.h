#ifndef PIPELINEADDER_H
#define PIPELINEADDER_H

#include "Pipeline.h"
#include "util.h"

#include "CompositeAdder.h"
#include "Display.h"

using namespace sacre;

class PipelineAdder : public Pipeline
{
 public:
  PipelineAdder(std::string);
};

PipelineAdder::PipelineAdder(std::string name) : Pipeline(name)
{
  CompositeAdder* ca = new CompositeAdder("CompositeAdder");
  addComponent(ca);

  Display* d = new Display("Display");
  addComponent(d);
  connect( ca->outPort< Token<int> >("out"), d->inPort< Token<int> >("in") );
}

#endif
