//R2B.h
#ifndef R2B_H
#define R2B_H

#include "log4cxx/logger.h"
using namespace log4cxx;

#include <iostream>
#include <fstream>
#include <string.h>
#include "Component.h"

using namespace sacre;
using namespace std;

//#define MAXWIDTH 1024;

class R2B: public Component
{
 
 public:
  R2B(string);
  virtual void* task(void*);
  ~R2B();

 private:
  int maxwidth;
  int* lines;
};

R2B::R2B(string _name): Component(_name)
{
  addInPort< Token<int> >("inParam");
  addInPort< Token<int> >("inData");
  addOutPort< Token<int> >("outData");
  
  //set maxwidth
  maxwidth=MAXWIDTH;
  int maxwidth8  = (maxwidth +7)/8 * 8;   // round up to multiples of 8
  lines = new int[maxwidth8 * 8];	// we need 8 lines before outputting
}

R2B::~R2B()
{
  LOG4CXX_DEBUG(Logger::getLogger("application"),
                this->name << " is destructed."
                );
  delete [] lines;
}

void* R2B::task(void* nullarg)
{
  int		in1;
  int		row, col;

  int		count = 0;			// number of lines read in
  int		width, height, width8;		// the actual width and height of the picture
  
  /* read first the parameters */
  width = this->inPort< Token<int> >("inParam")->read().getData();
  height= this->inPort< Token<int> >("inParam")->read().getData();
  width8 = ((width+7)/8)*8;
  
  while(1) {
    for (row=0; row<8; row++) {
      if (count < height) {
	for (col = 0 ; col < width8 ; col++ ) {
	  if (col < width) 
	    in1 = this->inPort< Token<int> >("inData")->read().getData();//repeat last values
	  lines [row * width8 + col] = in1;
	}
      }
      else {
	for (col = 0; col < width8; col++ ) {
	  lines [row * width8 + col] = lines [(row-1) * width8 + col];
	}
      }
      count++;  // line done
    }
    if (count >= height) count = 0;
    
    //-- when 8 lines read, output blocks
    for ( col = 0 ; col < width8 ; col += 8 ) {
      for ( row = 0 ; row < 8 ; row++ ) {
	for ( int k = 0 ; k < 8 ; k++ ) {
	  Token<int> pvt(lines [ col + row * width8 + k ]);
	  this->outPort< Token<int> >("outData")->write(pvt);
	  // output.write (lines [ col + row * width8 + k ]);
	}
      }
    }
  }

  // this delete is not useful because task always exits with StopTokenException
  delete [] lines;
  return NULL;
}


#endif
