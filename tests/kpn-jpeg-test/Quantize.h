//QUANTIZE.h
#ifndef QUANTIZE_H
#define QUANTIZE_H

#include "log4cxx/logger.h"
using namespace log4cxx;

#include <iostream>
#include <fstream>
#include <string.h>
#include "Component.h"

using namespace sacre;
using namespace std;


class Quantize: public Component
{
 
 public:
  Quantize(string);
  virtual void* task(void*);
  ~Quantize();
  
  static int quantization[64];
  
  // private:
  //int quantization;
};

 int Quantize::quantization[64]={ 16, 11, 10, 16, 24, 40, 51, 61,
				    12, 12, 14, 19, 26, 58, 60, 55,
				    14, 13, 16, 24, 40, 57, 69, 56,
				    14, 17, 22, 29, 51, 87, 80, 62,
				    18, 22, 37, 56, 68,109,103, 77,
				    24, 35, 55, 64, 81,104,113, 92,
				    49, 64, 78, 87,103,121,120,101,
				    72, 92, 95, 98,112,100,103, 99};


Quantize::Quantize(string _name):Component(_name)
{
  addInPort< Token<float> >("inData");
  addOutPort< Token<int> >("outData");
}


Quantize::~Quantize()
{
  LOG4CXX_DEBUG(Logger::getLogger("application"),
                this->name << " is destructed."
                );
}


void* Quantize::task(void* nullarg)
{
  int		i, j;
  float	value;
  int		temp_out;
  
  while (1) {
    for(i=0;i<8;i++) {
      for (j=0; j<8;j++){
	value = this->inPort< Token<float> >("inData")->read().getData();
	temp_out=(int)(floor(value/quantization[i*8+j]+0.5));
	//				cout << temp_out << " ";
	Token<int>* pvt=new Token<int>(temp_out);
	this->outPort< Token<int> >("outData")->write(*pvt);
	//output.write(temp_out);
      }
      //			cout << endl;
    }
  }

  return NULL;
}

#endif
