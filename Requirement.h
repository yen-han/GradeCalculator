#ifndef YH_REQUIREMENT_H_
#define YH_REQUIREMENT_H_
namespace yh {
   class Requirement {
      char m_courseCode[10]{};
      double m_overall{};
      char* m_comment1{};
      char* m_comment2{};

   public:
      Requirement() {};
      Requirement(const Requirement& r);
      Requirement& operator=(const Requirement& r);
      virtual ~Requirement();
      virtual const char* getCourse() const;
      virtual double getOverall() const;

      virtual std::ostream& displayTop(std::ostream& ostr) const;
      virtual std::ostream& displayBottom(std::ostream& ostr) const;
      virtual std::ifstream& load(std::ifstream& ifstr);
   };
}
#endif //! YH_REQUIREMENT_H_
