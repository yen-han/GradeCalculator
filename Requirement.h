#ifndef YH_REQUIREMENT_H_
#define YH_REQUIREMENT_H_
namespace yh {
   class Requirement {
      char m_courseCode[10]{};
      double m_overall{};

      char m_require1Name[10]{};
      double m_require1{};
      int m_count1{};
      int m_max1{};

      char m_require2Name[10]{};
      double m_require2{};
      int m_count2{};
      int m_max2{};

      char m_require3Name[10]{};
      double m_require3{};
      int m_count3{};
      int m_max3{};

      double m_test{};
      int m_maxTest{};
      char* m_comment1{};
      char* m_comment2{};
   public:
      Requirement() {};
      Requirement(const Requirement& r);
      Requirement& operator=(const Requirement& r);
      virtual ~Requirement();
      const char* getCourse() const;
      double getOverall() const;

      std::ostream& display(std::ostream& ostr) const;
      std::ifstream& load(std::ifstream& ifstr);
   };

   std::ostream& operator<<(std::ostream& ostr, const Requirement& r);
}
#endif YH_REQUIREMENT_H_
