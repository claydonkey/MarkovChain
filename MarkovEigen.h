#ifndef MARKOVEIGEN_H
  #define MARKOVEIGEN_H


  #include<cstdlib>
  #include <vector>
  #include <cmath>
  #include <stdint.h>
  #include <complex>


  #include <Eigen/Core>
  #include <Eigen/unsupported/Eigen/MatrixFunctions>


using namespace std;

/***
 *class by composition
 *

 */
class MarkovEigen {
private:


protected:


public:
  double * a;
  double T = 0.0;
  int kSize = 0;
  Eigen::MatrixXd marMat;
  Eigen::IOFormat CleanFmt;
  explicit MarkovEigen(const int size);
  explicit MarkovEigen(const int size, Eigen::MatrixXd mat);
  explicit MarkovEigen(const int size, double T);
  void initStreak(double prob);
  void initStreak(double * prob);
  void initCouponCollector();
  MarkovEigen identity();
  MarkovEigen operator*(const MarkovEigen &b);
  MarkovEigen operator^(uint64_t n);
  //MarkovEigen operator^( float  n);
  /*
  friend ostream& operator<<(ostream& lhs, const MarkovEigen & rhs) {
	  return rhs.marMat.format(rhs.CleanFmt);
  };
   */
};



#endif /* MARKOVMX_H */

