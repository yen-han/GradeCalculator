#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <cstring>
#include "Requirement.h"
#include "commonFunctions.h"
namespace yh {
    Requirement::Requirement(const Requirement& r) {
       m_policy1 = nullptr;
       m_policy2 = nullptr;
         operator=(r);
   }
   Requirement& Requirement::operator=(const Requirement& r) {
      if (this != &r) {
         strcpy(m_courseCode, r.m_courseCode);
         m_overall = r.m_overall;
         if (r.m_policy1) allocateCopy(m_policy1, r.m_policy1);
         if(r.m_policy2) allocateCopy(m_policy2, r.m_policy2);
      }
      return *this;
   }
   Requirement::~Requirement() {
      delete[] m_policy1;
      delete[] m_policy2;
   }

   const char* Requirement::getCourse() const {
      return m_courseCode;
   }

   double Requirement::getOverall() const {
      return m_overall;
   }

   std::ostream& Requirement::displayTop(std::ostream& ostr) const {
      seperatorDouble(ostr, 60);
      ostr << " Course : " << m_courseCode << std::endl;
      ostr.setf(std::ios::fixed);
      ostr.precision(0);
      ostr << " Overall : "<< m_overall << "% / 100 %" << std::endl;
      ostr.unsetf(std::ios::fixed);
      return ostr;
   }

   std::ostream& Requirement::displayBottom(std::ostream& ostr) const {
      if (m_policy1) ostr << " " << m_policy1 << std::endl;
      if (m_policy2) ostr << " " << m_policy2 << std::endl;
      seperatorDouble(ostr, 60);
      return ostr;
   }

   std::ifstream& Requirement::load(std::ifstream& ifstr) {
      ifstr.clear();
      ifstr.get(m_courseCode, 10, ',');
      ifstr.ignore();
      ifstr >> m_overall;
      ifstr.ignore();
      delete[] m_policy1;
      m_policy1 = getDynCstr(ifstr, ',');
      delete[] m_policy2;
      m_policy2 = nullptr;
      if (ifstr.peek() != '\n') {
         m_policy2 = getDynCstr(ifstr);
      }
      else {
         ifstr.ignore();
      }
      if (ifstr.fail()) {
         ifstr.setstate(std::ios::failbit);
      }
      return ifstr;
   }

}