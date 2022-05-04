#ifndef YH_REQUIREMENT_H_
#define YH_REQUIREMENT_H_
#include <iostream>
#include "Weight.h"
namespace yh {
   class Requirement {
      char m_courseCode[10]{};
      double m_overall{};

      char m_require1[15]{};
      char m_type1 = 'N';
      double m_weight1{};
      int m_count1{};
      int m_max1{};
      int m_equal1{};

      char m_require2[15]{};
      char m_type2 = 'N';
      double m_weight2{};
      int m_count2{};
      int m_max2{};
      int m_equal2{};

      char m_require3[15]{};
      char m_type3 = 'N';
      double m_weight3{};
      int m_count3{};
      int m_max3{};
      int m_equal3{};

      char m_type4 ='T';
      double m_test{};
      int m_maxTest{};
      int m_equalTest{};

      char* m_comment1{};
      char* m_comment2{};
      //Weight* m_weight[100]{};
     // int m_numWeight{};
   protected:
      int getCount(int num) const;
      double getWeight(int num) const;
   public:
      Requirement() {};
      Requirement(const Requirement& r);
      Requirement& operator=(const Requirement& r);
      virtual ~Requirement();
      const char* getCourse() const;
      double getOverall() const;
      double calculateWeight(char type);
      const char* getName(char* name, int num)const;

      std::ostream& display(std::ostream& ostr) const;
      std::ifstream& load(std::ifstream& ifstr);
   };

   std::ostream& operator<<(std::ostream& ostr, const Requirement& r);
}
#endif //! YH_REQUIREMENT_H_
