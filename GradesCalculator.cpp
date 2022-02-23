#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdio>
#include <cstring>
#include "commonFunctions.h"
#include "Grade.h"
using namespace std;
using namespace yh;

// ADD EVERY VALIDATION

void mainMenu();
bool subjectMenu(const char* searchSubject);
void modifyGradesMenu(const char* searchSubject, int& numGrades);
//void viewGradesMenu();
void readRequirement(const char* searchSubject, double totalScore);
//void record();

int main() {
   //main menu
   mainMenu();
   //record(); // To write in the file
   return 0;
}

void mainMenu() {
   char inputSubject[10];
   char searchSubject[10];
   do {
      cout << "Grades Calculator" << endl;
      cout << "Subject : ";
      cin >> inputSubject;
      // Ignore case sensitivity
      toUpper(searchSubject, inputSubject);
   } while (!subjectMenu(searchSubject));
}

// subject menu 1. view 2. set 3. weight setting 4.requirement to pass
bool subjectMenu(const char* searchSubject) {
   // Read data of search subject
   bool exit, valid=false;
   int numGrades = 0;
   double totalScore=0;
   // Read Weight setting on the course
   readWeightSetting(searchSubject);
   // Read all Grades 
   numGrades = readGrades(totalScore, searchSubject);
   if(numGrades>0){ 
      valid = true;
      int input;
      do {
         exit = false;
         cout << "=======================" << endl;
         cout << "1. View grades" << endl;
         cout << "2. Modify grades" << endl;
         cout << "3. Modify weight setting" << endl;
         cout << "4. Requirement to Pass" << endl;
         cout << "0. Exit" << endl;
         cout << ">>> ";
         cin >> input;
         cout << endl;
         switch (input) {
            // 1. View grades
         case 1:
               displayData(searchSubject, numGrades);
         break;

         // 2. Set grades
         case 2:
            // Go to modify Grades menu
            modifyGradesMenu(searchSubject, numGrades);
            break;

         case 3:
            modifyWeightSettingMenu(searchSubject);
            break;

            //4. Requirement to Pass
         case 4:
            readRequirement(searchSubject, totalScore);
            break;

            // 0. Exit
         case 0:
            exit = true;
            break;
         }
      } while (!exit);
   } 
   return valid;
}

void readRequirement(const char* searchSubject, double totalScore) {
   FILE* fptr = nullptr;
   fptr = fopen("requirement.csv", "r");
   char subject[10] = { '\0' };
   char requirement[100];
   bool found = false;
   if (fptr != nullptr) {

      cout << "Requirements To Pass for " << searchSubject << endl;
      cout << "----------------------------------" << endl;
      while (fscanf(fptr, "%[^,],%[^\n]\n", subject, requirement) == 2) {
         if (strstr(subject, searchSubject) != nullptr) {
            cout << requirement << endl;
            found = true;
         }
      }
      cout << endl;
      //rewind(fptr);
      fclose(fptr);
      fptr = nullptr;
      if (!found) {
         //bool finished = false;
         char answer;
         char add;
         cout << "Requirements not Found" << endl;
         cout << "Add requirements? (Y/N)" << endl << ">>>";
         cin >> answer;
         cin.ignore();
         if (answer == 'Y' || answer == 'y') {
            do {
               /*cout << "Subject name: ";
               cin.getline(subject, 10);*/
               cout << "Requirements to Pass: ";
               cin.getline(requirement, 50);
               fptr = fopen("requirement.csv", "a");
               fprintf(fptr, "%s,%s\n", searchSubject, requirement);
               cout << "Continue to Add? (Y/N)" << endl << ">>>";
               cin.get(add);
               cin.ignore();
               fclose(fptr);
               fptr = nullptr;
            } while (add == 'Y' || add == 'y');
         }
      }
      // your status TO pass
      cout << &totalScore << endl;
   }
   else {
      cout << "ERROR:: FILE NOT FOUND" << endl;
   }
}

// viewSubject menu 1. total(how much left to pass) 2. Quizes 3. Assignments 4. Tests 5. check requirement to pass 0. Exit
//void viewGradesMenu() {
//
//}

void modifyGradesMenu(const char* searchSubject, int& numGrades) {
   int input;
   bool exit;
   do{ 
      exit = false;
      cout << "=======================" << endl;
      cout << "1. Insert New grades" << endl;
      cout << "2. Modify existing grades" << endl;
      cout << "3. Delete grades" << endl;
      cout << "0. Exit" << endl;
      cout << ">>> ";
      cin >> input;

      switch (input) {
         // Insert/Create New Grades
      case 1:
         insertGrades(searchSubject, numGrades);
         break;
         // Update existing Grades
      case 2:
         break;
         // Delete existing Grades
      case 3:
         break;
      case 0:
         exit = true;
         break;
      }
   } while (!exit);
}

// ModifySubject menu 1. quiz 2. assignment 3. test 0. Exit

// ModifyEachCategory 1. Insert 2. Update 3. Delete 0. Exit

// Insertmenu 1. courseCode... set function

// Update menu 1. name 2. currentMark 3. unit 4. max

// Delete menu 1. name 
// show the info deleted
// Do you really want to delete? Y. resetInfo N. go back

// Delete compeltion-> after deletion, current score

// Sort for the best 0 quiz
