//Source.h
#ifndef SOURCE_H
#define SOURCE_H

#include "log4cxx/logger.h"
using namespace log4cxx;

#include <iostream>
#include <fstream>
#include <string.h>
#include "Component.h"

using namespace sacre;
using namespace std;

#define MAXWIDTH 1024

class Source: public Component
{
 
 public:
  Source(string);
  virtual void* task(void*);
  ~Source(); //check if it is necessary to use virtual destructor

 private:
  unsigned maxwidth;
  ifstream *stimulusfile;

};


//another constructor can be implented in Component.h
//includes pointer to file in parameters and maxwidth
Source::Source(string _name) : Component(_name)
{
  //two output ports for parameters and output data
  addOutPort< Token<int> >("outParam");
  addOutPort< Token<int> >("outData");
 
  //set maxwidth
  maxwidth=MAXWIDTH;

  //open file
  stimulusfile = new ifstream("mountain.pgm");
  if (!stimulusfile->is_open()) {
    cout << "Error opening file mountain.pgm "<<endl;  // << _filename << endl;
  } else {
    cout << "Succesfull opened file mountain.pgm "<<endl; // << _filename << endl;
  }

}


Source::~Source()
{
  //close file in destructor
  stimulusfile->close();
  LOG4CXX_DEBUG(Logger::getLogger("application"),
                this->name << " is destructed."
                );
}


void* Source::task(void* nullarg)
{
  
  char buffer[10];
  unsigned width, height, value;
  
  if (!stimulusfile->is_open())
    return NULL;
  
  // read in PGM identifier                                                                                                              
  *stimulusfile >> buffer;
  if (strcmp(buffer,"P2")) {
    cout << "no greyscale PGM file" << endl;
    return NULL;
  }
  // does not support comment lines in image file!                                                                                       
  // read in and put out width and height                                                                                                
  *stimulusfile >> width;
  if (width > maxwidth) {
    cout << "width of image " << width << " larger than maximum width " << maxwidth << endl;
    return NULL;
  }
  Token<int>* wt=new Token<int>(width);
  this->outPort< Token<int> >("outParam")->write(*wt);

  *stimulusfile >> height;
  Token<int>* ht=new Token<int>(height);
  this->outPort< Token<int> >("outParam")->write(*ht);

  // read in and put out max gray value                                                                                                  
  *stimulusfile >> value;
  Token<int>* vt=new Token<int>(value);
  this->outPort< Token<int> >("outParam")->write(*vt);

  cout << "inputfile:: width: " << width<< " height: " << height<< " greyvalue: " << value << endl;

  unsigned pixels = 0;
  while (pixels < width*height)
    {
      if (stimulusfile->eof())
	{
	  cout << "error file of wrong length" << endl;
	  break;
	}
      pixels++;
      *stimulusfile >> value;
      Token<int>* pvt=new Token<int>(value);
      this->outPort< Token<int> >("outData")->write(*pvt);
    }
  
  LOG4CXX_DEBUG(Logger::getLogger("application"),
		this->name << "'s ALL TOKENS ARE WRITTEN."
		);
  return NULL;
}

#endif
