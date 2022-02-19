// Create, Read, Update, Delete
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdio>
#include <cstring>
#include "Quiz.h"
#include "commonFunctions.h"
using namespace std;
namespace yh {

   void Quiz::resetInfo() {
      m_courseCode=0;
      m_quizName=nullptr;
      m_currentMark=-1; // possibly 0
      m_max=0;
   }

   Quiz::Quiz() {
      resetInfo();
   }
 
   Quiz::Quiz(const char* quizName, double weighted, double currentMark, double max) {
      resetInfo();
      if (quizName!= nullptr) {
         setQuizName(quizName);
         setCurrentMark(currentMark);
         setMax(max);
         setWeighted(weighted);
      }
   }

   Quiz::~Quiz() {
      delete[] m_quizName;
      m_quizName = nullptr;
   }
   Quiz& Quiz::setInfo(const char* quizName, double weighted, double currentMark, double max) {
      resetInfo();
      if (quizName != nullptr) {
         setQuizName(quizName);
         setCurrentMark(currentMark);
         setMax(max);
         setWeighted(weighted);
      }
      return *this;
   }

   Quiz& Quiz::setQuizName(const char* quizName) {
      if (quizName != nullptr) {
         m_quizName = new char[strlen(quizName) + 1];
         strcpy(m_quizName, quizName);
      }
      return *this;
   }

   Quiz& Quiz::setCurrentMark(double mark) {
      if (mark > 0) {
         m_currentMark = mark;
      }
      return *this;
   }
   Quiz& Quiz::setWeighted(double weighted) {
      if (weighted > 0) {
         m_weighted = weighted;
      }
      return *this;
   }

   Quiz& Quiz::setMax(double maxMark) {
      if (maxMark > 0) {
         m_max = maxMark;
      }
      return *this;
   }

   const char* Quiz::getQuizName() const {
      return m_quizName;
   }
   double Quiz::getCurrentMark() const {
      return m_currentMark;
   }
   double Quiz::getMaxMark() const {
      return m_max;
   }
   double Quiz::getWeighted() const {
      return m_weighted;
   }
   double Quiz::getTotal() const {
      return (m_currentMark / m_max * m_weighted); 
   }

   void Quiz::remaingMarkToPass() {
   }

   ostream& Quiz::display() const {
      cout << "Quiz Name : " << getQuizName() <<endl;
      cout << "Score     : " << getCurrentMark() << endl;
      cout << "Max       : " << getMaxMark() << endl;
      cout << "Weighted  : " << getWeighted()<<endl;
      cout << "---------------------" << endl;
      cout.setf(ios::fixed);
      cout.precision(3);
      cout << "Total     : " << getTotal() <<  " % " << endl;
      cout.unsetf(ios::fixed);
      cout << endl;
      return cout;
   }

   bool Quiz::isValid() const {
      return m_currentMark >= 0;
   }

   bool readQuiz() {
      bool finished = false;
      double total = 0;
      FILE* fptr = nullptr;
      fptr = fopen("quiz.csv", "r");
      if (fptr != nullptr) {
         // Read comma deliminated file
         char quizName[20];
         double score = 0, max = 0, weighted = 0;
         Quiz* quiz = nullptr;
         int numQuiz = 0;
         int sizeQuiz = 5;
         quiz = new Quiz[sizeQuiz];
         while (fscanf(fptr, "%[^,],%lf,%lf,%lf\n", quizName, &weighted, &score, &max) == 4) {
            if (numQuiz == sizeQuiz) {
               Quiz* tempQuiz = nullptr;
               tempQuiz = new Quiz[(sizeQuiz + numQuiz)];
               for (int i = 0; i < sizeQuiz; i++) {
                  tempQuiz[i] = quiz[i];
               }
               delete[] quiz;
               quiz = tempQuiz;
               sizeQuiz += numQuiz;
            }
            quiz[numQuiz].setInfo(quizName, weighted, score, max);
            numQuiz++;
            finished = true;
         }
         if (finished) {
            for (int i = 0; i < numQuiz; i++) {
               quiz[i].display();
            }
            for (int i = 0; i < numQuiz; i++) {
               total += quiz[i].getTotal();
            }
            cout << "QUIZ TOTAL: " << total << " / 15 %" << endl << endl;
         }
         else {
            setQuiz();
         }
         // Close file
         fclose(fptr);
         fptr = nullptr;

      }
      else {
         cout << "ERROR: File inaccesible";
      }
      return finished;
   }

   void setQuiz() {
      int numQuiz;
      char quizName[20];
      double score, max, weighted;
      double total = 0;
      Quiz* quiz = nullptr;
      cout << "How many Quiz do you have? ";
      cin >> numQuiz;
      quiz = new Quiz[numQuiz];
      for (int i = 0; i < numQuiz; i++) {
         cout << "Quiz Name : ";
         cin >> quizName;
         cout << "Score     : ";
         cin >> score;
         cout << "Max       : ";
         cin >> max;
         cout << "Weighted  : ";
         cin >> weighted;
         cout << endl;
         quiz[i].setInfo(quizName, weighted, score, max);
      }
      for (int i = 0; i < numQuiz; i++) {
         quiz[i].display() << endl;
      }

      for (int i = 0; i < numQuiz; i++) {
         total += quiz[i].getTotal();
      }
      cout << "QUIZ TOTAL: " << total << " / 15 %" << endl << endl;
      FILE* fptr = nullptr;
      fptr = fopen("quiz.csv", "w");
      if (fptr != nullptr) {
         for (int i = 0; i < numQuiz; i++) {
            fprintf(fptr, "%s,%lf,%lf,%lf\n", quiz[i].getQuizName(), quiz[i].getWeighted(), quiz[i].getCurrentMark(), quiz[i].getMaxMark());
         }
         fclose(fptr);
         fptr = nullptr;
      }
      else {
         cout << "ERROR: Can not write the data" << endl;
      }
   }

}
