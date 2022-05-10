#ifndef YH_MANAGEMENT_H_
#define YH_MANAGEMENT_H_
#include "Grade.h"
#include "Requirement.h"
#include "iWeight.h"
namespace yh {
   const int max = 100;

   class Management {
      char* m_file{};
      char m_course[10]{};
      Grade* m_grades[max]{};
      int m_numGrades{};
      Requirement* m_require[max]{};
      int m_numRequires{};
      iWeight* m_weight[max]{};
      int m_numWeight{};

      void deallocateGrades();
      void deallocateRequirements();
      void deallocateWeights();
      //void viewCourse();
      void viewGrades();
      void letterGrade(double subtotal);
      double viewTypeGrades(char type, int foundRequire);
      void modifyGrades();
      void insertGrades();
      void updateGrades();
      int search(int week, char type);
      void removeGrades();
      void remove(int index);
      void viewRequirements();
      void changeCourseCode();
      void saveGrades();
      int loadGrades();
      int loadRequirements();
      int loadWeights();
      int searchRequirements(const char* course);
      int searchWeights(const char* course, char type);
      void gradeChart();
      void sortByNo();
      void checkForBestMark(char type, int foundWeight);
   public: 
      Management() {};
      Management(const Management&) = delete;
      Management& operator=(const Management&) = delete;
      virtual ~Management();
      void run();

   };
}
#endif //!YH_MANAGEMENT_H_