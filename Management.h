#ifndef YH_MANAGEMENT_H_
#define YH_MANAGEMENT_H_
#include "Grade.h"
#include "Requirement.h"
namespace yh {
   const int max = 100;

   class Management {
      char* m_file{};
      char m_course[10]{};
      Grade* m_grades[max]{};
      int m_numGrades{};
      Requirement* m_require[max]{};
      int m_numRequires{};

      void deallocateGrades();
      void deallocateRequirements();
      void viewGrades();
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
   public: 
      Management() {};
      Management(const Management&) = delete;
      Management& operator=(const Management&) = delete;
      virtual ~Management();
      void run();

   };
}
#endif YH_MANAGEMENT_H_