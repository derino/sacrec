//RLDec.h
#ifndef RLDEC_H
#define RLDEC_H

#include "log4cxx/logger.h"
using namespace log4cxx;

#include <iostream>
#include <fstream>
#include <string.h>
#include "Component.h"

using namespace sacre;
using namespace std;


class RLDec: public Component
{
 
 public:
  RLDec(string);
  virtual void* task(void*);
  ~RLDec();
};


RLDec::RLDec(string _name):Component(_name)
{
  addInPort< Token<int> >("inData");
  addOutPort< Token<int> >("outData");
}


RLDec::~RLDec()
{
  LOG4CXX_DEBUG(Logger::getLogger("application"),
                this->name << " is destructed."
                );
}


void* RLDec::task(void* nullarg)
{
  int		count;
  int		value;
  
  while (1) {
    // read and write DC value
    Token<int> pvt(this->inPort< Token<int> >("inData")->read().getData());
    this->outPort< Token<int> >("outData")->write(pvt);
    // output.write(input.read());
    // process AC values
    count = 1;
    // read zero length value
    value = this->inPort< Token<int> >("inData")->read().getData();
    while (value != 64) {
      // process zl
      for ( ; value > 0 ; value-- ) {
	Token<int> pvt1(0);
	this->outPort< Token<int> >("outData")->write(pvt1);
	//output.write(0);
	count++;
      }
      // read and process non-zero value
      Token<int> pvt2(this->inPort< Token<int> >("inData")->read().getData());
      this->outPort< Token<int> >("outData")->write(pvt2);
      // output.write(input.read());
      count ++;
      // read zero length value
      value = this->inPort< Token<int> >("inData")->read().getData();
    }
    // process zero length of 64
    for ( ; count<64 ; ) {
      Token<int> pvt3(0);
      this->outPort< Token<int> >("outData")->write(pvt3);
      //output.write(0);
      count++;
    }
  }
  return NULL;
}

#endif
