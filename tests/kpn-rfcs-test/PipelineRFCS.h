#ifndef PIPELINERFCS_H
#define PIPELINERFCS_H

#include "Pipeline.h"
#include "util.h"
#include "native/RFCSMultiplicator.h"
#include "native/RFCSChecker.h"

#include "native/util/Source.h"
#include "native/util/Display.h"
#include "native/util/Multiply.h"
#include "native/util/FaultyMultiply.h"

using namespace sacre;

class PipelineRFCS : public Pipeline
{
 public:
  PipelineRFCS(std::string);
};

PipelineRFCS::PipelineRFCS(std::string name) : Pipeline(name)
{
  Source* s = new Source("Source1");
  addComponent(s);

  RFCSMultiplicator< Token<int> >* rfcsm = new RFCSMultiplicator< Token<int> >("RFCSMultiplicator1x3");
  addComponent(rfcsm);

  Multiply* m1 = new Multiply("Multiply1");
  addComponent(m1);

  FaultyMultiply* m2 = new FaultyMultiply("FaultyMultiply2");
  addComponent(m2);

  Multiply* m3 = new Multiply("Multiply3");
  addComponent(m3);

  RFCSChecker< Token<int> >* rfcsch = new RFCSChecker< Token<int> >("RFCSChecker");
  addComponent(rfcsch);

  Display* d = new Display("Display");
  addComponent(d);

  connect( s->outPort< Token<int> >("out"), rfcsm->inPort< Token<int> >("in") );
  connect( rfcsm->outPort< Token<int> >("out1"), m1->inPort< Token<int> >("in") );
  connect( rfcsm->outPort< Token<int> >("out2"), m2->inPort< Token<int> >("in") );
  connect( rfcsm->outPort< Token<int> >("out3"), m3->inPort< Token<int> >("in") );

  connect( m1->outPort< Token<int> >("out"), rfcsch->inPort< Token<int> >("in1") );
  connect( m2->outPort< Token<int> >("out"), rfcsch->inPort< Token<int> >("in2") );
  connect( m3->outPort< Token<int> >("out"), rfcsch->inPort< Token<int> >("in3") );

  connect( rfcsch->outPort< Token<int> >("out"), d->inPort< Token<int> >("in") );

  connect( rfcsch->outPort< Token<int> >("fault"), rfcsm->inPort< Token<int> >("fault") );
}

#endif
