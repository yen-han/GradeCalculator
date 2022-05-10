#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include "Management.h"
#include "commonFunctions.h"
#include "Menu.h"
#include "Weight.h"
#include "NotEvenWeight.h"
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
   void Management::deallocateWeights() {
      for (int i = 0; i < m_numWeight; i++) {
         delete m_weight[i];
      }
      m_numWeight = 0;
   }

   Management::~Management() {
      deallocateGrades();
      deallocateRequirements();
      deallocateWeights();
   }

   void Management::run() {
      int selection;
      Menu subMenu("1 | View Grades\n2 | Modify grades\n3 | Requirement to Pass\n4 | View Grade Chart\n5 | Change Course\n", 5);
      cout << "Starting Grades Calculator" << endl;
      loadGrades();
      loadRequirements();
      loadWeights();
      do {
         cout << "-------------------------------" << endl;
         cout << "Grades Calculator" << endl;
         cout << "Course: " << (m_course[0] == '\0' ? "N/A" : m_course) << endl;
         cout << "-------------------------------" << endl;
         selection = subMenu.run();
         if ((selection == 1 || selection==2||selection==3) && m_course[0] == '\0') selection = 5;

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
            // 3 | Requirement to Pass
         case 3:
            viewRequirements();
            break;
            // 4 | View Grade Chart
         case 4:
            gradeChart();
            break;
            // 5 | Change Course
         case 5:
            changeCourseCode();
            break;
            // 0 | Save & Exit
         case 0:
            sortByNo();
            saveGrades();
            break;
         }
      } while (selection != 0);
      cout << endl<< "Exiting Grades Calculator" << endl;
   }
   // 1 | View Grades
   void Management::viewGrades() {
      int foundWeight = searchWeights(m_course, 'W');
      int foundRequire = searchRequirements(m_course);
      double subtotal = 0;
      cout << endl <<"<< "<< m_weight[foundWeight]->getRequireName() << " >>" << endl;
      subtotal += viewTypeGrades('W', foundWeight);
      cout << endl << endl;

      foundWeight = searchWeights(m_course, 'A');
      cout << "<< " << m_weight[foundWeight]->getRequireName() << " >>" << endl;
      subtotal += viewTypeGrades('A', foundWeight);
      cout << endl << endl;

      foundWeight = searchWeights(m_course, 'Q');
      if (foundWeight > -1) {
         cout << "<< " << m_weight[foundWeight]->getRequireName() << " >>" << endl;
         subtotal += viewTypeGrades('Q', foundWeight);
         cout << endl << endl;
      }
      foundWeight = searchWeights(m_course, 'T');
      cout << "<< " << m_weight[foundWeight]->getRequireName()  << " >>" << endl;
      subtotal += viewTypeGrades('T', foundWeight);
      cout << endl << endl;

      cout.setf(ios::fixed);
      cout.precision(2);
      cout << "Total mark : " << subtotal <<" % / 100 %" << endl;
      if (m_require[foundRequire]->getOverall() - subtotal >= 0) {
         cout << "Remaining  : " << m_require[foundRequire]->getOverall() - subtotal << " % To Pass";
      }
      else {
         cout << "Remaining  : 0 % To Pass"<<endl;
         cout << "Grade      : ";
         letterGrade(subtotal);
      }
      cout.unsetf(ios::fixed);
      cout << endl;
   }
   double Management::viewTypeGrades(char type, int foundWeight) {
      checkForBestMark(type, foundWeight);
      sortByNo();
      double eachTotal = 0;
      cout << "No.      | ";
      for (int i = 0; i < m_numGrades; i++) {
         if (!strcmp(m_grades[i]->getCourse(), m_course)&& m_grades[i]->getType()==type) {
            if (m_grades[i]->getBest()==1) {
               (m_grades[i]->getNo()>9? cout << setw(5): cout << setw(6));
               cout << "*";

            }
            else {
               (m_grades[i]->getNo() > 9 ? cout << setw(6) : cout << setw(7));
            }
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
            cout.setf(std::ios::fixed);
            cout.precision(1);
            cout << m_grades[i]->getScore() << " | ";
            cout.unsetf(std::ios::fixed);
         }
      }
      cout << endl;
      cout << "Full     | ";
      for (int i = 0; i < m_numGrades; i++) {
         if (!strcmp(m_grades[i]->getCourse(), m_course) && m_grades[i]->getType() == type) {
            cout << setw(8);
            cout.setf(std::ios::fixed);
            cout.precision(0);
            cout << m_grades[i]->getFullMark() << " | ";
            cout.unsetf(std::ios::fixed);
         }
      }
      cout << endl;
      cout << "Weighted | ";
      for (int i = 0; i < m_numGrades; i++) {
         if (!strcmp(m_grades[i]->getCourse(), m_course) && m_grades[i]->getType() == type) {
            cout << setw(8);
            cout.setf(std::ios::fixed);
            cout.precision(2);
            cout << m_weight[foundWeight]->calculateWeight(
               m_grades[i]->getNo()) << " | ";
            cout.unsetf(std::ios::fixed);
         }
      }
      cout << endl;
      cout << "Total    | ";
      for (int i = 0; i < m_numGrades; i++) {
         if (!strcmp(m_grades[i]->getCourse(), m_course) && m_grades[i]->getType() == type) {
            cout << setw(8);
            cout.setf(std::ios::fixed);
            cout.precision(2);
            cout << m_grades[i]->getScore() / m_grades[i]->getFullMark() * m_weight[foundWeight]->calculateWeight(
               m_grades[i]->getNo()) << " | ";
            cout.unsetf(std::ios::fixed);
            if (m_weight[foundWeight]->getCount() == m_weight[foundWeight]->getMax()) {
               eachTotal += m_grades[i]->getScore() / m_grades[i]->getFullMark() * m_weight[foundWeight]->calculateWeight(
                  m_grades[i]->getNo());

            }
            else {
               if (m_grades[i]->getBest()) {
                  eachTotal += m_grades[i]->getScore() / m_grades[i]->getFullMark() * m_weight[foundWeight]->calculateWeight(
                     m_grades[i]->getNo());

               }
            }
         }
      }
      if (m_weight[foundWeight]->getCount() == m_weight[foundWeight]->getMax()) {
         cout.setf(std::ios::fixed);
         cout.precision(2);
         cout << endl << endl << "- Sum of " << m_weight[foundWeight]->getRequireName() << "s: " << eachTotal << "% / " << m_weight[foundWeight]->getTotalWeight() << "%";
         cout.unsetf(std::ios::fixed);
      }
      else {
         cout.setf(std::ios::fixed);
         cout.precision(2);
         cout << endl << endl << "- Best " << m_weight[foundWeight]->getCount() << " of " << m_weight[foundWeight]->getRequireName() << "s: " << eachTotal << " % / " << m_weight[foundWeight]->getTotalWeight() << " % ";
         cout.unsetf(std::ios::fixed);
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
            cout << "week: " << temp->getNo() << ", Type "<< temp->getType()<<" is already in the system.";
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
                  cout << "--- Aborted" << endl;
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
      cout << endl << "Type(W|weekly Q|quiz A|Assignment T|Test): ";
      cin >> type;
      cout << "No. : ";
      cin >> week;
      foundIdx = search(week, type);
      cout << endl;
      if (foundIdx < 0) {
         cout << "--- ERROR: Grade not found" ;
      }
      else {
         cout << "--- Before"<< endl<<* m_grades[foundIdx] << endl;
         Grade* temp = new Grade();
         temp->read(cin, m_course);
         cout <<endl<<"--- After"<< endl << *temp << endl;
         Menu subMenu("Are you sure to modify?\n1 | Yes\n", 1);
         if (subMenu.run() == 1) {
            m_grades[foundIdx] = temp;
            cout << "Grade Successfully modified";
         }
         else {
            cin.ignore();
            cout << "--- Aborted" << endl << endl;
         }
      }
   }
   // Search grade by week & type
   int Management::search(int no, char type) {
      int foundIdx = -1;
      for (int i = 0; i < m_numGrades; i++) {
         if (!strcmp(m_grades[i]->getCourse(),m_course) && m_grades[i]->getNo() == no && m_grades[i]->getType() == type) {
            foundIdx = i;
         }
      }
      return foundIdx;
   }
   // 2-3 | Delete Grades
   void Management::removeGrades() {
      int foundIdx = -1;
      int no; char type;
      cout << "Type(W|weekly Q|quiz A|Assignment T|Test): ";
      cin >> type;
      cout << "No. : ";
      cin >> no;
      foundIdx = search(no, type);
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
   // 3 | View requirement to Pass
   void Management::viewRequirements() {
      cout << endl;
      m_require[searchRequirements(m_course)]->displayTop(cout);
      if(searchWeights(m_course, 'W')!=-1) m_weight[searchWeights(m_course, 'W')]->display(cout);
      if (searchWeights(m_course, 'A') != -1) m_weight[searchWeights(m_course, 'A')]->display(cout);
      if (searchWeights(m_course, 'Q') != -1) m_weight[searchWeights(m_course, 'Q')]->display(cout);
      if (searchWeights(m_course, 'T') != -1) m_weight[searchWeights(m_course, 'T')]->display(cout);
      m_require[searchRequirements(m_course)]->displayBottom(cout);
      cout << endl;
   }
   // 4 | View Grade Chart
   void Management::gradeChart() {
      cout << endl;
      seperatorDouble(cout, 30);
      cout << "Letter\tPoint\tPercentage" << endl;
      cout << " A+\t 4.0\t 90~100%" << endl;
      cout << " A\t 4.0\t 80~89%" << endl;
      cout << " B+\t 3.5\t 75~79%" << endl;
      cout << " B\t 3.0\t 70~74%" << endl;
      cout << " C+\t 2.5\t 65~69%" << endl;
      cout << " C\t 2.0\t 60~64%" << endl;
      cout << " D+\t 1.5\t 55~59%" << endl;
      cout << " D\t 1.0\t 50~54%" << endl;
      cout << " F\t 0.0\t 0~49%" << endl;
      seperatorDouble(cout, 30);
      cout << endl;
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
   // Load grades
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
   // Load requirements
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
            if (datafile) {
               m_require[m_numRequires]= new Requirement();
               m_require[m_numRequires]->load(datafile);
               if (m_require[m_numRequires] && !datafile.fail()) {
                  m_numRequires++;
               }
               else {
                  delete m_require[m_numRequires];
               }
            }

         } while (datafile);
         datafile.close();
      }
      cout << m_numRequires << " requirements loaded!" << endl;
      return m_numRequires;
   }
   // Load weights
   int Management::loadWeights() {
      deallocateWeights();
      ifstream datafile("weight.csv");
      if (!datafile) {
         // No file
         datafile.close();
         cerr << "--- ERROR: Weight file INACCESIBLE" << endl;
      }
      else {
         do {
            char ch = datafile.peek();
            if (ch == '1') {
               m_weight[m_numWeight] = new Weight();
            }
            else if (ch == '0') {
               m_weight[m_numWeight] = new NotEvenWeight();
            }
            else {
               datafile.setstate(std::ios::failbit);
            }

            if (datafile) {
               m_weight[m_numWeight]->load(datafile);
               if (m_weight[m_numWeight] && !datafile.fail()) {
                  m_numWeight ++;
               }
               else {
                  delete m_weight[m_numWeight];
               }
            }
         } while (datafile);
         datafile.close();
      }
      cout << m_numWeight << " weights loaded!" << endl;
      return m_numWeight;

   }
   int Management::searchRequirements(const char* course) {
      int foundIdx = -1;
      for (int i = 0; i < m_numRequires; i++) {
         if (!strcmp(m_require[i]->getCourse(), m_course) ) {
            foundIdx = i;
         }
      }
      return foundIdx;
   }

   int Management::searchWeights(const char* course, char type) {
      int foundIdx = -1;
      for (int i = 0; i < m_numWeight; i++) {
         if (!strcmp(m_weight[i]->getCourse(), m_course)&& m_weight[i]->getType()==type) {
            foundIdx = i;
         }
      }
      return foundIdx;
   }

   void Management::letterGrade(double subtotal) {
      if (subtotal >= 90) cout << "A+ (4.0)";
      else if (subtotal >= 80) cout << "A (4.0)";
      else if (subtotal >= 75) cout << "B+ (3.5)";
      else if (subtotal >= 70) cout << "B (3.0)";
      else if (subtotal >= 65) cout << "C+ (2.5)";
      else if (subtotal >= 60) cout << "C (2.0)";
      else if (subtotal >= 55) cout << "D+ (1.5)";
      else if (subtotal >= 50) cout << "D (1.0)";
      else {
         cout << "F (0.0)";
      }
   }

   // Sorting: Numerically by m_no
   void Management::sortByNo() {
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
   }
   // Check for best mark
   void Management::checkForBestMark(char type, int foundWeight) {
      if (m_weight[foundWeight]->getCount() < m_weight[foundWeight]->getMax()) {
         int i, j, toCompare;
         for (i = 0; i < m_numGrades - 1; i++) {
            if (!strcmp(m_grades[i]->getCourse(), m_course)&& m_grades[i]->getType() == type) {
               toCompare = i;
               for (j = i + 1; j < m_numGrades; j++) {
                  if (!strcmp(m_grades[toCompare]->getCourse(), m_grades[j]->getCourse()) 
                     && m_grades[toCompare]->getType() == m_grades[j]->getType()
                     && (m_grades[toCompare]->getScore() / m_grades[toCompare]->getFullMark() * m_weight[foundWeight]->calculateWeight(
                        m_grades[toCompare]->getNo())) < (m_grades[j]->getScore() / m_grades[j]->getFullMark() * m_weight[foundWeight]->calculateWeight(
                           m_grades[j]->getNo()))) {
                     Grade* temp = m_grades[toCompare];
                     m_grades[toCompare] = m_grades[j];
                     m_grades[j] = temp;
                     //delete temp;
                  }
               }
            }

         }
         for (i = 0, j = 0; j < m_weight[foundWeight]->getCount() && i < m_numGrades; i++) {
            if (!strcmp(m_grades[i]->getCourse(), m_course) && m_grades[i]->getType() == type ) {
               m_grades[i]->setBest(1);
               j++;
            }
         }
      }
   }

}