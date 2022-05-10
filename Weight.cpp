#define _CRT_SECURE_NO_WARNINGS
#include <fstream>
#include <cstring>
#include "Weight.h"
namespace yh {
   Weight::Weight(const Weight& weight) {
      operator=(weight);
   }
   Weight& Weight::operator=(const Weight& weight) {
      if (this != &weight) {
         m_equal = weight.m_equal;
         strcpy(m_course, weight.m_course);
         m_type = weight.m_type;
         strcpy(m_require, weight.m_require);
         m_totalWeight = weight.m_totalWeight;
         m_count = weight.m_count;
         m_max = weight.m_max;
      }
      return *this;
   }
   char Weight::getType() const {
      return m_type;
   }
   const char* Weight::getCourse() const {
      return m_course;
   }
   const char* Weight::getRequireName() const {
      return m_require;
   }

   double Weight::getTotalWeight() const {
      return m_totalWeight;
   }

   int Weight::getCount() const {
      return m_count;
   }

   int Weight::getMax() const {
      return m_max;
   }
   double Weight::calculateWeight(int no) {
      return m_totalWeight/m_count;
   }
   std::ifstream& Weight::load(std::ifstream& ifstr) {
      ifstr.clear();
      ifstr >> m_equal;
      ifstr.ignore();
      ifstr.get(m_course, 10, ',');
      ifstr.ignore();
      ifstr >> m_type;
      ifstr.ignore();
      ifstr.get(m_require, 15, ',');
      ifstr.ignore();
      ifstr >> m_totalWeight;
      ifstr.ignore();
      ifstr >> m_count;
      ifstr.ignore();
      ifstr >> m_max;
      ifstr.ignore();
      while (ifstr.peek() == ',') ifstr.ignore();
      if (ifstr.peek() == '\n') ifstr.ignore();
      if (ifstr.fail()) {
         ifstr.setstate(std::ios::failbit);
      }
      return ifstr;
   }

   std::ostream& Weight::display(std::ostream& ostr) const {
      ostr.setf(std::ios::fixed);
      ostr.precision(0);
      ostr << " " << m_require << " : " << m_totalWeight << "% ( " << m_count << "/" << m_max << " )" << std::endl;
      ostr.unsetf(std::ios::fixed);
      return ostr;
   }

}