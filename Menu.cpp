#include <iostream>
#include "Menu.h"
#include "commonFunctions.h"
namespace yh {
   Menu::Menu(const char* list, unsigned int numOption) {
      if (list != nullptr) {
         allocateCopy(m_list, list);
         m_numOption = numOption;
      }
   }
   Menu::~Menu() {
      delete[] m_list;
   }

   unsigned int Menu::run() const {
      std::cout << m_list << "0 | Exit" << std::endl << ">>> ";
      return getint(0, m_numOption);
   }
}