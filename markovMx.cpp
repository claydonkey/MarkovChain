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
 * File:   markovMx.cpp
 * Author: anthony
 *
 * Created on 28 April 2016, 09:30
 */

#include <cstdlib>
#include "MarkovMx.h"

using namespace std;

template<class T >
MarkovMx<T>::MarkovMx(const MarkovMx & a) {
    /*...*/
}

template<class T >
MarkovMx<T>::MarkovMx(T *_a, const int size) : N(size), a(new T[size*size]) { // constructor with pre-defined array
    for (int r = 0; r < size; r++)
	for (int c = 0; c < size; c++)
	    a[(r * size) + c] = _a[(r * size) + c];
}

template<class T >
MarkovMx<T>::MarkovMx(const int size) : N(size), a(new T[size*size]) { // constructor with pre-defined array

}

template<class T >
void MarkovMx<T>::initMarkov(T prob) {

    for (int i = 0; i < N; i++)
	for (int j = 0; j < N; j++)
	    a[(i * N) + j ] = (i == 0 ? 1.0 - prob : ((i == j + 1) ? prob : 0.0));


    a[(N * N) - 1 ] = 1.0;
    a[N - 1 ] = 0.0;

}

template<class T >
void MarkovMx<T>::initMarkov(T * prob) {

    for (int i = 0; i < N; i++)
	for (int j = 0; j < N; j++)
	    a[(i * N) + j ] = (i == 0 ? 1 - prob[j] : ((i == j + 1) ? prob[i - 1] : 0.0));

    a[(N * N) - 1 ] = 1.0;
    a[N - 1 ] = 0.0;

}

template<class T >
MarkovMx<T> MarkovMx<T>::identity() {
    MarkovMx m(this->N);
    for (int r = 0; r < this->N; r++)
	for (int c = 0; c < this->N; c++)
	    m.a[(r * this->N) + c] = (r == c ? 1 : 0);
    return m;
}

template<class T >
MarkovMx<T> MarkovMx<T>::operator*(const MarkovMx &b) {
    MarkovMx d(N);
    for (int r = 0; r < N; r++)
	for (int c = 0; c < N; c++) {
	    d.a[(r * N) + c] = 0;
	    for (int k = 0; k < N; k++) {
		T row = a[(r * N) + k];
		T column = b.a[(k * N) + c];
		d.a[(r * N) + c] += row *column;
	    }
	}
    return d;
}

template<class T >
MarkovMx<T> MarkovMx<T>::operator^(unsigned long long int n) {
    if (n < 0)
	throw "Negative exponent not implemented";

    MarkovMx d = identity();
    MarkovMx &sq = *this;
    for (sq; n > 0; sq = sq * sq, n /= 2)
	if (n % 2 != 0)
	    d = d * sq;
    return d;
}

template<class T >
MarkovMx<T>::~MarkovMx() {

    //delete[] a;
}
// No need to call this TemporaryFunction() function,
// it's just to avoid link error.
template class MarkovMx<double>;



