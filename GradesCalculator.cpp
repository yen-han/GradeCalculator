#include <iostream>
#include "Quiz.h"

using namespace std;
using namespace yh;
void mainMenu();
//int subjectMenu();
int main() {
   // Read Excel file
   //main menu
   int numQuiz=1;
   mainMenu();
   //cout << "How many Quiz do you have? ";
   //cin >> numQuiz;
   Quiz quiz[2] = { { "Quiz1", 1.875, 11 , 12},
            { "Quiz2", 1.875, 7 , 9} };
   quiz[0].display();
   quiz[1].display();
   cout << endl;
   double total;
   total = quiz[0].getTotal()+ quiz[1].getTotal();
   cout << "QUIZ TOTAL: " <<total <<" / 15 %" << endl;
   //setCurrentMark();
   // Write excel file
   // Close file
   return 0;
}

void mainMenu() {
   
   cout << "Grades Calculator" << endl;
   cout << "subject : OOP244" << endl << endl;
   //cout << "Select subject : " << endl;
   //cin >> input;
}
//
//// subject menu 1. view 2. set 3. check requirement to pass
//int subjectMenu() {
//   int input;
//   bool exit;
//   do {
//      exit = true;
//      cout << "=================" << endl;
//      cout << "1. View grades" << endl;
//      cout << "2. Modify new grades" << endl;
//      cout << "3. Requirement to Pass" << endl;
//      cout << "0. Exit" << endl;
//      cin >> input;
//
//      switch (input) {
//         // 1. View grades
//      case 1:
//         break;
//         // 2. Set grades
//      case 2:
//         break;
//         //3. Requirement to Pass
//      case 3:
//         break;
//         // 0. Exit
//      case 0:
//         exit = false;
//         break;
//      }
//   } while (exit);
//   return input;
//}

// viewSubject menu 1. total(how much left to pass) 2. Quizes 3. Assignments 4. Tests 5. check requirement to pass 0. Exit

// ModifySubject menu 1. quiz 2. assignment 3. test 0. Exit

// ModifyEachCategory 1. Insert 2. Update 3. Delete 0. Exit

// Insertmenu 1. courseCode... set function

// Update menu 1. name 2. currentMark 3. unit 4. max

// Delete menu 1. name 
// show the info deleted
// Do you really want to delete? Y. resetInfo N. go back

// Delete compeltion-> after deletion, current score


