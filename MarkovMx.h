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
	  for (int r = 0; r < kSize; r++)
		for (int c = 0; c < kSize; c++)
		  markov_matrix_[r * kSize + c] = (r == c ? 1 : 0);
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

	void Identity() {
	  for (int r = 0; r < this->kSize; r++)
		for (int c = 0; c < this->kSize; c++)
		  this->markov_matrix_[r * kSize + c] = (r == c ? 1 : 0);
	}

	/* todo with side effects*/
	void Multi(const MarkovMx &b) {
	  for (int r = 0; r < kSize; r++)
		for (int c = 0; c < kSize; c++) {
		  this->markov_matrix_[r * kSize + c] = 0;
		  for (int k = 0; k < kSize; k++) {
			T row = markov_matrix_[r * b.kSize + k];
			T column = b.markov_matrix_[k * b.kSize + c];
			this->markov_matrix_[r * kSize + c] += row *column;
		  }
		}
	}

	static const MarkovMx<T> & toIdentity(const MarkovMx<T> &rhs) {
	  for (int r = 0; r < rhs.kSize; r++)
		for (int c = 0; c < rhs.kSize; c++)
		  rhs.markov_matrix_[r * rhs.kSize + c] = (r == c ? 1 : 0);
	  return rhs;
	}

	/* todo with side effects*/
	void Pow(uint64_t n) {
	  if (n < 0)
		throw "Negative exponent not implemented";
	  const MarkovMx<T> & i = MarkovMx<T>(this->kSize);
	  MarkovMx<T> &ref = *this;
	  bool first = true;
	  for (ref; n > 0; ref = ref * ref, n /= 2)
		if (first) {
		  Multi(i);
		  first = false;
		}
		else if (n % 2 != 0)
		  Multi(ref);
	}

	MarkovMx<T> identity() {
	  MarkovMx m(this->kSize);
	  for (int r = 0; r < this->kSize; r++)
		for (int c = 0; c < this->kSize; c++)
		  m.markov_matrix_[r * kSize + c] = (r == c ? 1 : 0);
	  return m;
	}

	inline MarkovMx<T> operator*(const MarkovMx &rhs) {
	  MarkovMx d(kSize);
	  for (int r = 0; r < kSize; r++)
		for (int c = 0; c < kSize; c++) {
		  d.markov_matrix_[r * kSize + c] = 0;
		  for (int k = 0; k < kSize; k++) {
			T row = markov_matrix_[r * rhs.kSize + k];
			T column = rhs.markov_matrix_[k * rhs.kSize + c];
			d.markov_matrix_[r * kSize + c] += row *column;
		  }
		}
	  return d;
	}

	MarkovMx<T> & operator^=(uint64_t n) {
	  if (n < 0)
		throw "Negative exponent not implemented";
	  const uint64_t c = n;
	  MarkovMx<T> i = this->identity();
	  MarkovMx<T> &lhs = *this;
	  for (lhs; n > 0; lhs = lhs * lhs, n /= 2)
		if (n % 2 != 0)
		  i = i * lhs;
	  this->markov_matrix_ = std::move(i.markov_matrix_);
	  return *this;
	}

	inline MarkovMx<T> operator^(uint64_t n) {
	  if (n < 0)
		throw "Negative exponent not implemented";
	  MarkovMx<T> i = this->identity();
	  MarkovMx<T> &lhs = *this;
	  for (lhs; n > 0; lhs = lhs * lhs, n /= 2)
		if (n % 2 != 0)
		  i = i * lhs;
	  return i;
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

