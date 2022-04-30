#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include "Management.h"
#include "Requirement.h"
#include "commonFunctions.h"
#include "Menu.h"
using namespace std;
namespace yh {
   void Management::deallocateGrades() {
      for (int i = 0; i < m_numGrades; i++) {
         delete m_grades[i];
      }
      m_numGrades = 0;
   }

   void Management::deallocateRequirements() {
      for (int i = 0; i < m_numRequires; i++) {
         delete m_require[i];
      }
      m_numRequires = 0;
   }

   Management::~Management() {
      deallocateGrades();
      deallocateRequirements();
   }

   void Management::run() {
      int selection;
      Menu subMenu("1 | View Grades\n2 | Modify grades\n3 | Modify weights\n4 | Requirement to Pass\n5 | Change Course\n", 5);
      cout << "Starting Grades Calculator" << endl;
      loadGrades();
      loadRequirements();
      cout << "-------------------------------" << endl;
      do {
         cout << "Grades Calculator" << endl;
         cout << "Course: " << (m_course[0] == '\0' ? "N/A" : m_course) << endl;
         cout << "-------------------------------" << endl;
         selection = subMenu.run();
         if (selection!=5 && m_course[0] == '\0') selection = 5;

         switch (selection) {
            // 1 | View grades
         case 1:
            viewGrades();
            cout << endl;
            break;
         case 2:
            modifyGrades();
            break;
         case 3:
            break;
         case 4:
            viewRequirements();
            break;
         case 5:
            changeCourseCode();
            break;
         case 0:
            saveGrades();
            break;
         }
      } while (selection != 0);
      cout << endl<< "Exiting Grades Calculator" << endl;
   }
   // 1 | View Grades
   void Management::viewGrades() {
      cout << endl<< "Week     | ";
      for (int i = 0; i < m_numGrades; i++) {
         if (!strcmp(m_grades[i]->getCourse(), m_course)) {

            cout<<setw(7);
            cout<< "#" << m_grades[i]->getWeek()<<" | ";
         }
      }
      cout << endl;
      cout << "Title    | ";
      for (int i = 0; i < m_numGrades; i++) {
         if (!strcmp(m_grades[i]->getCourse(), m_course)) {
            cout << setw(8);
            cout << m_grades[i]->getTitle() << " | ";
         }
      }
      cout << endl;
      cout << "Score    | ";
      for (int i = 0; i < m_numGrades; i++) {
         if (!strcmp(m_grades[i]->getCourse(), m_course)) {
            cout << setw(8);
            cout << m_grades[i]->getScore() << " | ";
         }
      }
      cout << endl;
      cout << "Full     | ";
      for (int i = 0; i < m_numGrades; i++) {
         if (!strcmp(m_grades[i]->getCourse(), m_course)) {
            cout << setw(8);
            cout << m_grades[i]->getFullMark() << " | ";
         }
      }
      cout << endl;
   }
   // 2 | Modify Grades
   void Management::modifyGrades() {
      int selection;
      Menu modifyGradesMenu("1 | Insert Grades\n2 | Update Grades\n3 | Delete Grades\n", 3);
      do {
         cout << endl<<"Course: " << m_course << endl;
         cout << "-------------------------------" << endl;
         selection = modifyGradesMenu.run();
         switch (selection) {
            // 1 | Insert Grades
         case 1:
            insertGrades();
            cout << endl;
            break;
            // 2 | Update Grades
         case 2:
            updateGrades();
            cout << endl;
            break;
            // 3 | Delete Grades
         case 3:
            removeGrades();
            break;
         case 0:
            cout << endl;
            break;
         }
      } while (selection != 0);

   }
   // 2-1 | Insert Grades
   void Management::insertGrades() {
      cout << endl;
      if (m_numGrades >= max) {
         cout << "Database full!" << endl;
      }
      else {
         Grade* temp = new Grade();
         temp->read(cin, m_course);
         if (search(temp->getWeek(), temp->getType()) > 0) {
            cout << "week: " << temp->getWeek() << ", Type "<< temp->getType()<<" is already in the system." << endl << endl;
            delete temp;
         }
         else {
            if (temp) {
               m_grades[m_numGrades++] = temp;
            }
            else {
               cout << *temp;
               delete temp;
            }
         }
      }
   }
   // 2-2 | Update Grades
   void Management::updateGrades() {
      int foundIdx = -1;
      int week; char type;
      cout << "Week : ";
      cin >> week;
      cout << "Type(Q|quiz A|Assignment T|Test): ";
      cin >> type;
      foundIdx = search(week, type);
      if (foundIdx < 0) {
         cout << "---ERROR: Grade not found" << endl;
      }
      else {
         cout <<"--- Before"<< endl<<* m_grades[foundIdx] << endl;
         Grade* temp = new Grade();
         temp->read(cin, m_course);
         cout <<"--- After"<< endl << *temp << endl;
         Menu subMenu("Are you sure to modify?\n1 | Yes\n", 1);
         if (subMenu.run() == 1) {
            m_grades[foundIdx] = temp;
         }
         else {
            cout << "Aborted!" << endl << endl;
         }
      }
   }
   // Search grade by week & type
   int Management::search(int week, char type) {
      int foundIdx = -1;
      for (int i = 0; i < m_numGrades; i++) {
         if (!strcmp(m_grades[i]->getCourse(),m_course) && m_grades[i]->getWeek() == week && m_grades[i]->getType() == type) {
            foundIdx = i;
         }
      }
      return foundIdx;
   }
   // 2-3 | Delete Grades
   void Management::removeGrades() {
      int foundIdx = -1;
      int week; char type;
      cout << "Week : ";
      cin >> week;
      cout << "Type(Q|quiz A|Assignment T|Test): ";
      cin >> type;
      foundIdx = search(week, type);
      if (foundIdx < 0) {
         cout << "---ERROR: Grade not found" << endl;
      }
      else {
         cout << "--- Grade to be Remove" << endl << *m_grades[foundIdx] << endl;
         Menu subMenu("Are you sure to remove?\n1 | Yes\n", 1);
         if (subMenu.run() == 1) {
            remove(foundIdx);
            cout << "Grade removed" << endl;
         }
         else {
            cout << "Aborted!" << endl << endl;
         }
      }
   }
   // Remove grade and re-arrange
   void Management::remove(int index) {
      delete m_grades[index];
      for (int i = index; i < m_numGrades - 1; i++) {
         m_grades[i] = m_grades[i + 1];
      }
      m_numGrades--;
   }
   // 4 | View requirement to Pass
   void Management::viewRequirements() {
      for (int i = 0; i < m_numRequires; i++) {
         if (!strcmp(m_require[i]->getCourse(), m_course)) {
            cout << *m_require[i] << endl;
         }
      }
   }

