//B2R.h
#ifndef B2R_H
#define B2R_H

#include "log4cxx/logger.h"
using namespace log4cxx;

#include <iostream>
#include <fstream>
#include <string.h>
#include "Component.h"

using namespace sacre;
using namespace std;

//#define MAXWIDTH 1024;

class B2R: public Component
{
 
 public:
  B2R(string);
  virtual void* task(void*);
  ~B2R();

 private:
  int maxwidth;

};


B2R::B2R(string _name):Component(_name)
{
  addInPort< Token<int> >("inParam");
  addInPort< Token<int> >("inData");
  addOutPort< Token<int> >("outData");
  
  //set maxwidth
  maxwidth=MAXWIDTH;
  
}

B2R::~B2R()
{
  LOG4CXX_DEBUG(Logger::getLogger("application"),
                this->name << " is destructed."
                );
}

void* B2R::task(void* nullarg)
{
  
  int		row, col;
  int		maxwidth8  = (maxwidth +7)/8 * 8;   // round up to multiples of 8
  int *	lines = new int [maxwidth8 * 8];	// we need 8 lines before outputting
  int		count = 0;		   	// number of lines read in
  int		width, height, width8; 	       	// the actual width and height of the picture
  
  /* read first the parameters */
  width= this->inPort< Token<int> >("inParam")->read().getData();
  height=  this->inPort< Token<int> >("inParam")->read().getData();
  width8 = ((width+7)/8)*8;
  
  /* perform the block rasterisation */
  while(1) {
    //read in the blocks for 8 lines
    for ( col = 0 ; col < width8 ; col += 8 ) {
      for ( row = 0 ; row < 8 ; row++ ) {
	for ( int k = 0 ; k < 8 ; k++ ) {
	  lines [ col + row * width8 + k ]=  this->inPort< Token<int> >("inData")->read().getData();
	}
      }
    }
    for (row=0; row<8; row++) {
      if (count < height) {
	for (col = 0 ; col < width ; col++ ) {
	  Token<int>* pvt=new Token<int>(lines [row * width8 + col]);
	  this->outPort< Token<int> >("outData")->write(*pvt);
	  //output.write(lines [row * width8 + col]);
	}
      }
      count++;  // line done
    }
    if (count >= height) count = 0;
  }

  return NULL;
  
}


#endif
