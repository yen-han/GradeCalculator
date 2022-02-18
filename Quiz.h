#ifndef YH_QUIZ_H_
#define YH_QUIZ_H_
namespace yh {
   class Quiz {
      int m_courseCode;
      char* m_quizName;
      double m_currentMark;
      double m_weighted;
      double m_max;
      void resetInfo();

   public:
      bool read(FILE* fptr);
      Quiz(const char* quizName, double weighted=1, double currentMark=0, double max=100);
      Quiz();
      ~Quiz();
      Quiz& setInfo(const char* quizName, double weighted = 1, double currentMark = 0, double max = 100);
      Quiz& setQuizName(const char* quizName);
      Quiz& setCurrentMark(double mark);
      Quiz& setWeighted(double maxMark);
      Quiz& setMax(double maxMark);
      void remaingMarkToPass();
      const char* getQuizName() const;
      double getCurrentMark() const;
      double getMaxMark() const;
      double getWeighted() const;
      double getTotal() const;
      std::ostream& display() const;
      bool isValid() const;

   };
   //extern bool read(FILE* fptr);
}

#endif // !YH_QUIZ_H_