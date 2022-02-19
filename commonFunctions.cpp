#include <cctype>
#include "commonFunctions.h"

namespace yh {
   // Convert string of lowercase to STRING OF UPPERCASE
   const char* toUpper(char* destination, char* source) {
      int i;
      for (i = 0; source[i]; i++) {
         destination[i] = (char)toupper(source[i]);
      }
      destination[i] = '\0';
      return destination;
   }
}