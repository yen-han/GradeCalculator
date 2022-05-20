#ifndef YH_NOTEQUALWEIGHTED_H_
#define YH_NOTEQUALWEIGHTED_H_
#include "Weighted.h"
namespace yh {
   class NotEqualWeighted : public Weighted {
      double m_eachWeight[15]{};

   public:
      NotEqualWeighted() {};
      NotEqualWeighted(const NotEqualWeighted& weight);
      NotEqualWeighted& operator=(const NotEqualWeighted& weight);
      virtual ~NotEqualWeighted() {};

      virtual double calculateWeight(int no);

      virtual std::ifstream& load(std::ifstream& ifstr);
      virtual std::ostream& display(std::ostream& ostr) const;
   };
}
#endif // !YH_NOTEQUALWEIGHTED_H_
