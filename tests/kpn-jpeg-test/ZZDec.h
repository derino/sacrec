//ZZDec.h
#ifndef ZZDEC_H
#define ZZDEC_H

#include "log4cxx/logger.h"
using namespace log4cxx;

#include <iostream>
#include <fstream>
#include <string.h>
#include "Component.h"

using namespace sacre;
using namespace std;


class ZZDec: public Component
{
 
 public:
  ZZDec(string);
  virtual void* task(void*);
  ~ZZDec();
};


ZZDec::ZZDec(string _name):Component(_name)
{
  addInPort< Token<int> >("inData");
  addOutPort< Token<int> >("outData");
}


ZZDec::~ZZDec()
{
  LOG4CXX_DEBUG(Logger::getLogger("application"),
                this->name << " is destructed."
                );
}


void* ZZDec::task(void* nullarg)
{
  int		i, j, l;
  int		block[64];
  
  while(1) {
    i=0 , j=-1;
    
    for ( l = 0 ; l < 4 ; l++ ) {
      for ( j++ ; i >= 0 ; j++, i-- ) {
	block[i*8+j] = this->inPort< Token<int> >("inData")->read().getData();
      }
      for ( i++ ; j >= 0 ; j--, i++ ) {
	block[i*8+j] =  this->inPort< Token<int> >("inData")->read().getData();
      }
    }
    
    for ( l = 0 ; l < 3 ; l++ ) {
      for ( i-- , j += 2 ; j < 8 ; j++ , i-- ) {
	block[i*8+j] =  this->inPort< Token<int> >("inData")->read().getData();
      }
      for ( j-- , i += 2 ; i < 8 ; j-- , i++ ) {
	block[i*8+j] =  this->inPort< Token<int> >("inData")->read().getData();
      }
    }
    
    i-- , j+=2;
    block[i*8+j] =  this->inPort< Token<int> >("inData")->read().getData();
    
    for ( i = 0 ; i < 8 ; ++i ) {
      for ( j = 0 ; j < 8 ; ++j ) {
	Token<int> pvt(block[i*8+j]);
	this->outPort< Token<int> >("outData")->write(pvt);
	//output.write(block[i*8+j]);
      }
    }
  }
  
  return NULL;
  
}

#endif
