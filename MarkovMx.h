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


#include<cstdlib>
#include <vector>
#include <cmath>
#include <stdint.h>
#include <complex>
#include <iomanip>

using namespace std;

template<class T >
class MarkovMx {
private:
    MarkovMx();
protected:
    MarkovMx(const MarkovMx & a);

public:
    T *a;
    int N = 0;
    MarkovMx(T *_a, const int size);
    MarkovMx(const int size);
    ~MarkovMx();
    void initMarkov(T prob);
    void initMarkov(T * prob);
    MarkovMx identity();
    MarkovMx operator*(const MarkovMx &b);
    MarkovMx operator^(unsigned long long int n);

    friend ostream& operator<<(ostream& lhs, const MarkovMx<T> & rhs) {
	for (int i = 0; i < rhs.N; i++) {
	    for (int j = 0; j < rhs.N; j++)
		lhs << setiosflags(ios::fixed)  << std::setprecision(4) << rhs.a[(i * rhs.N) + j ] << ",";
	    lhs << endl;
	}
	return lhs;
    };

};



#endif /* MARKOVMX_H */

