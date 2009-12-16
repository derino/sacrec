//IDCT.h
#ifndef IDCT_H
#define IDCT_H

#include "log4cxx/logger.h"
using namespace log4cxx;

#include <iostream>
#include <fstream>
#include <string.h>
#include <cmath>
#include "Component.h"

using namespace sacre;
using namespace std;


class IDCT: public Component
{ 
 
 public:
  IDCT(string);
  virtual void* task(void*);
  ~IDCT();

};

IDCT::IDCT(string _name):Component(_name)
{
  addInPort< Token<float> >("inData");
  addOutPort< Token<int> >("outData");
}

IDCT::~IDCT()
{
  LOG4CXX_DEBUG(Logger::getLogger("application"),
		this->name << " is destructed."
                );
}

void* IDCT::task(void* nullarg)
{
  int		i, j, k;
  float	value;
  float	block[64];
  float	temp_block[64];
  float	dct_coeffs[64];
  float	pi;
  int		blocki[64];
  int		pix;
  
  // calculate pi
  pi = 2*acos(0.0);
  
  // initialize dct_coeffs
  for ( i = 0 ; i < 8 ; i++ ) {
    for ( j = 0 ; j < 8 ; j++ ) {
      dct_coeffs[i*8+j] = cos((pi*(2*i+1)*j)/16);
    }
  }
  
  while (1) {
    // read input
    for ( i = 0 ; i < 8 ; i++ ) {
      for ( j = 0 ; j < 8 ; j++ ) {
	block[i*8+j] = this->inPort< Token<float> >("inData")->read().getData();
      }
    }
    
    // vertical 1D idct processing
    for ( i = 0 ; i < 8 ; i++ ) {
      for ( j = 0 ; j < 8 ; j++ ) {
	value = (block[j] * dct_coeffs[i*8])/sqrt(2);
	for ( k = 1 ; k < 8 ; k++ ) {
	  value += block[k*8+j] * dct_coeffs[i*8+k];
	}
	temp_block[i*8+j] = value / 2.0;
      }
    }

    // horizontal 1D idct processing
    for ( i = 0 ; i < 8 ; i++ ) {
      for ( j = 0 ; j < 8 ; j++ ) {
	value = (temp_block[j*8] * dct_coeffs[i*8])/sqrt(2);
	for ( k = 1 ; k < 8 ; ++k ) {
	  value += temp_block[j*8+k] * dct_coeffs[i*8+k];
	}
	pix = (int)(floor((value / 2.0) + 0.5));
	if (pix > 255) pix = 255;
	if (pix <   0) pix =   0;
	blocki[j*8+i] = pix;
      }
    }
    
    // output
    for ( i = 0 ; i < 8 ; ++i ) {
      for ( j = 0 ; j < 8 ; ++j ){
	Token<int> pvt(blocki[i*8+j]);
	this->outPort< Token<int> >("outData")->write(pvt);
	//	output.write(blocki[i*8+j]);
      }
    }
  }
  
  return NULL;
}

#endif
