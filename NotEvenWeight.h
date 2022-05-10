#ifndef YH_NOTEVENWEIGHT_H_
#define YH_NOTEVENWEIGHT_H_
#include "Weight.h"
namespace yh {
   class NotEvenWeight : public Weight {
      double m_eachWeight[15]{};

   public:
      NotEvenWeight() {};
      NotEvenWeight(const NotEvenWeight& weight);
      NotEvenWeight& operator=(const NotEvenWeight& weight);
      virtual ~NotEvenWeight() {};

      virtual double calculateWeight(int no);

      virtual std::ifstream& load(std::ifstream& ifstr);
      virtual std::ostream& display(std::ostream& ostr) const;
   };
}
#endif // !YH_NOTEVENWEIGHT_H_
