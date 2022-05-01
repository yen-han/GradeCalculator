#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <cstring>
#include "Requirement.h"

#include "commonFunctions.h"
namespace yh {
   const char* Requirement::getName(int num) const {
      char name[15] = {'\0'};
      if (num == 1) strcpy(name, m_require1);
      if (num == 2) strcpy(name, m_require2);
      if (num == 3) strcpy(name, m_require3);
      return name;
   }
   int Requirement::getCount(int num) const {
       int forCount=0;
       if (num == 1) forCount = m_count1;
       if (num == 2) forCount = m_count2;
       if (num == 3) forCount = m_count3;
       if (num == 4) forCount = m_maxTest;
        return forCount;
    }
    double Requirement::getWeight(int num) const{
       double forCount=0;
       if (num == 1) forCount = m_weight1;
       if (num == 2) forCount = m_weight2;
       if (num == 3) forCount = m_weight3;
       if (num == 4) forCount = m_test;
       return forCount;
    }
    Requirement::Requirement(const Requirement& r) {
         operator=(r);
   }
   Requirement& Requirement::operator=(const Requirement& r) {
      if (this != &r) {
         strcpy(m_courseCode, r.m_courseCode);
         m_overall = r.m_overall;

         strcpy(m_require1, r.m_require1);
         m_weight1 = r.m_weight1;
         m_count1 = r.m_count1;
         m_max1=r.m_max1;

         strcpy(m_require2, r.m_require2);
         m_weight2 = r.m_weight2;
         m_count2 = r.m_count2;
         m_max2 = r.m_max2;

         strcpy(m_require3, r.m_require3);
         m_weight3 = r.m_weight3;
         m_count3 = r.m_count3;
         m_max3 = r.m_max3;
         
         m_test = r.m_test;
         m_maxTest = r.m_maxTest;
         if (r.m_comment1) allocateCopy(m_comment1, r.m_comment1);
         if(r.m_comment2) allocateCopy(m_comment2, r.m_comment2);
      }
      return *this;
   }
   Requirement::~Requirement() {
      delete[] m_comment1;
      delete[] m_comment2;
   }

   const char* Requirement::getCourse() const {
      return m_courseCode;
   }

   double Requirement::getOverall() const {
      return m_overall;
   }

   double Requirement::calculateWeight(char type) {
      double weight = 0;
      if (type == m_type1) {
         weight = (m_weight1 / m_count1);
      }
      else if (type == m_type2) {
         weight = m_weight2/ m_count2;
      }
      else if (type == m_type3) {
         weight = m_weight3 / m_count3;
      }
      else if (type == m_type4) {
         weight = m_test / m_maxTest;
      }
      return weight;
   }

   std::ostream& Requirement::display(std::ostream& ostr) const {
      ostr << std::endl<< "===========================================================" << std::endl;
      ostr << " Course : " << m_courseCode << std::endl;
      ostr << " Overall : "<<m_overall << "% / 100 %" << std::endl;
      if (m_weight1) {
         ostr << " "<<m_require1 << " : " << m_weight1 << "% ( " << m_count1 << "/" << m_max1 <<" )"<< std::endl;
      }
      if (m_weight2) {
         ostr << " " << m_require2 << " : " << m_weight2 << "% ( " << m_count2 << "/" << m_max2 << " )" << std::endl;
      }
      if (m_weight3) {
         ostr << " " << m_require3 << " : " << m_weight3 << "% ( " << m_count3 << "/" << m_max3 << " )" << std::endl;
      }
      ostr <<" Test : " << m_test << "% ( " << m_maxTest << " Tests )" << std::endl;
      if(m_comment1) ostr << " " << m_comment1 << std::endl;
      if (m_comment2) ostr << " " << m_comment2 << std::endl;
      ostr << "===========================================================" << std::endl;
      return ostr;
   }

   std::ifstream& Requirement::load(std::ifstream& ifstr) {
      ifstr.clear();
      ifstr.get(m_courseCode, 10, ',');
      ifstr.ignore();
      ifstr >> m_overall;
      ifstr.ignore();
      ifstr.get(m_require1, 15, ',');
      ifstr.ignore();
      ifstr >> m_type1;
      ifstr.ignore();
      ifstr >> m_weight1;
      ifstr.ignore();
      ifstr >> m_count1;
      ifstr.ignore();
      ifstr >> m_max1;
      ifstr.ignore();
      ifstr >> m_equal1;
      ifstr.ignore();
      ifstr.get(m_require2, 15, ',');
      ifstr.ignore();
      ifstr >> m_type2;
      ifstr.ignore();
      ifstr >> m_weight2;
      ifstr.ignore();
      ifstr >> m_count2;
      ifstr.ignore();
      ifstr >> m_max2;
      ifstr.ignore();
      ifstr >> m_equal2;
      ifstr.ignore();
      if (ifstr.peek() != ',') {
         ifstr.get(m_require3, 15, ',');
         ifstr.ignore();
         ifstr >> m_type3;
         ifstr.ignore();
         ifstr >> m_weight3;
         ifstr.ignore();
         ifstr >> m_count3;
         ifstr.ignore();
         ifstr >> m_max3;
         ifstr.ignore();
         ifstr >> m_equal3;
         ifstr.ignore();
      }
      else {
         ifstr.ignore().ignore().ignore().ignore().ignore().ignore();
      }
      ifstr >> m_test;
      ifstr.ignore();
      ifstr >> m_maxTest;
      ifstr.ignore();
      ifstr >> m_equalTest;
      ifstr.ignore();
      delete[] m_comment1;
      m_comment1 = getDynCstr(ifstr, ',');
      if (ifstr.peek() != '\n') {
         delete[] m_comment2;
         m_comment2 = getDynCstr(ifstr);
      }
      if (ifstr.fail()) {
         ifstr.setstate(std::ios::failbit);
      }
      return ifstr;
   }

   std::ostream& operator<<(std::ostream& ostr, const Requirement& r) {
      return r.display(ostr);
   }
}