#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include "Management.h"
using namespace std;
using namespace yh;

// TO DEVELOP
// ADD EVERY VALIDATION
// Sort for the best # quiz
// Modify weights
// list stored course

void copyfile(const char* to, const char* from) {
   std::ifstream in(from);
   std::ofstream out(to);
   char ch;
   while (in.get(ch)) out.put(ch);
}

int main() {
   copyfile("grade.csv", "grade_root.csv");
   copyfile("requirement.csv", "requirement_root.csv");
   copyfile("weight.csv", "weight_root.csv");
   Management().run();
   return 0;
}

