#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdio>
#include <cstring>
#include "commonFunctions.h"
#include "Grade.h"
using namespace std;
using namespace yh;

// TO DEVELOP
// ADD EVERY VALIDATION
// Store number of quiz, assignment, test?
// Sort for the best 0 quiz
// For multiple subject
// Improve display with category(QTA)

void mainMenu();
bool subjectMenu(const char* searchCourse);
void modifyGradesMenu(const char* searchCourse, int& numGrades);
void modifyWeightSettingMenu(const char* searchCourse);
void readRequirement(const char* searchCourse, double totalScore);
//void record();

int main() {
   mainMenu();
   //record(); // To write in the file
   clearMemory();
   return 0;
}

void mainMenu() {
   char inputCourse[10];
   char searchCourse[10];
   do {
      cout << "Grades Calculator" << endl;
      cout << "Course Code : ";
      cin.get(inputCourse, 10, '\n');
      // Protect from longer course code
      cin.ignore(100, '\n');
      // Ignore case sensitivity
      toUpperString(searchCourse, inputCourse);
      // Loop until find VALID Course Code
   } while (!subjectMenu(searchCourse));
}

// SUBJECT MENU 
bool subjectMenu(const char* searchCourse) {
   // Read data of search subject
   bool exit, valid=false;
   int numGrades = 0;
   double totalScore=0;
   // Read Weight setting on the course
   readWeightSetting(searchCourse);
   // Read all Grades , RETURN NUMBER OF GRADES, SCORE UP TO DATE
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

         // 3. Set Weight setting
         case 3:
            // Go to modify Weight Setting menu
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

// 2. MODIFY GRADES MENU
void modifyGradesMenu(const char* searchCourse, int& numGrades) {
   int input;
   bool exit;
   do {
      exit = false;
      cout << "=======================" << endl;
      cout << "1. Insert New grades" << endl;
      cout << "2. Update existing grades" << endl;
      cout << "3. Delete grades" << endl;
      cout << "0. Exit" << endl;
      cout << ">>> ";
      cin >> input;
      cout << endl;
      switch (input) {
         // Insert or Create New Grades
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

// 3. MODIFY WEIGHT SETTING
void modifyWeightSettingMenu(const char* searchCourse) {
   int input;
   bool exit;
   do {
      displayWeightSetting(searchCourse);
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
         modifyQuizWeightSetting();
         displayWeightSetting(searchCourse);
         break;
      case 2:
         modifyAssignWeightSetting();
         displayWeightSetting(searchCourse);
         break;
      case 3:
         modifyTestWeightSetting();
         displayWeightSetting(searchCourse);
         break;
      case 0:
         exit = true;
         break;
      }
   } while (!exit);
}

void readRequirement(const char* searchCourse, double totalScore) {
   FILE* fptr = nullptr;
   fptr = fopen("requirement.csv", "r");
   char subject[10] = { '\0' };
   char requirement[100];
   bool found = false;
   if (fptr != nullptr) {

      cout << "*** Requirements To Pass for " << searchCourse << " ***"<< endl;
      cout << "----------------------------------" << endl;
      while (fscanf(fptr, "%[^,],%[^\n]\n", subject, requirement) == 2) {
         if (strstr(subject, searchCourse) != nullptr) {
            cout << requirement << endl;
            found = true;
         }
      }
      cout << endl;
      fclose(fptr);
      fptr = nullptr;
      if (!found) {
         char answer;
         char add;
         cout << "Requirements not Found" << endl;
         cout << "Add requirements? (Y/N)" << endl << ">>>";
         cin >> answer;
         answer = toUpperCharacter(answer);
         cin.ignore();
         if (answer == 'Y' || answer == 'y') {
            do {
               cout << "Requirements to Pass: ";
               cin.getline(requirement, 50);
               fptr = fopen("requirement.csv", "a");
               fprintf(fptr, "%s,%s\n", searchCourse, requirement);
               cout << "Continue to Add (Y/N)?" << endl << " >>>";
               cin.get(add);
               add = toUpperCharacter(add);
               cin.ignore();
               fclose(fptr);
               fptr = nullptr;
            } while (add == 'Y');
         }
      }
      // minimum TO pass
      cout << "Minimum to Pass: " <<(50-totalScore)<< " % / 50 %" << endl<<endl;
   }
   else {
      cout << "--- ERROR:: FILE NOT FOUND" << endl;
   }
}

// viewSubject menu 1. total(how much left to pass) 2. Quizes 3. Assignments 4. Tests 5. check requirement to pass 0. Exit
//void viewGradesMenu() {
//
//}