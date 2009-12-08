#ifndef _INPORT_H_
#define _INPORT_H_

namespace sacre
{

  template <typename T>
    class InPort
    {
    public:
      InPort(std::string _name);
      std::string getName();
      
    protected:
      std::string name;
      
    };
  
  template <typename T>
    InPort<T>::InPort(std::string _name): name(_name)
  {
  }
  
  template <typename T>
    std::string InPort<T>::getName()
    {
      return name;
    };
  
}

#endif /* _INPORT_H_ */
  
