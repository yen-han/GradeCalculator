#ifndef YH_GRADE_H_
#define YH_GRADE_H_
namespace yh {
   class Grade {
      char m_courseCode[10]{};
      int m_no{}; // To sort
      char m_type = 'N'; // W:Weekly Q:Quiz T:Test, A:Assignment, N:None
      char* m_title{};
      double m_score{};
      double m_fullMark{};
      int m_best{}; // 1:Count 0:Drop
   public:
      // Constructors
      Grade() {};
      Grade(const char* courseCode, int no, const char* title, char type, double score=0, double fullMark = 100);
      // Destructor
      virtual ~Grade();
      // Copy constructor
      Grade(const Grade& grade);
      // Copy assignment
      Grade& operator=(const Grade& grade);

      // Deallocate m_title
      void deallocate();
      // Create & SET GRADE
      Grade& setInfo(const char* courseCode, int no, const char* title, char type, double score = 0, double fullMark = 100);
      // Create & SET SCORE 
      Grade& setScore(double score);
      // Create & SET FULL MARK 
      Grade& setFullMark(double fullMark);

      const char* getCourse() const;
      // GET WEEK#
      int getNo() const;
      // GET TITLE of grade
      const char* getTitle() const;
      // GET SCORE 
      double getScore() const;
      // GET FULL MARK (out of)
      double getFullMark() const;
      // GET TYPE
      char getType() const;
      int getBest() const;
      void setBest(int best);

      // Report grades
      std::ostream& display(std::ostream& ostr) const;
      // Check if it is VALID GRADES(have score and type of T,Q,A)
      bool isValid() const;
      
      std::ofstream& save(std::ofstream& ofstr) const;
      //Read file
      std::ifstream& load(std::ifstream& ifstr);
      std::istream& read(std::istream& istr, const char* course);
   };

   std::ostream& operator<<(std::ostream& ostr, const Grade& g);
}

#endif // !YH_GRADE_H_