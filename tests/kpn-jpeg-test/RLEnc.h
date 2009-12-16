//RLEnc.h
#ifndef RLENC_H
#define RLENC_H

#include "log4cxx/logger.h"
using namespace log4cxx;

#include <iostream>
#include <fstream>
#include <string.h>
#include "Component.h"

using namespace sacre;
using namespace std;


class RLEnc: public Component
{
 
 public:
  RLEnc(string);
  virtual void* task(void*);
  ~RLEnc();
};


RLEnc::RLEnc(string _name):Component(_name)
{
  addInPort< Token<int> >("inData");
  addOutPort< Token<int> >("outData");
}


RLEnc::~RLEnc()
{
  LOG4CXX_DEBUG(Logger::getLogger("application"),
                this->name << " is destructed."
                );
}


void* RLEnc::task(void* nullarg)
{
  int		count;
  int		k;
  int		value;
  
  while (1) {
    // read and write DC value
    Token<int>* pvt=new Token<int>(this->inPort< Token<int> >("inData")->read().getData());
    this->outPort< Token<int> >("outData")->write(*pvt);
    //output.write(input.read());
    
    count = 0;
    
    for( k = 1 ; k < 64 ; k++ ) {
      value =  this->inPort< Token<int> >("inData")->read().getData();
      if ( value == 0 ) {
	count++;
      }
      else {
	Token<int>* pvt1=new Token<int>(count);
	this->outPort< Token<int> >("outData")->write(*pvt1);
	//output.write(count);
	count = 0;
	Token<int>* pvt2=new Token<int>(value);
	this->outPort< Token<int> >("outData")->write(*pvt2);
	//output.write(value);
      }
    }
    Token<int>* pvt3=new Token<int>(64);
    this->outPort< Token<int> >("outData")->write(*pvt3);
    //output.write(64);
  }

  return NULL;
}

#endif
