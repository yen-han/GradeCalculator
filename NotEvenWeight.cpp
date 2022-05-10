#include <iostream>
#include <fstream>
#include "NotEvenWeight.h"
namespace yh {
   NotEvenWeight::NotEvenWeight(const NotEvenWeight& weight) {
      operator=(weight);
   }

   NotEvenWeight& NotEvenWeight::operator=(const NotEvenWeight& weight) {
      if (this != &weight) {
         Weight::operator=(weight);
         for (int i = 0; weight.m_eachWeight[i]!=0 && i < 15; i++) {
            m_eachWeight[i] = weight.m_eachWeight[i];
         }
      }
      return *this;
   }

   double NotEvenWeight::calculateWeight(int no) {
      return m_eachWeight[no-1];
   }

   std::ifstream& NotEvenWeight::load(std::ifstream& ifstr) {
      Weight::load(ifstr);
      for (int i = 0; ifstr.peek() != '\n' && i < 15; i++) {
         ifstr >> m_eachWeight[i];
         while (ifstr.peek() == ',') ifstr.ignore();
      }
      ifstr.ignore();
      if (ifstr.fail()) {
         ifstr.setstate(std::ios::failbit);
      }
      return ifstr;
   }

   std::ostream& NotEvenWeight::display(std::ostream& ostr) const {
      Weight::display(ostr);
      if (!m_equal) {
         ostr.setf(std::ios::fixed);
         ostr.precision(0);
         for (int i = 0; m_eachWeight[i]!=0 && i < 15; i++) {
            std::cout << "  - " << Weight::getRequireName() << " " << i + 1 << ": " << m_eachWeight[i] << "%" << std::endl;
         }
         ostr.unsetf(std::ios::fixed);
      }
      return ostr;
   }

}