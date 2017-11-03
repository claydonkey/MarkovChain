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
#include <stdint.h>

#include <assert.h>
#include <iostream>
#include <cstdlib>
#include <vector>
#include <cmath>
#include <complex>
#include <limits>
#include <chrono>
#include <functional>

#include <Eigen/Dense>
#include "MarkovMx.h"
#include "MarkovEigen.h"
#include "MarkovStats.h"

#define TEST_ITERATIONS 10000
#define USE_TIMERNOT

using namespace std;
using namespace Eigen;

chrono::microseconds::rep Timer(std::function<void() > func) {
#ifdef USE_TIMER
  auto start = chrono::system_clock::now();
  for (int times = 0; times < TEST_ITERATIONS; times++) {
	func();
  }
  chrono::microseconds duration = chrono::duration_cast<chrono::microseconds>(std::chrono::system_clock::now() - start);
  return duration.count();
#endif
}

int main(int argc, char** argv) {
  std::cin.sync_with_stdio(false);
  int k;
  uint64_t n;
  double s;
  int puz;
  int k1;

  cout <<
		  "Enter Problem to Solve:\n 1. Coupon Collector\n 2. Streaks\n";
  cin >> puz;

  switch (puz) {
	case 2:
	  cout <<
			  "Enter the length of streak desired: ";
	  k1 = [](int t) {
		return cin >> t, std::move(t + 1);
	  }({});
	  cout <<
			  "Enter the probability of a single success: ";
	  cin >> s;
	  break;
	case 1:
	  cout <<
			  "Enter the number of different coupons in full set: ";
	  k1 = [](int t) {
		return cin >> t, std::move(t);
	  }({});
	  break;
  }

  cout <<
		  "Enter the number of trials: ";
  cin >> n;

  cout << endl << endl;

  Markov::MarkovMx <double> *mkv;

  switch (puz) {
	case 1:
	  mkv = new Markov::Coupon<double> (k1);
	  cout << *mkv << endl;
	  // cout << Timer([&]() {
	  *mkv ^= (n - 1);
	  // }) << std::endl;
	  break;
	case 2:
	  mkv = new Markov::Streak<double> (k1, s);
	  // cout << Timer([&]() {
	  *mkv ^= n;
	  //  }) << std::endl;
	  break;
  }
  cout << *mkv << endl;

  printf("\nprobability (std) %lf: \n\n",
		  mkv->markov_matrix_.get()[mkv->kSize * (k1 - 1)]);

  fflush(stdout);
  free(mkv);

  MarkovEigen mkv2(k1);

  switch (puz) {
	case 1:
	  mkv2.initCouponCollector();
	  cout << mkv2.marMat.format(mkv2.CleanFmt) << endl << endl;
	  //  cout << Timer([&]() {
	  mkv2 = mkv2 ^ (n - 1);
	  //  }) << std::endl;
	  break;
	case 2:
	  mkv2.initStreak(s);
	  cout << mkv2.marMat.format(mkv2.CleanFmt) << endl;
	  //  cout << Timer([&]() {
	  mkv2 = mkv2 ^ n;
	  //  }) << std::endl;
	  break;
  }

  cout << mkv2.marMat.format(mkv2.CleanFmt) << endl;

  printf("\nprobability (Eigen2) %lf: \n", mkv2.marMat(k1 - 1, 0));
  fflush(stdout);

  return 0;
}

