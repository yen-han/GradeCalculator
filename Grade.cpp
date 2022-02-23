// Create, Read, Update, Delete
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdio>
#include <cstring>
#include <iomanip>
#include "Grade.h"
#include "commonFunctions.h"
using namespace std;
namespace yh {
   // Set assessement Weight
   double eachWeight;
   double allWeight;
   double quizEachWeight = 1;
   double quizAllWeight;
   double assignEachWeight = 1;
   double assignAllWeight;
   double testEachWeight = 1;
   double testAllWeight;
   Grade* grades = nullptr;

   Grade& Grade::resetInfo() {
      m_courseCode[0] = '\0';
      m_week = 0;
      m_title=nullptr;
      m_score=-1; // possibly 0
      m_fullMark=0;
      m_type = 'N'; // None
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
         setTitle(title);
         m_type = type;
         setScore(score);
         setFullMark(fullMark);
         m_type = type;
      }
   }

   void Grade::deallocate() {
      delete[] m_title;
      m_title = nullptr;

   }

   Grade::~Grade() {
      deallocate();
   }
   Grade::Grade(const Grade& toCopyFrom) {
      strcpy(m_courseCode, toCopyFrom.m_courseCode);
      m_week = toCopyFrom.m_week;
      deallocate();
      setTitle(toCopyFrom.m_title);
      setScore(toCopyFrom.m_score);
      setFullMark(toCopyFrom.m_fullMark);
      m_type = toCopyFrom.m_type;
    
   }
   Grade& Grade::operator=(const Grade& toCopyFrom) {
      if (this != &toCopyFrom) {
         strcpy(m_courseCode, toCopyFrom.m_courseCode);
         m_week = toCopyFrom.m_week;
         deallocate();
         setTitle(toCopyFrom.m_title);
         setScore(toCopyFrom.m_score);
         setFullMark(toCopyFrom.m_fullMark);
         m_type = toCopyFrom.m_type;
      }
      return *this;
   }
   Grade& Grade::setInfo(const char* courseCode, int week, const char* title, char type, double score, double fullMark) {
      delete[] m_title;
      resetInfo();
      if (title != nullptr) {
         strcpy(m_courseCode, courseCode);
         m_week = week;
         setTitle(title);
         setScore(score);
         setFullMark(fullMark);
         m_type = type;
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
      if (fullMark > 0 && fullMark<=100) {
         m_fullMark = fullMark;
      }
      return *this;
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

   double Grade::getWeightedScore() const {
      if (m_type == 'Q') {
         eachWeight = quizEachWeight;
         allWeight = quizAllWeight;
      }
      else if (m_type == 'A') {
         eachWeight = assignEachWeight;
         allWeight = assignAllWeight;
      }
      else if (m_type == 'T') {
         eachWeight = testEachWeight;
         allWeight = testAllWeight;
      }
      return (m_score/ m_fullMark * eachWeight); 
   }

   ostream& Grade::display() const {
      cout << "Week     | #" << getWeek() << endl;
      cout << "Title    | " << getTitle() <<endl;
      cout << "Score    | " << getScore() << endl;
      cout << "Out of   | " << getFullMark() << endl;
      cout.setf(ios::fixed);
      cout.precision(3);
      cout << "Weighted | ";
      cout.setf(ios::fixed);
      cout.precision(3);
      if (getType() == 'Q') {
         cout << quizEachWeight;
      }
      else if (getType() == 'A') {
         cout << assignEachWeight;
      }
      else if (getType() == 'T') {
         cout << testEachWeight;
      }
      cout.unsetf(ios::fixed);
      cout << endl;
      cout << "---------------------" << endl;
      cout.precision(3);
      cout << "Total    | " << getWeightedScore() <<  " % " << endl;
      cout.unsetf(ios::fixed);
      cout << endl;
      return cout;
   }

   bool Grade::isValid() const {
      return (m_type == 'T' || m_type == 'Q'|| m_type == 'A') && m_score>0;
   }
   //------------------------------------------------------------
   void readWeightSetting(const char* searchCourse) {
      char subject[10] = { '\0' };
      double tempOneQuizWeight = 0;
      double tempAllQuizWeight = 0;
      double tempOneAssignWeight = 0;
      double tempAllAssignWeight = 0;
      double tempOneTestWeight = 0;
      double tempAllTestWeight = 0;

      FILE* fptr = nullptr;
      fptr = fopen("assessmentWeight.csv", "r");
      if (fptr != nullptr) {
         while (fscanf(fptr, "%[^,],%lf,%lf,%lf,%lf,%lf,%lf\n", subject, &tempOneQuizWeight, &tempAllQuizWeight, &tempOneAssignWeight, &tempAllAssignWeight, &tempOneTestWeight, &tempAllTestWeight) == 7) {
            if (strstr(subject, searchCourse) != nullptr) {
               quizEachWeight = tempOneQuizWeight;
               quizAllWeight = tempAllQuizWeight;
               assignEachWeight = tempOneAssignWeight;
               assignAllWeight = tempAllAssignWeight;
               testEachWeight = tempOneTestWeight;
               testAllWeight = tempAllTestWeight;
            }
         }
         fclose(fptr);
         fptr = nullptr;
      }
      else {
         cout << ">>>ERROR: WEIGHT SETTING FILE INACCESIBLE";
      }
   }

   int readGrades(double& totalScore, const char* searchCourse) {
      int numGrades = 0;
      bool found = false;
      FILE* fptr = nullptr;
      fptr = fopen("grade.csv", "r");
      if (fptr != nullptr) {
         // Read comma deliminated file
         char title[20];
         char subject[20] = { '\0' };
         char type;
         int week;
         double score = 0, fullMark = 0;
         int sizeGrades = 5;
         grades = new Grade[static_cast<__int64>(sizeGrades)];

         while (fscanf(fptr, "%[^,],%[^,],%d,%c,%lf,%lf\n", subject, title, &week, &type, &score, &fullMark) == 6) {
            if (strstr(subject, searchCourse) != nullptr){ 
               found = true;
               if (numGrades == sizeGrades) {
                  Grade* tempGrades = nullptr;
                  tempGrades = new Grade[static_cast<__int64>(sizeGrades) + numGrades];
                  for (int i = 0; i < sizeGrades; i++) {
                     tempGrades[i] = grades[i]; // copy assignment needed
                  }
                  delete[] grades;
                  grades = tempGrades;
                  sizeGrades += numGrades;
               }
               grades[numGrades].setInfo(searchCourse, week, title, type, score, fullMark);
               numGrades++;
            }
         }
         // Close file
         fclose(fptr);
         fptr = nullptr;
         if (found) {
            for (int i = 0; i < numGrades; i++) {
               totalScore += grades[i].getWeightedScore();
            }
         }
         else {
            cout << endl;
            cout << ">>> ERROR: Check Course Code" << endl << endl;
         }
      }
      else {
         cout << "ERROR: GRADE FILE INACCESIBLE";
      }
      return numGrades;
   }

   std::ostream& displayGrades(const char* searchCourse, const int numGrades) {
      double total = 0;
      double sumQuiz = 0;
      double sumAssign = 0;
      double sumTest = 0;
      if (numGrades > 0) {
         cout << "<< " << searchCourse << " >>" << endl;
         cout << "Week       | ";
         for (int i = 0; i < numGrades; i++) {
            if (grades[i].isValid()) {
            cout << setw(7);
            cout << "#" << grades[i].getWeek();
            }
         }
         cout << endl;
         cout << "Title      | ";
         for (int i = 0; i < numGrades ; i++) {
            if (grades[i].isValid()) {
               cout << setw(8);
               cout << grades[i].getTitle();
            }
         }
         cout << endl;

         cout << "Score      | ";
         for (int i = 0; i < numGrades ; i++) {
            if (grades[i].isValid()) {
               cout << setw(6);
               cout << grades[i].getScore() << "/" << grades[i].getFullMark();
            }
         }
         cout << endl;
         cout << "Weighted   | ";
         for (int i = 0; i < numGrades ; i++) {
            if (grades[i].isValid()) {
               cout.setf(ios::fixed);
               cout.precision(3);
               cout << setw(8);
               if (grades[i].getType() == 'Q') {
                  cout << quizEachWeight;
               }
               else if (grades[i].getType() == 'A') {
                  cout << assignEachWeight;
               }
               else if (grades[i].getType() == 'T') {
                  cout << testEachWeight;
               }
               cout.unsetf(ios::fixed);
            }
         }
         cout << endl;
         cout << "---------------------" << endl;
         cout << "Grade      | ";
         for (int i = 0; i < numGrades ; i++) {
            if (grades[i].isValid()) {
               cout.setf(ios::fixed);
               cout.precision(3);
               cout << setw(8);
               cout << grades[i].getWeightedScore();
               cout.unsetf(ios::fixed);
            }
         }
         cout << endl;
         for (int i = 0; i < numGrades ; i++) {
            if (grades[i].isValid()) {
               if (grades[i].getType() == 'Q') {
                  sumQuiz += grades[i].getWeightedScore();
               }
               else if (grades[i].getType() == 'A') {
                  sumAssign += grades[i].getWeightedScore();
               }
               else if (grades[i].getType() == 'T') {
                  sumTest += grades[i].getWeightedScore();
               }
            }
         }
         total = sumQuiz + sumAssign + sumTest;
         cout << endl;
         cout.setf(ios::fixed);
         cout.precision(2);
         cout << "QUIZ       |   " << sumQuiz << "  /  " << quizAllWeight << " %" << endl;
         cout << "ASSIGNMENT |   " << sumAssign << "  /  " << assignAllWeight << " %" << endl;
         cout << "TEST       |   " << sumTest << "  /  " << testAllWeight << " %" << endl << endl;
         cout << "TOTAL      |   " << total << "  /  " << (quizAllWeight + assignAllWeight + testAllWeight) << " %" << endl << endl;
         cout.unsetf(ios::fixed);
      }
      else {
         cout << "No data found. Return to menu." << endl;
      }
      return cout;
   }

   void modifyWeightSettingMenu(const char* searchCourse) {
      int input;
      bool exit;
      do {

         cout << searchCourse << "Weight Setting" << endl;
         cout << "=============================" << endl;
         cout.setf(ios::fixed);
         cout.precision(3);
         cout << "Each quiz weight : " << quizEachWeight << " %" << endl;
         cout.unsetf(ios::fixed);
         cout << "Total quiz weight: " << quizAllWeight << " %" << endl << endl;
         cout.setf(ios::fixed);
         cout.precision(3);
         cout << "Each Assignment weight : " << assignEachWeight << " %" << endl;
         cout.unsetf(ios::fixed);
         cout << "Total Assignment weight: " << assignAllWeight << " %" << endl << endl;
         cout.setf(ios::fixed);
         cout.precision(3);
         cout << "Each Test weight : " << testEachWeight << " %" << endl;
         cout.unsetf(ios::fixed);
         cout << "Total Test weight: " << testAllWeight << " %" << endl << endl;

         exit = false;
         cout << "=======================" << endl;
         cout << "1. Modify quiz setting" << endl;
         cout << "2. Modify Assignment setting" << endl;
         cout << "3. Modify Test setting" << endl;
         cout << "0. Exit" << endl;
         cout << ">>> ";
         cin >> input;
         cout << endl;
         switch (input) {
         case 1:
            break;
         case 2:
            break;
         case 3:
            break;
         case 0:
            exit = true;
            break;
         }
      } while (input != 0);
   }  

   void insertGrades(const char* searchCourse, int& numGrades) {
      int week;
      char type, answer;
      char title[20];
      double score, fullMark;
      double total = 0;
      do {
         cout << searchCourse << endl;
         do {
            cout << "Week         : ";
            cin >> week;
            if (week < 0 || week > 16) {
               cout << ">>>ERROR: Week is between 1 and 14" << endl;
            }
         } while (week<0 || week > 16);
         cout <<    "Title        : ";
         cin >> title;
         do {
            cout << "Type (Q|T|A) : ";
            cin >> type;
            if (!(type == 'Q' || type == 'T' || type == 'A')) {
               cout << ">>>ERROR: type can be Q for quiz, T for Test, A for assignment" << endl;
            }
         } while (!(type == 'Q' || type == 'T' || type == 'A'));
         cout << "Score        : ";
         cin >> score;
         do {
            cout << "Out of       : ";
            cin >> fullMark;
            if (fullMark < score) {
               cout << ">>>ERROR: full mark need to be bigger than score." << endl;
            }
         } while (fullMark < score);
         cout << endl;
         grades[numGrades].setInfo(searchCourse, week, title, type, score, fullMark);
         numGrades++;
         cout << "Have more? (Y|N)";
         cin >> answer;
      } while (answer=='Y' || answer=='y');

      displayGrades(searchCourse, numGrades );
      cout << endl;
   }

   void updateGrades(const char* searchCourse, int& numGrades) {
      int inputWeek, i, foundIndex=-1;
      char inputType;
      char answer;

      do {
         cout << endl;
         cout << "Week : ";
         cin >> inputWeek;
         cout << "Type : ";
         cin >> inputType;
         cout << endl;
         for (i = 0; i < numGrades; i++) {
            if (grades[i].getWeek() == inputWeek && grades[i].getType() == inputType) {
               grades[i].display();
               foundIndex = i;
            }
         }
         cout << "Update the grade? (Q to quit)" << endl << ">>>";
         cin >> answer;
      } while (!answer == 'Y' || !answer=='Q');
      if (answer != 'Q') {
         int week;
         char type;
         char title[20];
         double score, fullMark;
         cout << searchCourse << endl;
         do {
            cout << "Week         : ";
            cin >> week;
            if (week < 0 || week > 16) {
               cout << ">>>ERROR: Week is between 1 and 14" << endl;
            }
         } while (week < 0 || week > 16);
         cout << "Title        : ";
         cin >> title;
         do {
            cout << "Type (Q|T|A) : ";
            cin >> type;
            if (!(type == 'Q' || type == 'T' || type == 'A')) {
               cout << ">>>ERROR: type can be Q for quiz, T for Test, A for assignment" << endl;
            }
         } while (!(type == 'Q' || type == 'T' || type == 'A'));
         cout << "Score        : ";
         cin >> score;
         do {
            cout << "Out of       : ";
            cin >> fullMark;
            if (fullMark < score) {
               cout << ">>>ERROR: full mark need to be bigger than score." << endl;
            }
         } while (fullMark < score);
         cout << endl;
         grades[foundIndex].setInfo(searchCourse, week, title, type, score, fullMark);

         displayGrades(searchCourse, numGrades);
         cout << endl;
      }
   }

   void deleteGrades(const char* searchCourse, int& numGrades) {
      int inputWeek, i, foundIndex = -1;
      char inputType;
      char answer;
      do {
         cout << endl;
         cout << "Week : ";
         cin >> inputWeek;
         cout << "Type : ";
         cin >> inputType;
         cout << endl;
         for (i = 0; i < numGrades; i++) {
            if (grades[i].getWeek() == inputWeek && grades[i].getType() == inputType) {
               grades[i].display();
               foundIndex = i;
            }
         }
         cout << "Delete the grade? (Q to quit)" << endl << ">>>";
         cin >> answer;
      } while (!answer == 'Y' || !answer == 'Q');
      if (answer != 'Q') {
         grades[foundIndex].resetInfo();
      }
      displayGrades(searchCourse, numGrades);
      cout << endl;
   }
}