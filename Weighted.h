#ifndef YH_WEIGHTED_H_
#define YH_WEIGHTED_H_
#include "iWeight.h"
namespace yh {
   class Weighted : public iWeight {
      char m_course[10]{};
      char m_type = 'N'; // W:Weekly A:Assignment Q:Quiz T:Test
      char m_assessName[15]{};
      double m_totalWeight{};
      int m_count{};
      int m_max{};
   protected:
      int m_equal{}; // 1:evenly 0:not evenly
   public:
      Weighted() {};
      Weighted(const Weighted& weight);
      Weighted& operator=(const Weighted& weight);
      virtual ~Weighted() {};
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
#endif // !YH_EQUALWEIGHTED_H_