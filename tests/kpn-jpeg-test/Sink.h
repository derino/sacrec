//Sink.h
#ifndef SINK_H
#define SINK_H

#include "log4cxx/logger.h"
using namespace log4cxx;

#include <iostream>
#include <fstream>
#include "Component.h"

using namespace sacre;
using namespace std;

class Sink: public Component
{
 public:
  Sink(string);
  virtual void* task(void*);
  ~Sink();

 private:
  ofstream *resultfile;
  // const char* outputfile;
};


Sink::Sink(string _name):Component(_name)
{
  addInPort< Token<int> >("inParam");
  addInPort< Token<int> >("inData");

  resultfile = new ofstream("result.pgm");
  if (!resultfile->is_open())
      LOG4CXX_WARN(Logger::getLogger("application"),
		    this->name << ": Error opening file result.pgm"
		    );
}


Sink::~Sink()
{
  resultfile->close();
  delete resultfile;
}


void* Sink::task(void *nullarg )
{
  unsigned temp;
  unsigned count;
  unsigned width;
  unsigned height;
  
  if (!resultfile->is_open()) 
    return NULL;

  // write PGM identifier                                                                                                                
  *resultfile << "P2" << endl;
  // write width & height                                                                                                                
  width = this->inPort< Token<int> >("inParam")->read().getData();
  *resultfile << width << " ";
  height = this->inPort< Token<int> >("inParam")->read().getData();
  *resultfile << height << endl;
  // write max gray value                                                                                                                
  *resultfile << this->inPort< Token<int> >("inParam")->read().getData() << endl;

  count = 0;
  
  for (unsigned i=0; i< (width*height); i++)
    {
      temp=this->inPort< Token<int> >("inData")->read().getData();
      *resultfile << temp << " ";
      count++;
      if (count == 17)
	{
	  *resultfile << endl;
	  count = 0;
	}
    }
  
  LOG4CXX_DEBUG(Logger::getLogger("application"),
		this->name << "'s ALL TOKENS ARE READ."
		);
  return NULL;
  
}

#endif 
