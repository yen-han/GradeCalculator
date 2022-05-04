#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include "Management.h"
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
      do {
         cout << "-------------------------------" << endl;
         cout << "Grades Calculator" << endl;
         cout << "Course: " << (m_course[0] == '\0' ? "N/A" : m_course) << endl;
         cout << "-------------------------------" << endl;
         selection = subMenu.run();
         if (selection!=5 && m_course[0] == '\0') selection = 5;

         switch (selection) {
            // 1 | View Grades
         case 1:
            viewGrades();
            cout << endl;
            break;
            // 2 | Modify Grades
         case 2:
            modifyGrades();
            break;
            // 3 | Modify weight
         case 3:
            break;
            // 4 | Requirement to Pass
         case 4:
            viewRequirements();
            break;
            // 5 | Change Course
         case 5:
            changeCourseCode();
            break;
            // 0 | Save & Exit
         case 0:
            sort();
            saveGrades();
            break;
         }
      } while (selection != 0);
      cout << endl<< "Exiting Grades Calculator" << endl;
   }
   // 1 | View Grades
   void Management::viewGrades() {
      sort();
      int foundRequire = searchRequirements(m_course);
      double subtotal = 0;
      char name[15] = { '\0' };
      cout << endl <<"<< "<< m_require[foundRequire]->getName(name, 1)<< " >>"<< endl;
      subtotal += viewTypeGrades('W', foundRequire);
      cout << endl << endl;
      cout << "<< " << m_require[foundRequire]->getName(name, 2) << " >>" << endl;
      subtotal += viewTypeGrades('A', foundRequire);
      cout << endl << endl;
      cout << "<< " << m_require[foundRequire]->getName(name, 3) << " >>" << endl;
      subtotal += viewTypeGrades('Q', foundRequire);
      cout << endl << endl;
      cout << "<< Test >>" << endl;
      subtotal += viewTypeGrades('T', foundRequire);
      cout << endl << endl;
      cout.setf(ios::fixed);
      cout.precision(2);
      cout << "Total mark : " << subtotal <<" % / 100 %" << endl;
      if (m_require[foundRequire]->getOverall() - subtotal >= 0) {
         cout << "Remaining  : " << m_require[foundRequire]->getOverall() - subtotal << " % To Pass";
      }
      else {
         cout << "Remaining  : 0 % To Pass";
      }
      cout.unsetf(ios::fixed);
      cout << endl;
   }

   double Management::viewTypeGrades(char type, int foundRequire) {
      double eachTotal = 0;
      cout << "No.      | ";
      for (int i = 0; i < m_numGrades; i++) {
         if (!strcmp(m_grades[i]->getCourse(), m_course)&& m_grades[i]->getType()==type) {

            cout << setw(7);
            cout << "#" << m_grades[i]->getNo() << " | ";
         }
      }
      cout << endl;
      cout << "Title    | ";
      for (int i = 0; i < m_numGrades; i++) {
         if (!strcmp(m_grades[i]->getCourse(), m_course) && m_grades[i]->getType() == type) {
            cout << setw(8);
            cout << m_grades[i]->getTitle() << " | ";
         }
      }
      cout << endl;
      cout << "Score    | ";
      for (int i = 0; i < m_numGrades; i++) {
         if (!strcmp(m_grades[i]->getCourse(), m_course) && m_grades[i]->getType() == type) {
            cout << setw(8);
            cout << m_grades[i]->getScore() << " | ";
         }
      }
      cout << endl;
      cout << "Full     | ";
      for (int i = 0; i < m_numGrades; i++) {
         if (!strcmp(m_grades[i]->getCourse(), m_course) && m_grades[i]->getType() == type) {
            cout << setw(8);
            cout.setf(std::ios::fixed);
            cout.precision(2);
            cout << m_grades[i]->getFullMark() << " | ";
            cout.unsetf(std::ios::fixed);
         }
      }
      cout << endl;
      cout << "Weighted | ";
      for (int i = 0; i < m_numGrades; i++) {
         if (!strcmp(m_grades[i]->getCourse(), m_course) && m_grades[i]->getType() == type) {
            cout << setw(8);
            cout << (m_require[foundRequire]->calculateWeight(m_grades[i]->getType())) << " | ";
         }
      }
      cout << endl;
      cout << "Total    | ";
      for (int i = 0; i < m_numGrades; i++) {
         if (!strcmp(m_grades[i]->getCourse(), m_course) && m_grades[i]->getType() == type) {
            cout << setw(8);
            cout << m_grades[i]->getScore() / m_grades[i]->getFullMark() * (m_require[foundRequire]->calculateWeight(m_grades[i]->getType())) << " | ";
            eachTotal += m_grades[i]->getScore() / m_grades[i]->getFullMark() * (m_require[foundRequire]->calculateWeight(m_grades[i]->getType()));
         }
      }
      return eachTotal;
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
         cout << endl;
         if (search(temp->getNo(), temp->getType()) > 0) {
            cout << "week: " << temp->getNo() << ", Type "<< temp->getType()<<" is already in the system." << endl << endl;
            delete temp;
         }
         else {
            if (temp) {
               Menu subMenu("Are you sure to insert?\n1 | Yes\n", 1);
               if (subMenu.run() == 1) {
                  m_grades[m_numGrades] = temp;
                  cout <<endl<< *m_grades[m_numGrades] << endl;
                  cout << "Grade Successfully inserted" << endl;
                  m_numGrades++;
               }
               else {
                  cin.ignore();
                  cout << "--- Aborted" << endl << endl;
               }
            }
            else {
               cout << "Invalid Grade" << endl;
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
      cout << "Type(W|weekly Q|quiz A|Assignment T|Test): ";
      cin >> type;
      foundIdx = search(week, type);
      if (foundIdx < 0) {
         cout << "---ERROR: Grade not found" << endl;
      }
      else {
         cout <<"--- Before"<< endl<<* m_grades[foundIdx] << endl;
         Grade* temp = new Grade();
         temp->read(cin, m_course);
         cout <<endl<<"--- After"<< endl << *temp << endl;
         Menu subMenu("Are you sure to modify?\n1 | Yes\n", 1);
         if (subMenu.run() == 1) {
            m_grades[foundIdx] = temp;
            cout << "Grade Successfully modified" << endl;
         }
         else {
            cin.ignore();
            cout << "--- Aborted" << endl << endl;
         }
      }
   }
   // Search grade by week & type
   int Management::search(int week, char type) {
      int foundIdx = -1;
      for (int i = 0; i < m_numGrades; i++) {
         if (!strcmp(m_grades[i]->getCourse(),m_course) && m_grades[i]->getNo() == week && m_grades[i]->getType() == type) {
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
      cout << "Type(W|weekly Q|quiz A|Assignment T|Test): ";
      cin >> type;
      foundIdx = search(week, type);
      if (foundIdx < 0) {
         cout << "---ERROR: Grade not found" << endl;
      }
      else {
         cout << "--- Grade to be Remove" << endl << *m_grades[foundIdx] << endl;
         Menu subMenu("Are you sure to delete?\n1 | Yes\n", 1);
         if (subMenu.run() == 1) {
            remove(foundIdx);
            cout << "Grade deleted" << endl;
         }
         else {
            cin.ignore();
            cout << "--- Aborted" << endl << endl;
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
       cout << *m_require[searchRequirements(m_course)] << endl;
   }

   // 5 | Change Course
   void Management::changeCourseCode() {
      cin.ignore();
      bool done = false;
      char inputCourse[10];
      do {
         cout << "Enter Course Code(Enter to exit) : ";
         cin.get(inputCourse, 10, '\n');
         cin.ignore(100, '\n');
         // Ignore case sensitivity
         toUpperString(m_course, inputCourse);
         for (int i = 0; i < m_numGrades; i++) {
            if (!strcmp(m_grades[i]->getCourse(), m_course)) {
               done = true;
            }
         }
         if (!done) {
          cout << "--- ERROR: Grade of the Course is not found" << endl<<endl;
          Menu subMenu("Do you want to add the course?\n1 | Yes\n", 1);
          if (subMenu.run() == 1) {
             insertGrades();
             done = true;
          }
          else {
             cin.ignore();
             cout << "--- Aborted" << endl << endl;
          }
         }
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
      bool found = false;
      do {
         cout << "Enter file name: ";
         m_file = getDynCstr(cin, '\n');

         ifstream datafile(m_file);
         if (!datafile) {
            // No file
            datafile.close();
            cerr << "--- ERROR: " << m_file << " INACCESIBLE" << endl << endl;
         }
         else {
            found = true;
            do {
               m_grades[m_numGrades] = new Grade();
               m_grades[m_numGrades]->load(datafile);
               if (m_grades[m_numGrades] && !datafile.fail()) {
                  m_numGrades++;
               }
               else {
                  delete m_grades[m_numGrades];
               }
            } while (datafile);
            datafile.close();
            cout << m_numGrades << " grades loaded!" << endl;
         }
      } while (!found);
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

   int Management::searchRequirements(const char* course) {
      int foundIdx = -1;
      for (int i = 0; i < m_numRequires; i++) {
         if (!strcmp(m_require[i]->getCourse(), m_course)) {
            foundIdx = i;
         }
      }
      return foundIdx;
   }

   // Sorting: Numerically by m_no
   void Management::sort() {
      int i, j, toCompare;
      for (i = 0; i < m_numGrades-1; i++) {
         toCompare = i;
         for (j = i+1; j < m_numGrades; j++) {
            if (m_grades[toCompare]->getNo() > m_grades[j]->getNo()) {
               Grade* temp = m_grades[toCompare];
               m_grades[toCompare] = m_grades[j];
               m_grades[j] = temp;
               //delete temp;
            }
         }
      }
      cout << "sorted" << endl;
   }
   



}