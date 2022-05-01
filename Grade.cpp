// Create, Read, Update, Delete
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <fstream>
#include "Grade.h"
#include "commonFunctions.h"
using namespace std;
namespace yh {
   Grade& Grade::resetInfo() {
      m_courseCode[0] = '\0';
      m_week = 0;
      m_type = 'N'; // None
      m_title = nullptr;
      m_score = 0; 
      m_fullMark=0;
      return *this;
   }

   Grade::Grade() {
      resetInfo();
   }
 
   Grade::Grade(const char* courseCode, int week, const char* title, char type, double score, double fullMark) {
      resetInfo();
      if (title!= nullptr) {
         strcpy(m_courseCode, courseCode);
         m_week = week;
         m_type = type;
         setTitle(title);
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
      resetInfo();
      if (grade.isValid()) {
         operator=(grade);
      }
   }
   Grade& Grade::operator=(const Grade& grade) {
      if (this != &grade) {
         strcpy(m_courseCode, grade.m_courseCode);
         m_week = grade.m_week;
         m_type = grade.m_type;
         deallocate();
         setTitle(grade.m_title);
         setScore(grade.m_score);
         setFullMark(grade.m_fullMark);
      }
      return *this;
   }
   Grade& Grade::setInfo(const char* courseCode, int week, const char* title, char type, double score, double fullMark) {
      delete[] m_title;
      resetInfo();
      if (title != nullptr) {
         strcpy(m_courseCode, courseCode);
         m_week = week;         
         m_type = type;
         setTitle(title);
         setScore(score);
         setFullMark(fullMark);
      }
      return *this;
   }

   Grade& Grade::setTitle(const char* title) {
      if (title != nullptr) {
         m_title = new char[strlen(title) + 1];
         strcpy(m_title, title);
      }
      return *this;
   }

   Grade& Grade::setScore(double score) {
      if (score > 0) {
         m_score = score;
      }
      return *this;
   }

   Grade& Grade::setFullMark(double fullMark) {
      if (fullMark > 0) {
         m_fullMark = fullMark;
      }
      return *this;
   }

   const char* Grade::getCourse() const {
      return m_courseCode;
   }
   int Grade::getWeek() const {
      return m_week;
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

   ostream& Grade::display(ostream& ostr) const {
      ostr << "Week     | #" << getWeek() << endl;
      ostr << "Type     | " ;
      if (getType() == 'Q') ostr << "Quiz";
      if (getType() == 'T') ostr << "Test";
      if (getType() == 'A') ostr << "Assign";
      cout << endl;
      ostr << "Title    | " << getTitle() <<endl;
      ostr << "Score    | " << getScore() << endl;
      ostr << "Full     | " << getFullMark() << endl;
      return ostr;
   }

   bool Grade::isValid() const {
      return (m_type == 'T' || m_type == 'Q'|| m_type == 'A') && m_score > 0;
   }
   std::ifstream& Grade::load(std::ifstream& ifstr) {
      ifstr.clear();
      ifstr.get(m_courseCode, 10, ',');
      ifstr.ignore();
      ifstr >> m_week;
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
      cout << "Week : ";
      istr >> m_week;
      cout << "Type(Q|T|A) : ";
      istr >> m_type;
      istr.ignore();
      cout << "Title : ";
      m_title = getDynCstr(istr, '\n');
      cout << "Score : ";
      istr >> m_score;
      cout << "Full Mark : ";
      istr >> m_fullMark;
      return istr;
   }

   std::ofstream& Grade::save(std::ofstream& ofstr) const {
      ofstr << m_courseCode << ',' << m_week << ',' << m_type<<',' << m_title << ',';
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



