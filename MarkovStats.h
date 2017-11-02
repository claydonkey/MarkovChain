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
 * File:   MarkovStats.h
 * Author: Anthony Campbell
 *
 * Created on 02 November 2017, 17:36
 */

#ifndef MARKOVSTATS_H
  #define MARKOVSTATS_H

  #include "MarkovMx.h"
namespace Markov {

  template<class T >
  class Coupon : public MarkovMx<T> {
  public:
	using MarkovMx<double>::MarkovMx;
	using MarkovMx<double>::operator=;

	explicit Coupon(const int size) : MarkovMx<T>(size) {
	  for (T i = 0.0; i < this->kSize; i++)
		for (T j = 0.0; j < this->kSize; j++)
		  this->markov_matrix_[i * this->kSize + j] = (i == j ? (j + 1.0) / this->kSize : (i == (j + 1.0) ? (this->kSize - (j + 1.0)) / this->kSize : 0.0));
	  this->markov_matrix_[this->kSize * (this->kSize - 1) + this->kSize - 1] = 1.0;
	  this->markov_matrix_[this->kSize - 1] = 0.0;
	}
  };

  template<class T >
  class Streak : public MarkovMx<double> {
  public:
	using MarkovMx<double>::MarkovMx;
	using MarkovMx<double>::operator=;

	explicit Streak(const int size, double prob) : MarkovMx<T>(size) {
	  for (int i = 0; i < kSize; i++)
		for (int j = 0; j < kSize; j++)
		  markov_matrix_[i * kSize + j] = (i == 0 ? 1.0 - prob : (i == j + 1 ? prob : 0.0));
	  markov_matrix_[kSize * (kSize - 1) + kSize - 1] = 1.0;
	  markov_matrix_[kSize - 1] = 0.0;
	}
  };
}
#endif /* MARKOVSTATS_H */

