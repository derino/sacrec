#ifndef INTTOKEN_H
#define INTTOKEN_H

#include "Token.h"

namespace sacre
{

  class IntToken : public Token
  {
  public:
    //IntToken(IntToken&);
    IntToken(int);
    //void operator=(IntToken&);
    int getData();
  protected:
    int data;
  };

  IntToken::IntToken(int d)
    {
      data = d;
    }
  /*
  IntToken::IntToken(IntToken& it)
    {
      data = it.getData();
    }


  void IntToken::operator=(IntToken& it)
    {
      data = it.getData();
      }*/

  int IntToken::getData()
  {
    return data;
  }
}

#endif
