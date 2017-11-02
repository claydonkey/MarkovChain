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
 * File:   MarkovMx.h
 * Author: anthony
 *
 * Created on 28 April 2016, 09:32
 */

#ifndef MARKOVMX_H
  #define MARKOVMX_H


  #include <cstdlib>
  #include <vector>
  #include <cmath>
  #include <stdint.h>
  #include <complex>
  #include <iomanip>

using namespace std;

namespace Markov {

  template<class T >
  class MarkovMx {
  protected:


  public:
	const uint64_t kSize = 0;
	std::unique_ptr<T[] > markov_matrix_;
	explicit MarkovMx();

	template< size_t N = 0 >
	explicit MarkovMx(const T(&_a)[N]) : kSize(N), markov_matrix_(new T[kSize*kSize]) {
	}

	explicit MarkovMx(T *_a, const int N) : kSize(N), markov_matrix_(new T[kSize*kSize]) {
	  for (int r = 0; r < kSize; r++)
		for (int c = 0; c < kSize; c++)
		  markov_matrix_[r * kSize + c] = _a[r, c];
	}

	explicit MarkovMx(const int n) : kSize(n), markov_matrix_(new T[kSize*kSize]) {
	}

	MarkovMx(MarkovMx const &) = delete;

	MarkovMx & operator=(MarkovMx const &) = delete;

	MarkovMx<T> & operator=(MarkovMx &&rhs) {
	  if (this != &rhs)
		markov_matrix_ = std::move(rhs.markov_matrix_);
	  return *this;
	}

	MarkovMx(MarkovMx &&rhs) : kSize(rhs.kSize), markov_matrix_(std::move(rhs.markov_matrix_)) {
	}

	MarkovMx<T> identity() {
	  MarkovMx m(this->kSize);
	  for (int r = 0; r < this->kSize; r++)
		for (int c = 0; c < this->kSize; c++)
		  m.markov_matrix_[r * kSize + c] = (r == c ? 1 : 0);
	  return m;
	}

	MarkovMx<T> operator*(const MarkovMx &b) {
	  MarkovMx d(kSize);
	  for (int r = 0; r < kSize; r++)
		for (int c = 0; c < kSize; c++) {
		  d.markov_matrix_[r * kSize + c] = 0;
		  for (int k = 0; k < kSize; k++) {

			T row = markov_matrix_[r * b.kSize + k];
			T column = b.markov_matrix_[k * b.kSize + c];
			d.markov_matrix_[r * kSize + c] += row *column;
		  }
		}
	  return d;
	}

	MarkovMx<T> operator^(uint64_t n) {
	  if (n < 0)
		throw "Negative exponent not implemented";
	  MarkovMx<T> d = identity();
	  MarkovMx<T> &sq = *this;
	  for (sq; n > 0; sq = sq * sq, n /= 2)
		if (n % 2 != 0)
		  d = d * sq;
	  return d;
	}

	friend ostream& operator<<(ostream& lhs, const MarkovMx<T> & rhs) {
	  for (int i = 0; i < rhs.kSize; i++) {
		for (int j = 0; j < rhs.kSize; j++) {
		  if (j == 0)lhs << "[";
		  lhs << setiosflags(ios::fixed) << std::setprecision(4) << rhs.markov_matrix_[i * rhs.kSize + j] << ((j == (rhs.kSize - 1)) ? "]" : ", ");
		}
		lhs << endl;
	  }
	  return lhs;
	};
  };
}

#endif /* MARKOVMX_H */

