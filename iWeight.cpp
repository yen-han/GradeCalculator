#include <fstream>
#include <iostream>
#include "iWeight.h"
namespace yh {
   std::ostream& operator<<(std::ostream& ostr, const iWeight& iw) {
      return iw.display(ostr);
   }

}