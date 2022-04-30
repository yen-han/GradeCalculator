#ifndef YH_MENU_H_
#define YH_MENU_H_
namespace yh {
   class Menu {
      char* m_list{};
      unsigned int m_numOption{};

   public:
      Menu(const char* list, unsigned int numOption);
      Menu(const Menu& menu) = delete;
      Menu& operator=(const Menu& menu) = delete;
      ~Menu();

      unsigned int run() const;
   };
}
#endif // !YH_MENU_H_