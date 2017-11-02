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
#include "MarkovEigen.h"
#include <Eigen/Dense>
#include <Eigen/unsupported/Eigen/MatrixFunctions>

using namespace std;
using namespace Eigen;

MarkovEigen::MarkovEigen(const int size) : N(size), marMat(size, size), CleanFmt(4, 0, ", ", "\n", "[", "]") { // constructor with pre-defined array
    //  a = marMat.data();
    //    Map<MatrixXd>(a, size, size) = marMat;
}

MarkovEigen::MarkovEigen(const int size, Eigen::MatrixXd mat) : N(size), marMat(mat), CleanFmt(4, 0, ", ", "\n", "[", "]") { // constructor with pre-defined array
    //   a = marMat.data();
    //  Map<MatrixXd>(a, mat.rows(), mat.cols()) = marMat;
}

void MarkovEigen::initCouponCollector() {
    for (double i = 0.0; i < N; i++)
	for (double j = 0.0; j < N; j++)
	    marMat(i, j) = (i == j ? (j + 1.0) / N : (i == (j + 1.0) ? (N - (j + 1.0)) / N : 0.0));

    marMat(N - 1, N - 1) = 1.0;
    marMat(0, N - 1) = 0.0;
}

void MarkovEigen::initStreak(double T) {  //1  /(15^16) *(sum ((-1)^i) *C(15, i)(15-i)^16 , i=0 to 16) in Alpha for Sterling Number of Second Kind
    for (int i = 0; i < N; i++)
	for (int j = 0; j < N; j++)
	    marMat(i, j) = (i == 0 ? 1.0 - T : (i == j + 1 ? T : 0.0));

    marMat(N - 1, N - 1) = 1.0;
    marMat(0, N - 1) = 0.0;

}

void MarkovEigen::initStreak(double * T) {

    for (int i = 0; i < N; i++)
	for (int j = 0; j < N; j++)
	    marMat(i, j) = (i == 0 ? 1 - T[j] : (i == j + 1 ? T[i - 1] : 0.0));

    marMat(N - 1, N - 1) = 1.0;
    marMat(0, N - 1) = 0.0;

}

MarkovEigen MarkovEigen::operator^(unsigned long long int n) {

    return MarkovEigen(n, marMat.pow(n));
}

//MarkovEigen MarkovEigen::operator^( float  n) {

   // return MarkovEigen(n, marMat.pow(n));
//}


MarkovEigen::~MarkovEigen() {

    //delete[] a;
}