// Create, Read, Update, Delete
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdio>
#include <cstring>
#include <iomanip>
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
      ostr.setf(ios::fixed);
      ostr.precision(3);
      ostr << "Weighted | ";
      ostr.setf(ios::fixed);
      ostr.precision(3);
      //if (getType() == 'Q') {
      //   cout << quizEachWeight;
      //}
      //else if (getType() == 'A') {
      //   cout << assignEachWeight;
      //}
      //else if (getType() == 'T') {
      //   cout << testEachWeight;
      //}
      ostr.unsetf(ios::fixed);
      ostr << endl;
      ostr << "---------------------" << endl;
      ostr.precision(3);
      //cout << "Total    | " << getWeightedScore() <<  " % " << endl;
      ostr.unsetf(ios::fixed);
      ostr << endl;
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
   ////------------------------------------------------------------
   //// Read Weight Setting on the course
   //void readWeightSetting(const char* searchCourse) {
   //   char subject[10] = { '\0' };
   //   double tempOneQuizWeight = 0;
   //   double tempAllQuizWeight = 0;
   //   double tempOneAssignWeight = 0;
   //   double tempAllAssignWeight = 0;
   //   double tempOneTestWeight = 0;
   //   double tempAllTestWeight = 0;
   //   //ifstream file;     
   //   //file.open("assessmentWeight.csv");
   //   FILE* fptr = nullptr;
   //   fptr = fopen("assessmentWeight.csv", "r");
   //   if(fptr!=nullptr) {
   //   //if (file.is_open()) {
   //      //while(file){ 
   //      while (fscanf(fptr, "%[^,],%lf,%lf,%lf,%lf,%lf,%lf\n", subject, &tempOneQuizWeight, &tempAllQuizWeight, &tempOneAssignWeight, &tempAllAssignWeight, &tempOneTestWeight, &tempAllTestWeight) == 7) {
   //         if (strstr(subject, searchCourse) != nullptr) {
   //            //file >> subject;
   //            //file >> quizEachWeight;
   //            //file >> quizAllWeight;
   //            //file >> assignEachWeight;
   //            //file >> assignAllWeight;
   //            //file >> testEachWeight;
   //            //file >> testAllWeight;
   //            quizEachWeight = tempOneQuizWeight;
   //            quizAllWeight = tempAllQuizWeight;
   //            assignEachWeight = tempOneAssignWeight;
   //            assignAllWeight = tempAllAssignWeight;
   //            testEachWeight = tempOneTestWeight;
   //            testAllWeight = tempAllTestWeight;
   //         }
   //      }
   //      fclose(fptr);
   //      //file.close();
   //      fptr = nullptr;
   //   }
   //   else {
   //      cout << "--- ERROR: WEIGHT SETTING FILE INACCESIBLE";
   //   }
   //}
   //
   std::ostream& operator<<(std::ostream& ostr, const Grade& g) {
      return g.display(ostr);
   }
   //std::ostream& displayQuiz(const char* searchCourse, const int numGrades) {
   //   double sumQuiz = 0;
   //   if (numGrades > 0) {
   //      cout << "*** " << searchCourse << " ***" << endl << endl;
   //      cout << "Week       | ";
   //      for (int i = 0; i < numGrades; i++) {
   //         if (grades[i].isValid() && grades[i].getType()=='Q') {
   //            cout << setw(7);
   //            cout << "#" << grades[i].getWeek();
   //         }
   //      }
   //      cout << endl;
   //      cout << "Title      | ";
   //      for (int i = 0; i < numGrades; i++) {
   //         if (grades[i].isValid() && grades[i].getType() == 'Q') {
   //            cout << setw(8);
   //            cout << grades[i].getTitle();
   //         }
   //      }
   //      cout << endl;

   //      cout << "Score      | ";
   //      for (int i = 0; i < numGrades; i++) {
   //         if (grades[i].isValid() && grades[i].getType() == 'Q') {
   //            cout << setw(6);
   //            cout << grades[i].getScore() << "/" << grades[i].getFullMark();
   //         }
   //      }
   //      cout << endl;
   //      cout << "Weighted   | ";
   //      for (int i = 0; i < numGrades; i++) {
   //         if (grades[i].isValid() && grades[i].getType() == 'Q') {
   //            cout.setf(ios::fixed);
   //            cout.precision(3);
   //            cout << setw(8);
   //            cout << quizEachWeight;
   //            cout.unsetf(ios::fixed);
   //         }
   //      }
   //      cout << endl;
   //      cout << "---------------------" << endl;
   //      cout << "Grade      | ";
   //      for (int i = 0; i < numGrades; i++) {
   //         if (grades[i].isValid() && grades[i].getType() == 'Q') {
   //            cout.setf(ios::fixed);
   //            cout.precision(3);
   //            cout << setw(8);
   //            cout << grades[i].getWeightedScore();
   //            cout.unsetf(ios::fixed);
   //         }
   //      }
   //      cout << endl;
   //      for (int i = 0; i < numGrades; i++) {
   //         if (grades[i].isValid()) {
   //            if (grades[i].getType() == 'Q') {
   //               sumQuiz += grades[i].getWeightedScore();
   //            }
   //         }
   //      }

   //      cout << endl;
   //      cout.setf(ios::fixed);
   //      cout.precision(2);
   //      cout << "QUIZ       |   " << sumQuiz << "  /  " << quizAllWeight << " %" << endl;
   //      cout.unsetf(ios::fixed);
   //   }
   //   else {
   //      cout << "--- ERROR: No data found. Return to menu." << endl;
   //   }
   //   return cout;
   //}
   //std::ostream& displayAssignment(const char* searchCourse, const int numGrades) {
   //   double sumAssign = 0;
   //   if (numGrades > 0) {
   //      cout << "*** " << searchCourse << " ***" << endl << endl;
   //      cout << "Week       | ";
   //      for (int i = 0; i < numGrades; i++) {
   //         if (grades[i].isValid() && grades[i].getType() == 'A') {
   //            cout << setw(7);
   //            cout << "#" << grades[i].getWeek();
   //         }
   //      }
   //      cout << endl;
   //      cout << "Title      | ";
   //      for (int i = 0; i < numGrades; i++) {
   //         if (grades[i].isValid() && grades[i].getType() == 'A') {
   //            cout << setw(8);
   //            cout << grades[i].getTitle();
   //         }
   //      }
   //      cout << endl;

   //      cout << "Score      | ";
   //      for (int i = 0; i < numGrades; i++) {
   //         if (grades[i].isValid() && grades[i].getType() == 'A') {
   //            cout << setw(6);
   //            cout << grades[i].getScore() << "/" << grades[i].getFullMark();
   //         }
   //      }
   //      cout << endl;
   //      cout << "Weighted   | ";
   //      for (int i = 0; i < numGrades; i++) {
   //         if (grades[i].isValid() && grades[i].getType() == 'A') {
   //            cout.setf(ios::fixed);
   //            cout.precision(3);
   //            cout << setw(8);
   //            cout << assignEachWeight;
   //            cout.unsetf(ios::fixed);
   //         }
   //      }
   //      cout << endl;
   //      cout << "---------------------" << endl;
   //      cout << "Grade      | ";
   //      for (int i = 0; i < numGrades; i++) {
   //         if (grades[i].isValid() && grades[i].getType() == 'A') {
   //            cout.setf(ios::fixed);
   //            cout.precision(3);
   //            cout << setw(8);
   //            cout << grades[i].getWeightedScore();
   //            cout.unsetf(ios::fixed);
   //         }
   //      }
   //      cout << endl;
   //      for (int i = 0; i < numGrades; i++) {
   //         if (grades[i].isValid()) {
   //            if (grades[i].getType() == 'A') {
   //               sumAssign += grades[i].getWeightedScore();
   //            }
   //         }
   //      }

   //      cout << endl;
   //      cout.setf(ios::fixed);
   //      cout.precision(2);
   //      cout << "ASSIGNMENT |   " << sumAssign << "  /  " << assignAllWeight << " %" << endl;
   //      cout.unsetf(ios::fixed);
   //   }
   //   else {
   //      cout << "--- ERROR: No data found. Return to menu." << endl;
   //   }
   //   return cout;
   //}
   //std::ostream& displayTest(const char* searchCourse, const int numGrades) {
   //   double sumTest = 0;
   //   if (numGrades > 0) {
   //      cout << "*** " << searchCourse << " ***" << endl << endl;
   //      cout << "Week       | ";
   //      for (int i = 0; i < numGrades; i++) {
   //         if (grades[i].isValid() && grades[i].getType() == 'T') {
   //            cout << setw(7);
   //            cout << "#" << grades[i].getWeek();
   //         }
   //      }
   //      cout << endl;
   //      cout << "Title      | ";
   //      for (int i = 0; i < numGrades; i++) {
   //         if (grades[i].isValid() && grades[i].getType() == 'T') {
   //            cout << setw(8);
   //            cout << grades[i].getTitle();
   //         }
   //      }
   //      cout << endl;

   //      cout << "Score      | ";
   //      for (int i = 0; i < numGrades; i++) {
   //         if (grades[i].isValid() && grades[i].getType() == 'T') {
   //            cout << setw(6);
   //            cout << grades[i].getScore() << "/" << grades[i].getFullMark();
   //         }
   //      }
   //      cout << endl;
   //      cout << "Weighted   | ";
   //      for (int i = 0; i < numGrades; i++) {
   //         if (grades[i].isValid() && grades[i].getType() == 'T') {
   //            cout.setf(ios::fixed);
   //            cout.precision(3);
   //            cout << setw(8);
   //            cout << testEachWeight;
   //            cout.unsetf(ios::fixed);
   //         }
   //      }
   //      cout << endl;
   //      cout << "---------------------" << endl;
   //      cout << "Grade      | ";
   //      for (int i = 0; i < numGrades; i++) {
   //         if (grades[i].isValid() && grades[i].getType() == 'T') {
   //            cout.setf(ios::fixed);
   //            cout.precision(3);
   //            cout << setw(8);
   //            cout << grades[i].getWeightedScore();
   //            cout.unsetf(ios::fixed);
   //         }
   //      }
   //      cout << endl;
   //      for (int i = 0; i < numGrades; i++) {
   //         if (grades[i].isValid()) {
   //            if (grades[i].getType() == 'T') {
   //               sumTest += grades[i].getWeightedScore();
   //            }
   //         }
   //      }

   //      cout << endl;
   //      cout.setf(ios::fixed);
   //      cout.precision(2);
   //      cout << "TEST       |   " << sumTest << "  /  " << testAllWeight << " %" << endl << endl;
   //      cout.unsetf(ios::fixed);
   //   }
   //   else {
   //      cout << "--- ERROR: No data found. Return to menu." << endl;
   //   }
   //   return cout;
   //}
   //// Display grades with format
   //std::ostream& displayGrades(const char* searchCourse, const int numGrades) {
   //   double total = 0;
   //   double sumQuiz = 0;
   //   double sumAssign = 0;
   //   double sumTest = 0;
   //   if (numGrades > 0) {
   //      cout << "*** " << searchCourse << " ***" << endl << endl;
   //      cout << "Week       | ";
   //      for (int i = 0; i < numGrades; i++) {
   //         if (grades[i].isValid()) {
   //         cout << setw(7);
   //         cout << "#" << grades[i].getWeek();
   //         }
   //      }
   //      cout << endl;
   //      cout << "Title      | ";
   //      for (int i = 0; i < numGrades ; i++) {
   //         if (grades[i].isValid()) {
   //            cout << setw(8);
   //            cout << grades[i].getTitle();
   //         }
   //      }
   //      cout << endl;

   //      cout << "Score      | ";
   //      for (int i = 0; i < numGrades ; i++) {
   //         if (grades[i].isValid()) {
   //            cout << setw(6);
   //            cout << grades[i].getScore() << "/" << grades[i].getFullMark();
   //         }
   //      }
   //      cout << endl;
   //      cout << "Weighted   | ";
   //      for (int i = 0; i < numGrades ; i++) {
   //         if (grades[i].isValid()) {
   //            cout.setf(ios::fixed);
   //            cout.precision(3);
   //            cout << setw(8);
   //            if (grades[i].getType() == 'Q') {
   //               cout << quizEachWeight;
   //            }
   //            else if (grades[i].getType() == 'A') {
   //               cout << assignEachWeight;
   //            }
   //            else if (grades[i].getType() == 'T') {
   //               cout << testEachWeight;
   //            }
   //            cout.unsetf(ios::fixed);
   //         }
   //      }
   //      cout << endl;
   //      cout << "---------------------" << endl;
   //      cout << "Grade      | ";
   //      for (int i = 0; i < numGrades ; i++) {
   //         if (grades[i].isValid()) {
   //            cout.setf(ios::fixed);
   //            cout.precision(3);
   //            cout << setw(8);
   //            cout << grades[i].getWeightedScore();
   //            cout.unsetf(ios::fixed);
   //         }
   //      }
   //      cout << endl;
   //      for (int i = 0; i < numGrades ; i++) {
   //         if (grades[i].isValid()) {
   //            if (grades[i].getType() == 'Q') {
   //               sumQuiz += grades[i].getWeightedScore();
   //            }
   //            else if (grades[i].getType() == 'A') {
   //               sumAssign += grades[i].getWeightedScore();
   //            }
   //            else if (grades[i].getType() == 'T') {
   //               sumTest += grades[i].getWeightedScore();
   //            }
   //         }
   //      }
   //      total = sumQuiz + sumAssign + sumTest;
   //      cout << endl;
   //      cout.setf(ios::fixed);
   //      cout.precision(2);
   //      cout << "QUIZ       |   " << sumQuiz << "  /  " << quizAllWeight << " %" << endl;
   //      cout << "ASSIGNMENT |   " << sumAssign << "  /  " << assignAllWeight << " %" << endl;
   //      cout << "TEST       |   " << sumTest << "  /  " << testAllWeight << " %" << endl << endl;
   //      cout << "TOTAL      |   " << total << "  /  " << (quizAllWeight + assignAllWeight + testAllWeight) << " %" << endl << endl;
   //      cout.unsetf(ios::fixed);
   //   }
   //   else {
   //      cout << "--- ERROR: No data found. Return to menu." << endl;
   //   }
   //   return cout;
   //}

   //void getGradeInput(int& week, char* title, char& type, double& score, double& fullMark) {
   //   do {
   //      cout << "Week         : ";
   //      cin >> week;
   //      if (week < 0 || week > 16) {
   //         cout << "--- ERROR: Week is between 1 and 14" << endl;
   //      }
   //   } while (week < 0 || week > 16);
   //   cout << "Title        : ";
   //   cin.get(title, 20, '\n');
   //   cin.ignore(100, '\n');
   //   do {
   //      cout << "Type (Q|T|A) : ";
   //      cin.get(type);
   //      type=toUpperCharacter(type);
   //      if (!(type == 'Q' || type == 'T' || type == 'A')) {
   //         cout << "--- ERROR: Type must be Q for quiz, T for Test, A for assignment" << endl;
   //      }
   //   } while (!(type == 'Q' || type == 'T' || type == 'A'));
   //   cout << "Score        : ";
   //   cin >> score;
   //   do {
   //      cout << "Out of       : ";
   //      cin >> fullMark;
   //      if (fullMark < score) {
   //         cout << "--- ERROR: full mark need to be bigger than score." << endl;
   //      }
   //   } while (fullMark < score);
   //   cout << endl;
   //}

   //void displayWeightSetting(const char* searchCourse) {
   //   cout << "*** Weight Setting for " << searchCourse << " ***" << endl<<endl;
   //   cout.setf(ios::fixed);
   //   cout.precision(3);
   //   cout << "Each QUIZ(Q)       | " << quizEachWeight << " %" << endl;
   //   cout.unsetf(ios::fixed);
   //   cout << "All  QUIZ(Q)       | " << quizAllWeight << " %" << endl << endl;
   //   cout.setf(ios::fixed);
   //   cout.precision(3);
   //   cout << "Each ASSIGNMENT(A) | " << assignEachWeight << " %" << endl;
   //   cout.unsetf(ios::fixed);
   //   cout << "All  ASSIGNMENT(A) | " << assignAllWeight << " %" << endl << endl;
   //   cout.setf(ios::fixed);
   //   cout.precision(3);
   //   cout << "Each TEST(T)       | " << testEachWeight << " %" << endl;
   //   cout.unsetf(ios::fixed);
   //   cout << "All  TEST(T)       | " << testAllWeight << " %" << endl << endl;
   //}

   //void modifyQuizWeightSetting() {
   //   double inputEachQuiz;
   //   double inputAllQuiz;
   //   char answer;
   //   do { 
   //   cout << "Each Quiz  : ";
   //   cin >> inputEachQuiz;
   //   cout << "All Quiz   : ";
   //   cin >> inputAllQuiz;
   //   cout << endl;

   //   cout << "Change (Y/N)?"<< " >>> ";
   //      cin >> answer;
   //      answer = toUpperCharacter(answer);
   //   } while (answer != 'Y');
   //   if (answer == 'Y') {
   //      quizEachWeight = inputEachQuiz;
   //      quizAllWeight = inputAllQuiz;
   //   }
   //}
   //void modifyAssignWeightSetting() {
   //   double inputEachAssign;
   //   double inputAllAssign;
   //   char answer;
   //   do {
   //      cout << "Each Assignment : ";
   //      cin >> inputEachAssign;
   //      cout << "All Assginment  : ";
   //      cin >> inputAllAssign;
   //      cout << endl;

   //      cout << "Change (Y/N)?" << " >>> ";
   //      cin >> answer;
   //      answer = toUpperCharacter(answer);
   //   } while (answer != 'Y');
   //   if (answer == 'Y') {
   //      assignEachWeight = inputEachAssign;
   //      assignAllWeight = inputAllAssign;
   //   }
   //}
   //void modifyTestWeightSetting() {
   //   double inputEachTest;
   //   double inputAllTest;
   //   char answer;
   //   do {
   //      cout << "Each Test  : ";
   //      cin >> inputEachTest;
   //      cout << "All Test   : ";
   //      cin >> inputAllTest;
   //      cout << endl;

   //      cout << "Change (Y/N)?" << " >>> ";
   //      cin >> answer;
   //      answer = toUpperCharacter(answer);
   //   } while (answer != 'Y');
   //   if (answer == 'Y') {
   //      testEachWeight = inputEachTest;
   //      testAllWeight = inputAllTest;
   //   }
   //}

   //void selectionSort(int numGrades) {
   //   int i, j, min;
   //   Grade temp;
   //   for (i = 0; i < numGrades; i++)
   //   {
   //      min = i;
   //      for (j = i + 1; j < numGrades; j++) {
   //         // if week is same but has Q or A or T
   //         if (grades[j].getWeek() < grades[min].getWeek()) {
   //            min = j;
   //         }
   //      }
   //      if (min != i) {
   //         temp = grades[i];
   //         grades[i] = grades[min];
   //         grades[min] = temp;
   //      }
   //   }
   //}
}



