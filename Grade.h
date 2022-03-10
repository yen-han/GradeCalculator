#ifndef YH_GRADE_H_
#define YH_GRADE_H_
namespace yh {
   class Grade {
      char m_courseCode[10];
      int m_week; // To sort
      char* m_title;
      double m_score;
      double m_fullMark;
      char m_type; // Q: quiz, T: test, A: assignment, N: none

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

      // Reset recognized invalid state
      Grade& resetInfo();
      // Deallocate m_title
      void deallocate();
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
   extern void readWeightSetting(const char* searchCourse);
   // Read ALL grads on the data file
   extern int readGrades(double& totalScore, const char* searchCourse);
   // Display Grades in format
   extern std::ostream& displayGrades(const char* searchCourse, const int numGrades);

   extern std::ostream& displayQuiz(const char* searchCourse, const int numGrades);

   extern std::ostream& displayAssignment(const char* searchCourse, const int numGrades);
   extern std::ostream& displayTest(const char* searchCourse, const int numGrades);

   // Insert/Create New grades
   extern void insertGrades(const char* searchCourse, int& numGrades);
   // Update existing grades
   extern void updateGrades(const char* searchCourse, int& numGrades);
   // Delete existing grades
   extern void deleteGrades(const char* searchCourse, int& numGrades);
   
   // Get Grade input 
   void getGradeInput(int& week, char* title, char& type, double& score, double& fullMark);
   // Find matched grades by week, type info
   int findMatchedIndex(const int numGrades);

   // Display Weight setting
   void displayWeightSetting(const char* searchCourse);
   // Update QUIZ Weight setting
   void modifyQuizWeightSetting();
   // Update ASSIGNMENT Weight setting
   void modifyAssignWeightSetting();
   // Update TEST Weight setting
   void modifyTestWeightSetting();
   void selectionSort(int numGrades);

   // Delete Dynamic allocated memory
   extern void clearMemory();
}

#endif // !YH_GRADE_H_