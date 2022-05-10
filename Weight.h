#ifndef YH_WEIGHT_H_
#define YH_WEIGHT_H_
#include "iWeight.h"
namespace yh {
   class Weight : public iWeight {
      char m_course[10]{};
      char m_type = 'N'; // W:Weekly A:Assignment Q: Quiz T:Test
      char m_require[15]{};
      double m_totalWeight{};
      int m_count{};
      int m_max{};
   protected:
      int m_equal{}; // 1:evenly 0:not evenly
   public:
      Weight() {};
      Weight(const Weight& weight);
      Weight& operator=(const Weight& weight);
      virtual ~Weight() {};
      virtual const char* getCourse() const;
      virtual char getType() const;
      virtual const char* getRequireName() const;
      virtual double getTotalWeight() const;
      virtual int getCount() const;
      virtual int getMax() const;
      virtual double calculateWeight(int no);

      virtual std::ifstream& load(std::ifstream& ifstr);
      virtual std::ostream& display(std::ostream& ostr) const;
   };
}
#endif // !YH_WEIGHT_H_