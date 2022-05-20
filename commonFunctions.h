#ifndef YH_COMMONFUNCTIONS_H_
#define YH_COMMONFUNCTIONS_H_

namespace yh {
   // Convert string of lowercase to STRING OF UPPERCASE
   const char* toUpperString(char* destination, char* source);

   // Convert character of lowercase to CHRACTER OF UPPERCASE
   char toUpperCharacter(char character);
   // Draw the number of seperator=
   void seperatorDouble(std::ostream& ostr, int num);
   // Copy character array dynamically
   void allocateCopy(char*& desc, const char* src);
   // Receive string & allocate dynamically
   char* getDynCstr(std::istream& istr, char delim='\n');
   // Receive integer within range
   int getint(int min, int max);
}

#endif // !YH_COMMONFUNCTIONS_H_
