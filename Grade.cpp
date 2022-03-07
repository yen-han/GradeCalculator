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
   // Read Weight Setting on the course
   void readWeightSetting(const char* searchCourse) {
      char subject[10] = { '\0' };
      double tempOneQuizWeight = 0;
      double tempAllQuizWeight = 0;
      double tempOneAssignWeight = 0;
      double tempAllAssignWeight = 0;
      double tempOneTestWeight = 0;
      double tempAllTestWeight = 0;
      //ifstream file;     
      //file.open("assessmentWeight.csv");
      FILE* fptr = nullptr;
      fptr = fopen("assessmentWeight.csv", "r");
      if(fptr!=nullptr) {
      //if (file.is_open()) {
         //while(file){ 
         while (fscanf(fptr, "%[^,],%lf,%lf,%lf,%lf,%lf,%lf\n", subject, &tempOneQuizWeight, &tempAllQuizWeight, &tempOneAssignWeight, &tempAllAssignWeight, &tempOneTestWeight, &tempAllTestWeight) == 7) {
            if (strstr(subject, searchCourse) != nullptr) {
               //file >> subject;
               //file >> quizEachWeight;
               //file >> quizAllWeight;
               //file >> assignEachWeight;
               //file >> assignAllWeight;
               //file >> testEachWeight;
               //file >> testAllWeight;
               quizEachWeight = tempOneQuizWeight;
               quizAllWeight = tempAllQuizWeight;
               assignEachWeight = tempOneAssignWeight;
               assignAllWeight = tempAllAssignWeight;
               testEachWeight = tempOneTestWeight;
               testAllWeight = tempAllTestWeight;
            }
         }
         fclose(fptr);
         //file.close();
         fptr = nullptr;
      }
      else {
         cout << "--- ERROR: WEIGHT SETTING FILE INACCESIBLE";
      }
   }
   
   // Read all grades on data file
   int readGrades(double& totalScore, const char* searchCourse) {
      int numGrades = 0;
      bool found = false;
      FILE* fptr = nullptr;
      fptr = fopen("grade.csv", "r");
      if (fptr != nullptr) {
         char title[20];
         char subject[20] = { '\0' };
         char type;
         int week;
         double score = 0, fullMark = 0;
         unsigned int sizeGrades = 5;
         grades = new Grade[sizeGrades];

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
            cout << "--- ERROR: Check Course Code" << endl << endl;
         }
      }
      else {
         cout << "--- ERROR: GRADE FILE INACCESIBLE";
      }
      return numGrades;
   }

   std::ostream& displayQuiz(const char* searchCourse, const int numGrades) {
      double sumQuiz = 0;
      if (numGrades > 0) {
         cout << "*** " << searchCourse << " ***" << endl << endl;
         cout << "Week       | ";
         for (int i = 0; i < numGrades; i++) {
            if (grades[i].isValid() && grades[i].getType()=='Q') {
               cout << setw(7);
               cout << "#" << grades[i].getWeek();
            }
         }
         cout << endl;
         cout << "Title      | ";
         for (int i = 0; i < numGrades; i++) {
            if (grades[i].isValid() && grades[i].getType() == 'Q') {
               cout << setw(8);
               cout << grades[i].getTitle();
            }
         }
         cout << endl;

         cout << "Score      | ";
         for (int i = 0; i < numGrades; i++) {
            if (grades[i].isValid() && grades[i].getType() == 'Q') {
               cout << setw(6);
               cout << grades[i].getScore() << "/" << grades[i].getFullMark();
            }
         }
         cout << endl;
         cout << "Weighted   | ";
         for (int i = 0; i < numGrades; i++) {
            if (grades[i].isValid() && grades[i].getType() == 'Q') {
               cout.setf(ios::fixed);
               cout.precision(3);
               cout << setw(8);
               cout << quizEachWeight;
               cout.unsetf(ios::fixed);
            }
         }
         cout << endl;
         cout << "---------------------" << endl;
         cout << "Grade      | ";
         for (int i = 0; i < numGrades; i++) {
            if (grades[i].isValid() && grades[i].getType() == 'Q') {
               cout.setf(ios::fixed);
               cout.precision(3);
               cout << setw(8);
               cout << grades[i].getWeightedScore();
               cout.unsetf(ios::fixed);
            }
         }
         cout << endl;
         for (int i = 0; i < numGrades; i++) {
            if (grades[i].isValid()) {
               if (grades[i].getType() == 'Q') {
                  sumQuiz += grades[i].getWeightedScore();
               }
            }
         }

         cout << endl;
         cout.setf(ios::fixed);
         cout.precision(2);
         cout << "QUIZ       |   " << sumQuiz << "  /  " << quizAllWeight << " %" << endl;
         cout.unsetf(ios::fixed);
      }
      else {
         cout << "--- ERROR: No data found. Return to menu." << endl;
      }
      return cout;
   }
   std::ostream& displayAssignment(const char* searchCourse, const int numGrades) {
      double sumAssign = 0;
      if (numGrades > 0) {
         cout << "*** " << searchCourse << " ***" << endl << endl;
         cout << "Week       | ";
         for (int i = 0; i < numGrades; i++) {
            if (grades[i].isValid() && grades[i].getType() == 'A') {
               cout << setw(7);
               cout << "#" << grades[i].getWeek();
            }
         }
         cout << endl;
         cout << "Title      | ";
         for (int i = 0; i < numGrades; i++) {
            if (grades[i].isValid() && grades[i].getType() == 'A') {
               cout << setw(8);
               cout << grades[i].getTitle();
            }
         }
         cout << endl;

         cout << "Score      | ";
         for (int i = 0; i < numGrades; i++) {
            if (grades[i].isValid() && grades[i].getType() == 'A') {
               cout << setw(6);
               cout << grades[i].getScore() << "/" << grades[i].getFullMark();
            }
         }
         cout << endl;
         cout << "Weighted   | ";
         for (int i = 0; i < numGrades; i++) {
            if (grades[i].isValid() && grades[i].getType() == 'A') {
               cout.setf(ios::fixed);
               cout.precision(3);
               cout << setw(8);
               cout << assignEachWeight;
               cout.unsetf(ios::fixed);
            }
         }
         cout << endl;
         cout << "---------------------" << endl;
         cout << "Grade      | ";
         for (int i = 0; i < numGrades; i++) {
            if (grades[i].isValid() && grades[i].getType() == 'A') {
               cout.setf(ios::fixed);
               cout.precision(3);
               cout << setw(8);
               cout << grades[i].getWeightedScore();
               cout.unsetf(ios::fixed);
            }
         }
         cout << endl;
         for (int i = 0; i < numGrades; i++) {
            if (grades[i].isValid()) {
               if (grades[i].getType() == 'A') {
                  sumAssign += grades[i].getWeightedScore();
               }
            }
         }

         cout << endl;
         cout.setf(ios::fixed);
         cout.precision(2);
         cout << "ASSIGNMENT |   " << sumAssign << "  /  " << assignAllWeight << " %" << endl;
         cout.unsetf(ios::fixed);
      }
      else {
         cout << "--- ERROR: No data found. Return to menu." << endl;
      }
      return cout;
   }
   std::ostream& displayTest(const char* searchCourse, const int numGrades) {
      double sumTest = 0;
      if (numGrades > 0) {
         cout << "*** " << searchCourse << " ***" << endl << endl;
         cout << "Week       | ";
         for (int i = 0; i < numGrades; i++) {
            if (grades[i].isValid() && grades[i].getType() == 'T') {
               cout << setw(7);
               cout << "#" << grades[i].getWeek();
            }
         }
         cout << endl;
         cout << "Title      | ";
         for (int i = 0; i < numGrades; i++) {
            if (grades[i].isValid() && grades[i].getType() == 'T') {
               cout << setw(8);
               cout << grades[i].getTitle();
            }
         }
         cout << endl;

         cout << "Score      | ";
         for (int i = 0; i < numGrades; i++) {
            if (grades[i].isValid() && grades[i].getType() == 'T') {
               cout << setw(6);
               cout << grades[i].getScore() << "/" << grades[i].getFullMark();
            }
         }
         cout << endl;
         cout << "Weighted   | ";
         for (int i = 0; i < numGrades; i++) {
            if (grades[i].isValid() && grades[i].getType() == 'T') {
               cout.setf(ios::fixed);
               cout.precision(3);
               cout << setw(8);
               cout << testEachWeight;
               cout.unsetf(ios::fixed);
            }
         }
         cout << endl;
         cout << "---------------------" << endl;
         cout << "Grade      | ";
         for (int i = 0; i < numGrades; i++) {
            if (grades[i].isValid() && grades[i].getType() == 'T') {
               cout.setf(ios::fixed);
               cout.precision(3);
               cout << setw(8);
               cout << grades[i].getWeightedScore();
               cout.unsetf(ios::fixed);
            }
         }
         cout << endl;
         for (int i = 0; i < numGrades; i++) {
            if (grades[i].isValid()) {
               if (grades[i].getType() == 'T') {
                  sumTest += grades[i].getWeightedScore();
               }
            }
         }

         cout << endl;
         cout.setf(ios::fixed);
         cout.precision(2);
         cout << "TEST       |   " << sumTest << "  /  " << testAllWeight << " %" << endl << endl;
         cout.unsetf(ios::fixed);
      }
      else {
         cout << "--- ERROR: No data found. Return to menu." << endl;
      }
      return cout;
   }
   // Display grades with format
   std::ostream& displayGrades(const char* searchCourse, const int numGrades) {
      double total = 0;
      double sumQuiz = 0;
      double sumAssign = 0;
      double sumTest = 0;
      if (numGrades > 0) {
         cout << "*** " << searchCourse << " ***" << endl << endl;
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
         cout << "--- ERROR: No data found. Return to menu." << endl;
      }
      return cout;
   }

   // CREATE OR INSERT grades
   void insertGrades(const char* searchCourse, int& numGrades) {
      int week;
      char type, answer;
      char title[20];
      double score, fullMark;
      double total = 0;

      do {
        cout << "*** INSERT " << searchCourse << " ***" << endl << endl;
        getGradeInput(week, title, type, score, fullMark);
         grades[numGrades].setInfo(searchCourse, week, title, type, score, fullMark);
         numGrades++;
         cout << "Insert more? (Y/N)?" << " >>>";
         cin >> answer;
         answer = toUpperCharacter(answer);
      } while (answer == 'Y');

      displayGrades(searchCourse, numGrades);
      cout << endl;
   }

   // UPDATE grades
   void updateGrades(const char* searchCourse, int& numGrades) {
      int foundIndex = -1;
      char answer;
      int week;
      char type;
      char title[20];
      double score, fullMark;
      cout << "*** UPDATE " << searchCourse << " ***" << endl << endl;
      do {
         foundIndex = findMatchedIndex(numGrades);
         cout << "Update the grade (Y/N)?" << " >>>";
         cin >> answer;
         answer = toUpperCharacter(answer);
      } while (!(answer == 'Y' || answer == 'N'));
      cout << endl;
      if (answer != 'N') {
         getGradeInput(week, title, type, score, fullMark);
         grades[foundIndex].setInfo(searchCourse, week, title, type, score, fullMark);

         displayGrades(searchCourse, numGrades);
         cout << endl;
      }
   }

   // DELETE grades
   void deleteGrades(const char* searchCourse, int& numGrades) {
      int foundIndex = -1;
      char answer;
      do {
         cout << "*** DELETE " << searchCourse << " ***" << endl << endl;
         foundIndex = findMatchedIndex(numGrades);
         cout << "Delete the grade (Y/N)?" << endl << " >>>";
         cin >> answer;
         answer = toUpperCharacter(answer);
      } while (!(answer == 'Y' || answer == 'N'));
      cout << endl;
      if (toUpperCharacter(answer) != 'N') {
         grades[foundIndex].resetInfo();
      }
      displayGrades(searchCourse, numGrades);
      cout << endl;
   }

   int findMatchedIndex(const int numGrades) {
      int inputWeek, i, foundIndex = -1;
      char inputType;

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
      return foundIndex;
   }

   void getGradeInput(int& week, char* title, char& type, double& score, double& fullMark) {
      do {
         cout << "Week         : ";
         cin >> week;
         if (week < 0 || week > 16) {
            cout << "--- ERROR: Week is between 1 and 14" << endl;
         }
      } while (week < 0 || week > 16);
      cout << "Title        : ";
      cin.get(title, 20, '\n');
      cin.ignore(100, '\n');
      do {
         cout << "Type (Q|T|A) : ";
         cin.get(type);
         type=toUpperCharacter(type);
         if (!(type == 'Q' || type == 'T' || type == 'A')) {
            cout << "--- ERROR: Type must be Q for quiz, T for Test, A for assignment" << endl;
         }
      } while (!(type == 'Q' || type == 'T' || type == 'A'));
      cout << "Score        : ";
      cin >> score;
      do {
         cout << "Out of       : ";
         cin >> fullMark;
         if (fullMark < score) {
            cout << "--- ERROR: full mark need to be bigger than score." << endl;
         }
      } while (fullMark < score);
      cout << endl;
   }

   void displayWeightSetting(const char* searchCourse) {
      cout << "*** Weight Setting for " << searchCourse << " ***" << endl<<endl;
      cout.setf(ios::fixed);
      cout.precision(3);
      cout << "Each QUIZ(Q)       | " << quizEachWeight << " %" << endl;
      cout.unsetf(ios::fixed);
      cout << "All  QUIZ(Q)       | " << quizAllWeight << " %" << endl << endl;
      cout.setf(ios::fixed);
      cout.precision(3);
      cout << "Each ASSIGNMENT(A) | " << assignEachWeight << " %" << endl;
      cout.unsetf(ios::fixed);
      cout << "All  ASSIGNMENT(A) | " << assignAllWeight << " %" << endl << endl;
      cout.setf(ios::fixed);
      cout.precision(3);
      cout << "Each TEST(T)       | " << testEachWeight << " %" << endl;
      cout.unsetf(ios::fixed);
      cout << "All  TEST(T)       | " << testAllWeight << " %" << endl << endl;
   }

   void modifyQuizWeightSetting() {
      double inputEachQuiz;
      double inputAllQuiz;
      char answer;
      do { 
      cout << "Each Quiz  : ";
      cin >> inputEachQuiz;
      cout << "All Quiz   : ";
      cin >> inputAllQuiz;
      cout << endl;

      cout << "Change (Y/N)?"<< " >>> ";
         cin >> answer;
         answer = toUpperCharacter(answer);
      } while (answer != 'Y');
      if (answer == 'Y') {
         quizEachWeight = inputEachQuiz;
         quizAllWeight = inputAllQuiz;
      }
   }
   void modifyAssignWeightSetting() {
      double inputEachAssign;
      double inputAllAssign;
      char answer;
      do {
         cout << "Each Assignment : ";
         cin >> inputEachAssign;
         cout << "All Assginment  : ";
         cin >> inputAllAssign;
         cout << endl;

         cout << "Change (Y/N)?" << " >>> ";
         cin >> answer;
         answer = toUpperCharacter(answer);
      } while (answer != 'Y');
      if (answer == 'Y') {
         assignEachWeight = inputEachAssign;
         assignAllWeight = inputAllAssign;
      }
   }
   void modifyTestWeightSetting() {
      double inputEachTest;
      double inputAllTest;
      char answer;
      do {
         cout << "Each Test  : ";
         cin >> inputEachTest;
         cout << "All Test   : ";
         cin >> inputAllTest;
         cout << endl;

         cout << "Change (Y/N)?" << " >>> ";
         cin >> answer;
         answer = toUpperCharacter(answer);
      } while (answer != 'Y');
      if (answer == 'Y') {
         testEachWeight = inputEachTest;
         testAllWeight = inputAllTest;
      }
   }

   void clearMemory() {
      delete[] grades;
      grades = nullptr;
   }
}



