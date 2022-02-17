#include <iostream>
#include "Quiz.h"

using namespace std;
using namespace yh;
void mainMenu();
bool subjectMenu();
void setQuiz();

int main() {
   // Read Excel file
   //main menu
   mainMenu();
   //setCurrentMark();
   // Write excel file
   // Close file
   return 0;
}

void mainMenu() {
   
   cout << "Grades Calculator" << endl;
   cout << "subject : OOP244" << endl;
   //cout << "Select subject : " << endl;
   //cin >> input;
   subjectMenu();
}

// subject menu 1. view 2. set 3. check requirement to pass
bool subjectMenu() {
   int input;
   bool exit;
   do {
      exit = true;
      cout << "=================" << endl;
      cout << "1. View grades" << endl;
      cout << "2. Modify new grades" << endl;
      cout << "3. Requirement to Pass" << endl;
      cout << "0. Exit" << endl ;
      cout << ">>> ";
      cin >> input;

      switch (input) {
      // 1. View grades
      case 1:
         cout << "unavailable" << endl;
         break;
      // 2. Set grades
      case 2:
         setQuiz();
         break;
      //3. Requirement to Pass
      case 3:
         cout << "unavailable" << endl;
         break;
      // 0. Exit
      case 0:
         exit = false;
         break;
      }
   } while (exit);
   return exit;
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
   cout << "QUIZ TOTAL: " << total << " / 15 %" << endl;
}

// viewSubject menu 1. total(how much left to pass) 2. Quizes 3. Assignments 4. Tests 5. check requirement to pass 0. Exit

// ModifySubject menu 1. quiz 2. assignment 3. test 0. Exit

// ModifyEachCategory 1. Insert 2. Update 3. Delete 0. Exit

// Insertmenu 1. courseCode... set function

// Update menu 1. name 2. currentMark 3. unit 4. max

// Delete menu 1. name 
// show the info deleted
// Do you really want to delete? Y. resetInfo N. go back

// Delete compeltion-> after deletion, current score


