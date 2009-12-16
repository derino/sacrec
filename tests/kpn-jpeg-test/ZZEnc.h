//ZZEnc.h
#ifndef ZZENC_H
#define ZZENC_H

#include "log4cxx/logger.h"
using namespace log4cxx;

#include <iostream>
#include <fstream>
#include <string.h>
#include "Component.h"

using namespace sacre;
using namespace std;


class ZZEnc: public Component
{
 
 public:
  ZZEnc(string);
  virtual void* task(void*);
  ~ZZEnc();
};


ZZEnc::ZZEnc(string _name):Component(_name)
{
  addInPort< Token<int> >("inData");
  addOutPort< Token<int> >("outData");
}


ZZEnc::~ZZEnc()
{
  LOG4CXX_DEBUG(Logger::getLogger("application"),
                this->name << " is destructed."
                );
}


void* ZZEnc::task(void* nullarg)
{
  int		i, j, k, l;
  int		temp_block[64];                     
  int		block[64];
  
  while(1) {
    //read in the blocks for 8 lines
    for ( i = 0 ; i < 8 ; i ++) {
      for ( j = 0 ; j < 8 ; j++ ) {
	temp_block[8 * i + j ]=  this->inPort< Token<int> >("inData")->read().getData();
      }
    }
    
    i = 0 , j = -1 , k = 0;
    
    for ( l = 0 ; l < 4 ; l++ ) {
      for ( j++ ; i >= 0 ; j++ , i-- ) {
	block[k] = temp_block[i*8+j];
	k++;
      }
      
      for ( i++ ; j >= 0 ; j-- , i++ ) {
	block[k] = temp_block[i*8+j];
	k++;
      }
    }
    
    for ( l = 0 ; l < 3 ; l++ ) {
      for ( i-- , j += 2 ; j < 8 ; j++ , i-- ) {
	block[k] = temp_block[i*8+j];
	k++;
      }
      for ( j-- , i += 2 ; i < 8 ; j-- , i++ ) {
	block[k] = temp_block[i*8+j];
	k++;
      }
    }
    
    i-- , j += 2;
    block[k] = temp_block[i*8+j];
    
    for ( i = 0 ; i < 64 ; ++i ) {
      Token<int>* pvt=new Token<int>(block[i]);
      this->outPort< Token<int> >("outData")->write(*pvt);
      //output.write (block[i]);
    }
  }
  
  return NULL;
}

#endif
