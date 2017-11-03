/*
 * The MIT License
 *
 * Copyright 2017 Anthony Campbell.
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
/**
 * @author Anthony Campbell anthony@claydonkey.com
 */

/*
 * File:   MarkovTestClass.cpp
 * Author: Anthony Campbell
 *
 * Created on 03-Nov-2017, 10:16:50
 */

#include "MarkovTestSuite.h"
#include "../MarkovStats.h"
#include "../MarkovMx.h"
#include "../MarkovEigen.h"
uint32_t k1;
uint64_t n;

void setup() {
  k1 = 170;
  n = 2000;
}

void BM_markov_std_naive_coupon_dbl(benchmark::State& state) {
  while (state.KeepRunning()) {
	Markov::Coupon<double>mkv(k1);
	mkv = mkv ^ (n - 1);
  }
}

void BM_markov_eigen_postfix_coupon_dbl(benchmark::State& state) {
  while (state.KeepRunning()) {
	Markov::Coupon<double>mkv(k1);
	mkv ^= (n - 1);
  }
}

//void BM_markov_Pow_coupon_dbl(benchmark::State& state) {
//  while (state.KeepRunning()) {
//	Markov::Coupon<double>mkv(k1);
//	mkv.Pow(n - 1);
//  }
//}

void BM_markov_eigen_naive_coupon_dbl(benchmark::State& state) {
  while (state.KeepRunning()) {
	MarkovEigen mkv(k1);
	mkv.initCouponCollector();
	mkv = mkv ^ (n - 1);
  }
}


#ifndef NOASSMBLR
BENCHMARK(BM_markov_std_naive_coupon_dbl);
BENCHMARK(BM_markov_eigen_postfix_coupon_dbl);
//BENCHMARK(BM_markov_Pow_coupon_dbl);
BENCHMARK(BM_markov_eigen_naive_coupon_dbl);
#endif

TEST_F(TestSuite, testmarkovcoupon1) {

  MarkovEigen mkv1(k1);
  mkv1.initCouponCollector();
  mkv1 = mkv1 ^ (n - 1);

  Markov::Coupon<double>c(k1);
  c = c^(n - 1);

  double resc = c.markov_matrix_.get()[c.kSize * (k1 - 1)];
  double res1 = mkv1.marMat(k1 - 1, 0);
  printf("\n[PRBABILITY] ");
  printf("(std) :  %lf\n", resc);
  printf("[PRBABILITY] ");
  printf("(eign) : %lf\n\n", res1);

  EXPECT_EQ(ceilf(resc * 10000) / 10000, ceilf(res1 * 10000) / 10000);

}

TEST_F(TestSuite, testmarkovcoupon2) {

  MarkovEigen mkv1(k1);
  mkv1.initCouponCollector();
  mkv1 = mkv1 ^ (n - 1);

  Markov::Coupon<double>c(k1);
  c ^= (n - 1);

  double resc = c.markov_matrix_.get()[c.kSize * (k1 - 1)];
  double res1 = mkv1.marMat(k1 - 1, 0);
  printf("\n[PRBABILITY] ");
  printf("(std) :  %lf\n", resc);
  printf("[PRBABILITY] ");
  printf("(eign) : %lf\n\n", res1);

  EXPECT_EQ(ceilf(resc * 10000) / 10000, ceilf(res1 * 10000) / 10000);
  SUCCEED();
}

//TEST_F(TestSuite, testmarkovcoupon3) {
//
//  MarkovEigen mkv1(k1);
//  mkv1.initCouponCollector();
//  mkv1 = mkv1 ^ (n - 1);
//
//  Markov::Coupon<double>c2(k1);
//  c2.Pow(n - 1);
//
//  auto resc2 = c2.markov_matrix_.get()[c2.kSize * (k1 - 1)];
//  auto res1 = mkv1.marMat(k1 - 1, 0);
//  printf("\n[PRBABILITY] ");
//  printf("(std) :  %lf\n", resc2);
//  printf("[PRBABILITY] ");
//  printf("(eign) : %lf\n\n", res1);
//
//  EXPECT_EQ(resc2, res1);
//
//}
