#ifndef TOKEN_H
#define TOKEN_H

#include "log4cxx/logger.h"
using namespace log4cxx;

namespace sacre
{

  enum TokenType { STOP_TOKEN, DATA_TOKEN, VIRTUAL_TOKEN, FAULT_PRESENT_TOKEN, NO_FAULT_TOKEN };
  
  template <typename T>
  class Token
  {
  public:
    Token();
    Token(T);
    Token(TokenType);    
    bool isStop();
    bool isFaultPresentToken();
    T getData();

  protected:
    TokenType type;
    T data;
  };

  template <typename T>
    Token<T>::Token()
    {
      type = DATA_TOKEN;
      this->data = NULL;
    }
  
  template <typename T>
    Token<T>::Token(T data)
    {
      type = DATA_TOKEN;
      this->data = data;
    }
  
  template <typename T>
    Token<T>::Token(TokenType type)
    {
      this->type = type;
      data = NULL;
    }

  template <typename T>
    bool Token<T>::isStop()
    {
      return type == STOP_TOKEN;
    }

  template <typename T>
    bool Token<T>::isFaultPresentToken()
    {
      return type == FAULT_PRESENT_TOKEN;
    }

  template <typename T>
    T Token<T>::getData()
    {
      return data;
    }

}

#endif
