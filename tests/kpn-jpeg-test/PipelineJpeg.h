#ifndef PIPELINEJPEG_H
#define PIPELINEJPEG_H

#include <iostream>
#include <pthread.h>

#include "native/Fork.h"
#include "util.h"
#include "Pipeline.h"

#include "Source.h"
#include "Sink.h"
#include "R2B.h"
#include "DCT.h"
#include "Quantize.h"
#include "ZZEnc.h"
#include "RLEnc.h"
#include "RLDec.h"
#include "ZZDec.h"
#include "Normalize.h"
#include "IDCT.h"
#include "B2R.h"


using namespace sacre;

class PipelineJpeg : public Pipeline
{
 public:
  PipelineJpeg(std::string);
};

PipelineJpeg::PipelineJpeg(std::string name) : Pipeline(name)
{
  Source* so = new Source("Source");
  addComponent(so);
  R2B*    r2b = new R2B("R2B");
  addComponent(r2b);
  DCT*    dct = new DCT("DCT");
  addComponent(dct);
  Quantize* q = new Quantize("Quantize");
  addComponent(q);
  ZZEnc*    zze=new ZZEnc("ZZEnc");
  addComponent(zze);
  RLEnc*    rle=new RLEnc("RLEnc");
  addComponent(rle);
  RLDec*    rld=new RLDec("RLDec");
  addComponent(rld);
  ZZDec*    zzd=new ZZDec("ZZDec");
  addComponent(zzd);
  Normalize* n = new Normalize("Normalize");
  addComponent(n);
  IDCT*   idct =new IDCT("IDCT");
  addComponent(idct);
  B2R*    b2r = new B2R("B2R");
  addComponent(b2r);
  Sink*   si = new Sink("Sink");
  addComponent(si);
  Fork< Token<int>,3>* f=new Fork< Token<int>,3 >("Fork1x3");
  addComponent(f);

  connect( so->outPort< Token<int> >("outParam"), f->inPort< Token<int> >("in") );
  connect( f->outPort< Token<int> >("out1"), r2b->inPort< Token<int> >("inParam") );
  connect( f->outPort< Token<int> >("out2"), b2r->inPort< Token<int> >("inParam") );
  connect( f->outPort< Token<int> >("out3"), si->inPort< Token<int> >("inParam") );
  connect( so->outPort< Token<int> >("outData"), r2b->inPort< Token<int> >("inData") );
  connect( r2b->outPort< Token<int> >("outData"), dct->inPort< Token<int> >("inData") );
  connect( dct->outPort< Token<float> >("outData"), q->inPort< Token<float> >("inData") );
  connect( q->outPort< Token<int> >("outData"), zze->inPort< Token<int> >("inData") );
  connect( zze->outPort< Token<int> >("outData"), rle->inPort< Token<int> >("inData") );
  connect( rle->outPort< Token<int> >("outData"), rld->inPort< Token<int> >("inData") );
  connect( rld->outPort< Token<int> >("outData"), zzd->inPort< Token<int> >("inData") );
  connect( zzd->outPort< Token<int> >("outData"), n->inPort< Token<int> >("inData") );
  connect( n->outPort< Token<float> >("outData"), idct->inPort< Token<float> >("inData") );
  connect( idct->outPort< Token<int> >("outData"), b2r->inPort< Token<int> >("inData") );
  connect( b2r->outPort< Token<int> >("outData"), si->inPort< Token<int> >("inData") );

}

#endif
