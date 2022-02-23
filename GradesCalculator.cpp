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
bool subjectMenu(const char* searchCourse);
void modifyGradesMenu(const char* searchCourse, int& numGrades);
//void viewGradesMenu();
void readRequirement(const char* searchCourse, double totalScore);
//void record();

int main() {
   //main menu
   mainMenu();
   //record(); // To write in the file
   return 0;
}

void mainMenu() {
   char inputCourse[10];
   char searchCourse[10];
   do {
      cout << "Grades Calculator" << endl;
      cout << "Course Code : ";
      cin >> inputCourse;
      // Ignore case sensitivity
      toUpper(searchCourse, inputCourse);
   } while (!subjectMenu(searchCourse));
}

// subject menu 1. view 2. set 3. weight setting 4.requirement to pass
bool subjectMenu(const char* searchCourse) {
   // Read data of search subject
   bool exit, valid=false;
   int numGrades = 0;
   double totalScore=0;
   // Read Weight setting on the course
   readWeightSetting(searchCourse);
   // Read all Grades 
   numGrades = readGrades(totalScore, searchCourse);
   if(numGrades > 0){ 
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
               displayGrades(searchCourse, numGrades);
         break;

         // 2. Set grades
         case 2:
            // Go to modify Grades menu
            modifyGradesMenu(searchCourse, numGrades);
            break;

         case 3:
            modifyWeightSettingMenu(searchCourse);
            break;

            //4. Requirement to Pass
         case 4:
            readRequirement(searchCourse, totalScore);
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

void readRequirement(const char* searchCourse, double totalScore) {
   FILE* fptr = nullptr;
   fptr = fopen("requirement.csv", "r");
   char subject[10] = { '\0' };
   char requirement[100];
   bool found = false;
   if (fptr != nullptr) {

      cout << "Requirements To Pass for " << searchCourse << endl;
      cout << "----------------------------------" << endl;
      while (fscanf(fptr, "%[^,],%[^\n]\n", subject, requirement) == 2) {
         if (strstr(subject, searchCourse) != nullptr) {
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
               fprintf(fptr, "%s,%s\n", searchCourse, requirement);
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

void modifyGradesMenu(const char* searchCourse, int& numGrades) {
   int input;
   bool exit;
   do{ 
      exit = false;
      cout << "=======================" << endl;
      cout << "1. Insert New grades" << endl;
      cout << "2. Update existing grades" << endl;
      cout << "3. Delete grades" << endl;
      cout << "0. Exit" << endl;
      cout << ">>> ";
      cin >> input;

      switch (input) {
         // Insert/Create New Grades
      case 1:
         insertGrades(searchCourse, numGrades);
         break;
         // Update existing Grades
      case 2:
         updateGrades(searchCourse, numGrades);
         break;
         // Delete existing Grades
      case 3:
         deleteGrades(searchCourse, numGrades);
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
