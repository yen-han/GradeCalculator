#define _CRT_SECURE_NO_WARNINGS
#include <fstream>
#include <cstring>
#include "Weighted.h"
namespace yh {
   Weighted::Weighted(const Weighted& weight) {
      operator=(weight);
   }
   Weighted& Weighted::operator=(const Weighted& weight) {
      if (this != &weight) {
         m_equal = weight.m_equal;
         strcpy(m_course, weight.m_course);
         m_type = weight.m_type;
         strcpy(m_assessName, weight.m_assessName);
         m_totalWeight = weight.m_totalWeight;
         m_count = weight.m_count;
         m_max = weight.m_max;
      }
      return *this;
   }
   char Weighted::getType() const {
      return m_type;
   }
   const char* Weighted::getCourse() const {
      return m_course;
   }
   const char* Weighted::getRequireName() const {
      return m_assessName;
   }

   double Weighted::getTotalWeight() const {
      return m_totalWeight;
   }

   int Weighted::getCount() const {
      return m_count;
   }

   int Weighted::getMax() const {
      return m_max;
   }
   double Weighted::calculateWeight(int no) {
      return m_totalWeight/m_count;
   }
   std::ifstream& Weighted::load(std::ifstream& ifstr) {
      ifstr.clear();
      ifstr >> m_equal;
      ifstr.ignore();
      ifstr.get(m_course, 10, ',');
      ifstr.ignore();
      ifstr >> m_type;
      ifstr.ignore();
      ifstr.get(m_assessName, 15, ',');
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

   std::ostream& Weighted::display(std::ostream& ostr) const {
      ostr.setf(std::ios::fixed);
      ostr.precision(0);
      ostr << " " << m_assessName << " : " << m_totalWeight << "% ( " << m_count << "/" << m_max << " )" << std::endl;
      ostr.unsetf(std::ios::fixed);
      return ostr;
   }

}