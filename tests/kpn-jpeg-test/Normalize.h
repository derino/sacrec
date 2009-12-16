//NORMALIZE.h
#ifndef NORMALIZE_H
#define NORMALIZE_H

#include "log4cxx/logger.h"
using namespace log4cxx;

#include <iostream>
#include <fstream>
#include <string.h>
#include "Component.h"

using namespace sacre;
using namespace std;


class Normalize: public Component
{
 
 public:
  Normalize(string);
  virtual void* task(void*);
  ~Normalize();
  
  static int quantization[64];
  //private:
  //int* quantization;
};

int Normalize::quantization[64]={ 16, 11, 10, 16, 24, 40, 51, 61,
				  12, 12, 14, 19, 26, 58, 60, 55,
				  14, 13, 16, 24, 40, 57, 69, 56,
				  14, 17, 22, 29, 51, 87, 80, 62,
				  18, 22, 37, 56, 68,109,103, 77,
				  24, 35, 55, 64, 81,104,113, 92,
				  49, 64, 78, 87,103,121,120,101,
				  72, 92, 95, 98,112,100,103, 99};


Normalize::Normalize(string _name):Component(_name)
{
  addInPort< Token<int> >("inData");
  addOutPort< Token<float> >("outData");
}

Normalize::~Normalize()
{
  LOG4CXX_DEBUG(Logger::getLogger("application"),
                this->name << " is destructed."
                );
}


void* Normalize::task(void* nullarg)
{
  int		i, j;
  int		value;
  float		temp_out;
  
  while (1) {
    for(i=0;i<8;i++) {
      for (j=0; j<8;j++){
	value = this->inPort< Token<int> >("inData")->read().getData();
	temp_out=value * quantization[i*8+j];
	//cout << temp_out << " ";
	Token<float>* pvt=new Token<float>(temp_out);
	this->outPort< Token<float> >("outData")->write(*pvt);
	//	output.write(temp_out);
      }
      //cout << endl;
    }
  }

  return NULL;
}


#endif
