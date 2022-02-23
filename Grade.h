#ifndef YH_GRADE_H_
#define YH_GRADE_H_
namespace yh {
   class Grade {
      char m_courseCode[8];
      int m_week; // To sort
      char* m_title;
      double m_score;
      double m_fullMark;
      char m_type; // Q: quiz, T: test, A: assignment, N: none

      // Reset recognized invalid state
      Grade& resetInfo();
      // Deallocate m_title
      void deallocate();

   public:
      // Constructors
      Grade();
      Grade(const char* courseCode, int week, const char* title, char type, double score=0, double fullMark = 100);
      // Destructor
      ~Grade();
      // Copy constructor
      Grade(const Grade& toCopyFrom);
      // Copy assignment
      Grade& operator=(const Grade& toCopyFrom);

      // Create & SET GRADE
      Grade& setInfo(const char* courseCode, int week, const char* title, char type, double score = 0, double fullMark = 100);
      // Create & SET TITLE
      Grade& setTitle(const char* title);
      // Create & SET SCORE 
      Grade& setScore(double score);
      // Create & SET FULL MARK 
      Grade& setFullMark(double fullMark);

      // GET WEEK#
      int getWeek() const;
      // GET TITLE of grade
      const char* getTitle() const;
      // GET SCORE 
      double getScore() const;
      // GET FULL MARK (out of)
      double getFullMark() const;
      // GET TYPE
      char getType() const;
      // Get weighted score on each
      double getWeightedScore() const;

      // Report grades
      std::ostream& display() const;
      // Check if it is VALID GRADES(have score and type of T,Q,A)
      bool isValid() const;
   };
   // Read All Weight Setting On the course
   extern void readWeightSetting(const char* searchSubject);
   // Read ALL grads on the data file
   extern int readGrades(double& totalScore, const char* searchSubject);

   extern std::ostream& displayData(const char* searchSubject, const int numGrades);
   // Insert/Create New grades
   extern void insertGrades(const char* searchSubject, int& numGrades);

   extern void deleteGrades(const char* searchSubject, int& numGrades);
   extern void modifyWeightSettingMenu(const char* searchSubject);
}

#endif // !YH_GRADE_H_