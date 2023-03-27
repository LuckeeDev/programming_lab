#include <vector>

#ifndef LAB_230327_STATISTICS_H
#define LAB_230327_STATISTICS_H
namespace pf {
struct Statistics {
  double mean;
  double sigma;
  double mean_err;
  double median;
};

class Sample {
  std::vector<double> entries_;

 public:
  int size() const;

  void add(double x);

  std::vector<double> &entries();

  const std::vector<double> &entries() const;

  bool remove(double x);

  Statistics statistics() const;

  Sample &operator+=(const Sample &r);
};

Sample operator+(const Sample &l, const Sample &r);
}  // namespace pf
#endif  // LAB_230327_STATISTICS_H
