#ifndef YH_COMMONFUNCTIONS_H_
#define YH_COMMONFUNCTIONS_H_

namespace yh {
   // Convert string of lowercase to STRING OF UPPERCASE
   const char* toUpperString(char* destination, char* source);

   // Convert character of lowercase to CHRACTER OF UPPERCASE
   char toUpperCharacter(char character);
   void seperatorDouble();
   void allocateCopy(char*& desc, const char* src);
   int getint(int min, int max);
   char* getDynCstr(std::istream& istr, char delim='\n');
}

#endif // !YH_COMMONFUNCTIONS_H_
