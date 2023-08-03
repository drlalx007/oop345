#ifndef SDDS_COLLECTION_H
#define SDDS_COLLECTION_H
#include <iostream>
#include "Pair.h"
#include <string>
namespace sdds {

template<class T, size_t CAPACITY>
class Collection {
protected:
 T array[CAPACITY];
 size_t numOfElements{0};
 T dummy{};
public:
 Collection(){}

 virtual ~Collection() {}

 size_t size()const
 {
   return numOfElements;
 }

 void display(std::ostream& ostr = std::cout)const{
    ostr << "----------------------" << std::endl;
    ostr << "|" << " Collection Content " << "|" << std::endl;
    ostr << "----------------------" << std::endl;
    for (size_t i = 0; i < numOfElements; i++) {
    ostr << array[i] << std::endl;
    }
    ostr << "----------------------" << std::endl;
 }

 virtual bool add(const T& item) {
  bool res = false;
  if (numOfElements < CAPACITY) {
   array[numOfElements] = item;
   numOfElements++;
   res = true;
  }
  return res;
 }

 T& operator[](int index) {
  if (index >= 0 && index < numOfElements) {
   return array[index];
  }
  return dummy;
 }

};


template<> Collection<Pair,100>::Collection() {
  Pair a("No Key","No Value");
  dummy = a;

};

}
#endif // !