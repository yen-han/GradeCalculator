#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdio>
#include <cstring>
#include "Quiz.h"

using namespace std;
using namespace yh;

void mainMenu();
bool subjectMenu();
void readRequirement();

int main() {
   //main menu
   mainMenu();

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
      cout << "0. Exit" << endl;
      cout << ">>> ";
      cin >> input;

      switch (input) {
         // 1. View grades
      case 1:
         readQuiz();
         cout << "unavailable" << endl;
         break;

      // 2. Set grades
      case 2:
         setQuiz();
         break;

         //3. Requirement to Pass
      case 3:
         cout << endl;
         readRequirement();
         break;

         // 0. Exit
      case 0:
         exit = false;
         break;
      }
   } while (exit);
   return exit;
}

void readRequirement() {
   FILE* fptr = nullptr;
   fptr = fopen("requirement.csv", "r");
   if (fptr != nullptr) {
      char subject[10];
      char requirement[100];
      bool found = false;
      cout << "Requirements for OOP244" << endl;
      cout << "-----------------------" << endl;
      while (fscanf(fptr, "%[^,],%[^\n]\n", subject, requirement) == 2) {
         if (strstr(subject, "OOP244") != nullptr) {
            cout << requirement << endl;
            found = true;
         }
      }
      if(!found) {
         cout << "Requirement not Found" << endl;
      }
      cout << endl;
      //rewind(fptr);
      fclose(fptr);
      fptr = nullptr;
   }
   else {
      cout << "FILE NOT FOUND" << endl;
   }
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


