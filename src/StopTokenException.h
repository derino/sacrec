#ifndef _STOPTOKENEXCEPTION_H_
#define _STOPTOKENEXCEPTION_H_

#include <exception>

class StopTokenException : public std::exception
{
  virtual const char* what() const throw()
  {
    return "Stop token received!";
  }
};

#endif // _STOPTOKENEXCEPTION_H_