   // 5 | Change Course
   void Management::changeCourseCode() {
      cin.ignore();
      bool done = false;
      char inputCourse[10];
      do {
         cout << "Enter Course Code : ";
         cin.get(inputCourse, 10, '\n');
         cin.ignore(100, '\n');
         // Ignore case sensitivity
         toUpperString(m_course, inputCourse);
         for (int i = 0; i < m_numGrades; i++) {
            if (!strcmp(m_grades[i]->getCourse(), m_course)) {
               done = true;
            }
         }
         if (!done) cout << "--- ERROR: Course is not found" << endl<<endl;
      } while (!done);
      cout << endl;
   }
   // 0 | Exit
   void Management::saveGrades() {
      if (m_file) {
         ofstream saveFile(m_file);
         for (int i = 0; i < m_numGrades; i++) {
            m_grades[i]->save(saveFile) << endl;
         }
         saveFile.flush();
         saveFile.close();
      }
   }

   int Management::loadGrades() {
      saveGrades();
      deallocateGrades();

      cout<< "Enter file name: ";
      m_file=getDynCstr(cin, '\n');

      ifstream datafile(m_file);
      if (!datafile) {
         // No file
         datafile.close();
         cerr << "--- ERROR: " << m_file <<" INACCESIBLE" << endl;
      }
      else {
         do{
            m_grades[m_numGrades] = new Grade();
            m_grades[m_numGrades]->load(datafile);
            if (m_grades[m_numGrades]&& !datafile.fail()) {
               m_numGrades++;
            }
            else {
               delete m_grades[m_numGrades];
            }
         } while (datafile);
         datafile.close();
         cout << m_numGrades << " grades loaded!" << endl;
      }
      return m_numGrades;
   }

   int Management::loadRequirements() {
      deallocateRequirements();
      ifstream datafile("requirement.csv");
      if (!datafile) {
         // No file
         datafile.close();
         cerr << "--- ERROR: Requirement file INACCESIBLE" << endl;
      }
      else {
         do {
            m_require[m_numRequires] = new Requirement();
            m_require[m_numRequires]->load(datafile);
            if (m_require[m_numRequires] && !datafile.fail()) {
               m_numRequires++;
            }
            else {
               delete m_require[m_numRequires];
            }
         } while (datafile);
         datafile.close();
      }
      cout << m_numRequires << " requirements loaded!" << endl;
      return m_numRequires;
   }


}