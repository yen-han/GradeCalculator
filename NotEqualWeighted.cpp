#include <iostream>
#include <fstream>
#include "NotEqualWeighted.h"
namespace yh {
   NotEqualWeighted::NotEqualWeighted(const NotEqualWeighted& nweight) {
      operator=(nweight);
   }

   NotEqualWeighted& NotEqualWeighted::operator=(const NotEqualWeighted& nweight) {
      if (this != &nweight) {
         Weighted::operator=(nweight);
         for (int i = 0; nweight.m_eachWeight[i] != 0 && i < 15; i++) {
            m_eachWeight[i] = nweight.m_eachWeight[i];
         }
      }
      return *this;
   }

   double NotEqualWeighted::calculateWeight(int no) {
      return m_eachWeight[no-1];
   }

   std::ifstream& NotEqualWeighted::load(std::ifstream& ifstr) {
      Weighted::load(ifstr);
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

   std::ostream& NotEqualWeighted::display(std::ostream& ostr) const {
      Weighted::display(ostr);
      if (!m_equal) {
         ostr.setf(std::ios::fixed);
         ostr.precision(0);
         for (int i = 0; m_eachWeight[i] != 0 && i < 15; i++) {
            std::cout << "  - " << Weighted::getRequireName() << " " << i + 1 << ": " << m_eachWeight[i] << "%" << std::endl;
         }
         ostr.unsetf(std::ios::fixed);
      }
      return ostr;
   }

}