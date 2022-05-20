#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <fstream>
#include "Grade.h"
#include "commonFunctions.h"
namespace yh {
   Grade::Grade(const char* courseCode, int no, const char* title, char type, double score, double fullMark) {
      if (title!= nullptr) {
         strcpy(m_courseCode, courseCode);
         m_no = no;
         m_type = type;
         allocateCopy(m_title, title);
         setScore(score);
         setFullMark(fullMark);
      }
   }

   void Grade::deallocate() {
      delete[] m_title;
      m_title = nullptr;
   }

   Grade::~Grade() {
      deallocate();
   }
   Grade::Grade(const Grade& grade) {
      if (grade.isValid()) {
         operator=(grade);
      }
   }
   Grade& Grade::operator=(const Grade& grade) {
      if (this != &grade) {
         strcpy(m_courseCode, grade.m_courseCode);
         m_no = grade.m_no;
         m_type = grade.m_type;
         allocateCopy(m_title, grade.m_title);
         setScore(grade.m_score);
         setFullMark(grade.m_fullMark);
      }
      return *this;
   }

   Grade& Grade::setInfo(const char* courseCode, int no, const char* title, char type, double score, double fullMark) {
      if (title != nullptr) {
         strcpy(m_courseCode, courseCode);
         m_no = no;
         m_type = type;
         allocateCopy(m_title, title);
         setScore(score);
         setFullMark(fullMark);
      }
      return *this;
   }

   Grade& Grade::setScore(double score) {
      if (score > 0) m_score = score;
      return *this;
   }

   Grade& Grade::setFullMark(double fullMark) {
      if (fullMark > 0) m_fullMark = fullMark;
      return *this;
   }

   const char* Grade::getCourse() const {
      return m_courseCode;
   }
   int Grade::getNo() const {
      return m_no;
   }
   const char* Grade::getTitle() const {
      return m_title;
   }
   double Grade::getScore() const {
      return m_score;
   }
   double Grade::getFullMark() const {
      return m_fullMark;
   }
   char Grade::getType() const {
      return m_type;
   }

   int Grade::getBest() const {
      return m_best;
   }

   void Grade::setBest(int best) {
      m_best = best;
   }

   std::ostream& Grade::display(std::ostream& ostr) const {
      ostr << "Type     | " ;
      if (getType() == 'W') ostr << "Weekly";
      if (getType() == 'Q') ostr << "Quiz";
      if (getType() == 'T') ostr << "Test";
      if (getType() == 'A') ostr << "Assign";
      ostr << std::endl;
      ostr << "No.      | #" << getNo() << std::endl;
      ostr << "Title    | " << getTitle() << std::endl;
      ostr.setf(std::ios::fixed);
      ostr.precision(1);
      ostr << "Score    | " << getScore() << std::endl;
      ostr.precision(0);
      ostr << "Full     | " << getFullMark() << std::endl;
      ostr.unsetf(std::ios::fixed);
      return ostr;
   }

   bool Grade::isValid() const {
      return (m_type == 'T' || m_type == 'Q'|| m_type == 'A' || m_type == 'W') && m_score > 0;
   }
   std::ifstream& Grade::load(std::ifstream& ifstr) {
      ifstr.clear();
      ifstr.get(m_courseCode, 10, ',');
      ifstr.ignore();
      ifstr >> m_no;
      ifstr.ignore();
      ifstr >> m_type;
      ifstr.ignore();
      delete[] m_title;
      m_title = getDynCstr(ifstr, ',');
      ifstr >> m_score;
      ifstr.ignore();
      ifstr >> m_fullMark;
      ifstr.ignore();
      if (ifstr.fail()) {
         ifstr.setstate(std::ios::failbit);
      }
      return ifstr;
   }
   std::istream& Grade::read(std::istream& istr, const char* course) {
      istr.clear();
      delete[] m_title;

      strcpy(m_courseCode, course);
      std::cout << "No. : ";
      istr >> m_no;
      do {
         std::cout << "Type(W|A|Q|T) : ";
         istr >> m_type;
         istr.ignore();
      } while (!(m_type == 'W' || m_type == 'A' || m_type == 'Q' || m_type == 'T'));
      std::cout << "Title : ";
      m_title = getDynCstr(istr, '\n');
      std::cout << "Score : ";
      istr >> m_score;
      do {
         std::cout << "Full Mark : ";
         istr >> m_fullMark;
      } while (m_fullMark < m_score);
      return istr;
   }

   std::ofstream& Grade::save(std::ofstream& ofstr) const {
      ofstr << m_courseCode << ',' << m_no << ',' << m_type<<',' << m_title << ',';
      ofstr.setf(std::ios::fixed);
      ofstr.precision(2);
      ofstr << m_score <<',';
      ofstr << m_fullMark;
      ofstr.unsetf(std::ios::fixed);
      return ofstr;
   }
   std::ostream& operator<<(std::ostream& ostr, const Grade& g) {
      return g.display(ostr);
   }
}



