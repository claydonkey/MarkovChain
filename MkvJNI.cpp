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
#include <string.h>
#include <jni.h>
#include "MarkovMx.h"
#include "MarkovEigen.h"
#define USEEIGEN

using namespace std;
using namespace Eigen;


/* This is a trivial JNI example where we use a native method
 * to return a new VM String. See the corresponding Java source
 * file located at:
 *
 *   apps/samples/hello-jni/project/src/com/example/hellojni/HelloJni.java
 */
#ifdef __cplusplus
extern "C" {
#endif
    int k1 = 21;
    int n = 1000000;
    double p = 0.5;

    jdoubleArray Java_com_claydonkey_algorithms_MainActivity_markovArrayResult
    (JNIEnv * env, jobject jobj, jdouble pin, jint nin, jint kin) {


	k1 = (kin + 1);
	p = pin;
	n = nin;

#if defined USEEIGEN
	MarkovEigen mkv2(k1);//, p);
	mkv2.initStreak(p);
	mkv2 = mkv2 ^ n;

	jdoubleArray arr = env->NewDoubleArray(k1 * k1);
	//double *resultC;
	//Eigen::Map<Eigen::MatrixXd> m(resultC, mkv2.marMat.rows(), mkv2.marMat.cols()) ;
	mkv2.marMat.transposeInPlace();
	env->SetDoubleArrayRegion(arr, 0, k1 * k1, reinterpret_cast<const jdouble *> (mkv2.marMat.data()));
#else
	double array [k1 * k1];
	//double Markov20[] = {0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5};


	MarkovMx<double>mkv(array, k1);
	//    m.initMarkov(Markov20);
	mkv.initMarkov(p);
	mkv = mkv ^ n;

	jdoubleArray arr = env->NewDoubleArray(k1 * k1);
	env->SetDoubleArrayRegion(arr, 0, k1 * k1, reinterpret_cast<const jdouble *> (mkv.a));
#endif
	return arr;

    }

    jstring Java_com_claydonkey_algorithms_MainActivity_stringFromJNI
    (JNIEnv * env, jobject jobj) {
	return env->NewStringUTF("Markov Test");
    }

    jint Java_com_claydonkey_algorithms_MainActivity_markovArrayDim
    (JNIEnv * env, jobject jobj) {
	return k1;
    }

#ifdef __cplusplus
}
#endif