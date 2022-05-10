#ifndef YH_IWEIGHT_H_
#define YH_IWEIGHT_H_
namespace yh {
   class iWeight {
   public:
      virtual ~iWeight() {};
      virtual const char* getCourse() const = 0;
      virtual char getType() const = 0;
      virtual const char* getRequireName() const = 0;
      virtual double getTotalWeight() const = 0;
      virtual int getCount() const = 0;
      virtual int getMax() const = 0;
      virtual double calculateWeight(int no) = 0;

      virtual std::ifstream& load(std::ifstream& ifstr) = 0;
      virtual std::ostream& display(std::ostream& ostr) const = 0;
   };
   std::ostream& operator<<(std::ostream& ostr, const iWeight& iw);
}
#endif //!YH_IWEIGHT_H_