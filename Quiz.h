#ifndef YH_QUIZ_H_
#define YH_QUIZ_H_
namespace yh {
   class Quiz {
      int m_courseCode;
      char* m_quizName;
      char m_unit[4];
      double m_currentMark;
      double m_weighted;
      double m_max;
      void resetInfo();

   public:
      Quiz(const char* quizName, double weighted=1, double currentMark=0, double max=100);
      Quiz();
      ~Quiz();
      Quiz& setQuizName(const char* quizName);
      void setUnit(const char unit);
      Quiz& setCurrentMark(double mark);
      Quiz& setWeighted(double maxMark);
      Quiz& setMax(double maxMark);
      void remaingMarkToPass();
      const char* getQuizName() const;
      double getCurrentMark() const;
      double getMaxMark() const;
      double getWeighted() const;
      double getTotal() const;
      void display() const;
      void isValid() const;

   };
}

#endif // !YH_QUIZ_H_