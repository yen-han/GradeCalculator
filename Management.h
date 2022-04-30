#ifndef YH_MANAGEMENT_H_
#define YH_MANAGEMENT_H_
#include "Grade.h"
namespace yh {
   const int max_grades = 100;

   class Management {
      char* m_file{};
      char m_course[10]{};
      Grade* m_grades[max_grades]{};
      int m_numGrades{};

      void deallocateGrades();
      void viewGrades();
      void modifyGrades();
      void insertGrades();
      void updateGrades();
      int search(int week, char type);
      void removeGrades();
      void remove(int index);
      void changeCourseCode();
      void saveGrades();
      int loadGrades();
   public: 
      Management() {};
      Management(const Management&) = delete;
      Management& operator=(const Management&) = delete;
      virtual ~Management();
      void run();
   };
}
#endif YH_MANAGEMENT_H_