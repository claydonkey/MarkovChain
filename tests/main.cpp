/*
 * The MIT License
 *
 * Copyright 2016 anthony.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

/*
 * File:   main.cpp
 * Author: anthony
 *
 * Created on 27 April 2016, 13:29
 */

#include<iostream>
#include<cstdlib>
#include <vector>
#include <cmath>
#include <stdint.h>
#include <complex>
#include "MarkovMx.h"
#include "MarkovEigen.h"
#include <limits>
#include <chrono>
#include <functional>
#include "assert.h"
#include <Eigen/Dense>
//#include <unsupported/Eigen/MatrixFunctions>

#define TEST_ITERATIONS 1000
#define USEEIGEN2
#define STREAKSq

using namespace std;
using namespace Eigen;

chrono::microseconds::rep execution(std::function<void() > func) {
  auto start = chrono::system_clock::now();
  for (int times = 0; times < TEST_ITERATIONS; times++) {
	func();
  }


  chrono::microseconds duration = chrono::duration_cast<chrono::microseconds>(std::chrono::system_clock::now() - start);
  return duration.count();
}

int main(int argc, char** argv) {
  std::cin.sync_with_stdio(false);
  int k;
  unsigned long long int n;
  double s;
  int puz;

  Affine3f transform(Translation3f(0.0f, -0.75f, 0.0f));
  cout << transform.matrix() << std::endl;


  cout << "Enter Problem to Solve:\n 1. Coupon Collector\n 2. Streaks\n";
  cin >> puz;


  cout << "Max Power: " << numeric_limits<unsigned long long int>::max() << endl;
  cout << "Enter the number of trials:\n";
  cin >> n;


  int k1;
  switch (puz) {
	case 2:
	  cout << "Enter the length of streak desired:\n";
	  k1 = [](int t) {
		return cin >> t, std::move(t + 1);
	  }({});
	  cout << "Enter the probability of single success:\n";
	  cin >> s;
	  break;
	case 1:
	  cout << "Enter the number of Different Coupons to Collect:\n";

	  k1 = [](int t) {
		return cin >> t, std::move(t);
	  }({});
	  break;
  }

#if defined USEEIGEN
  Eigen::MatrixXd marMat(k1, k1);
  Eigen::IOFormat CleanFmt(4, 0, ", ", "\n", "[", "]");

  for (int i = 0; i < k1; i++)
	for (int j = 0; j < k1; j++) {
	  marMat(i, j) = ((i == j + 1) ? s : 0.0);
	  if (i == 0)
		marMat(0, j) = 1.0 - s;
	}
  marMat(k1 - 1, k1 - 1) = 1.0;
  marMat(0, k1 - 1) = 0.0;
  //   cout << marMat.format(CleanFmt);
  //       cout << execution([&]() {
  marMat = marMat.pow(n);
  //    }) << std::endl;
  //  cout << marMat.format(CleanFmt);
  printf("\nprobability (Eigen) %lf: \n", marMat(k1 - 1, 0));

#elif defined USEEIGEN2
  MarkovEigen mkv2(k1);

  switch (puz) {
	case 1:
	  mkv2.initCouponCollector();
	  cout << mkv2.marMat.format(mkv2.CleanFmt) << endl;
	  mkv2 = mkv2 ^ (n - 1);
	  break;
	case 2:
	  mkv2.initStreak(s);
	  cout << mkv2.marMat.format(mkv2.CleanFmt) << endl;
	  mkv2 = mkv2 ^ n;
	  break;

  }


  cout << mkv2.marMat.format(mkv2.CleanFmt) << endl;

  printf("\nprobability (Eigen2) %lf: \n", mkv2.marMat(k1 - 1, 0));
  fflush(stdout);


  //  mkv2.marMat.transposeInPlace();
  //     MarkovMx<double>mkv( mkv2.marMat.data(), k1);
  //      cout << mkv << endl;
#else

  double array [k1 * k1];
  // double Markov20[] = {0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5};
  MarkovMx<double>mkv(array, k1);
  mkv.initStreak(s);
  // cout << execution([&]() {
  cout << mkv << endl;
  mkv = mkv ^ n;
  cout << mkv << endl;
  //}) << endl;

  printf("probability %lf: \n", mkv.a[(k1 * (k1 - 1))]);
#endif
  // cin >> n;
  return 0;
}

