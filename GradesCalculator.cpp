#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdio>
#include <cstring>
#include "commonFunctions.h"
#include "Grade.h"
#include "Management.h"
using namespace std;
using namespace yh;

// TO DEVELOP
// ADD EVERY VALIDATION
// Store number of quiz, assignment, test?
// Sort for the best # quiz
// For multiple subject
// Improve display with category(QTA)
// More functions

bool subjectMenu(const char* searchCourse);
void displayGradesMenu(const char* searchCourse, int& numGrades);
void modifyWeightSettingMenu(const char* searchCourse);
void readRequirement(const char* searchCourse, double totalScore);

int main() {
   Management().run();
   return 0;
}


// SUBJECT MENU 
bool subjectMenu(const char* searchCourse) {
   // Read data of search subject
   bool exit, valid=false;
   int numGrades = 0;
   int input;
   double totalScore=0;
   // Read Weight setting on the course
   //readWeightSetting(searchCourse);
   // Read all Grades , RETURN NUMBER OF GRADES, SCORE UP TO DATE
   //numGrades = readGrades(totalScore, searchCourse);
   if(numGrades > 0){ 
      valid = true;
      do {
         exit = false;
         seperatorDouble();
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
            displayGradesMenu(searchCourse, numGrades);
          //  displayGrades(searchCourse, numGrades);
         break;

         // 2. Set grades
         case 2:
            // Go to modify Grades menu
            //modifyGradesMenu(searchCourse, numGrades);
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

// 1. VIEW GRADES MENU
void displayGradesMenu(const char* searchCourse, int& numGrades) {
   int input;
   seperatorDouble();
   cout << "1. Total Grades" << endl;
   cout << "2. Quiz Grades" << endl;
   cout << "3. Assignment Grades" << endl;
   cout << "4. Test Grades" << endl;
   cout << "5. Check requirement" << endl;
   cout << "0. Exit" << endl;
   cout << ">>> ";
   cin >> input;
   cout << endl;
   switch (input) {
      // 1. Total Grades
   case 1:
      // *** TO DEVELOP
      break;
      // 2. Quiz Grades
   case 2:
  //    displayQuiz(searchCourse, numGrades);
      break;
      // 3. Assignment Grades
   case 3:
    //  displayAssignment(searchCourse, numGrades);
      break;
      // 4. Test Grades
   case 4:
   //   displayTest(searchCourse, numGrades);
      break;
      // 5. Check requirement
   case 5:
      break;
      // 0. Exit
   case 0:
      break;
   }
}

// 3. MODIFY WEIGHT SETTING
void modifyWeightSettingMenu(const char* searchCourse) {
   int input;
   bool exit;
   do {
    //  displayWeightSetting(searchCourse);
      exit = false;
      seperatorDouble();
      cout << "1. Modify quiz setting" << endl;
      cout << "2. Modify Assignment setting" << endl;
      cout << "3. Modify Test setting" << endl;
      cout << "0. Exit" << endl;
      cout << ">>> ";
      cin >> input;
      cout << endl;
      switch (input) {
      case 1:
      //   modifyQuizWeightSetting();
       //  displayWeightSetting(searchCourse);
         break;
      case 2:
      //   modifyAssignWeightSetting();
       //  displayWeightSetting(searchCourse);
         break;
      case 3:
       //  modifyTestWeightSetting();
       //  displayWeightSetting(searchCourse);
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
