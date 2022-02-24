#include <cctype>
#include "commonFunctions.h"

namespace yh {
   // Convert string of lowercase to STRING OF UPPERCASE
   const char* toUpperString(char* destination, char* source) {
      int i;
      for (i = 0; source[i]; i++) {
         destination[i] = (char)toupper(source[i]);
      }
      destination[i] = '\0';
      return destination;
   }
   // Convert character of lowercase to CHRACTER OF UPPERCASE
   char toUpperCharacter(char character) {
      return (char) toupper(character);
   }
}