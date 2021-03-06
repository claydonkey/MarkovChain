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
 * File:   MarkovTestRunner.cpp
 * Author: Anthony Campbell
 *
 * Created on 03-Nov-2017, 10:16:50
 */

// CppUnit site http://sourceforge.net/projects/cppunit/files

#include <gtest/gtest.h>
#ifndef NOBENCHMARK
#include <benchmark/benchmark.h>
#endif
#include <stdlib.h>
#include <iostream>
#include "MarkovTestSuite.h"


using namespace std;

int main(int argc, const char** argv) {
#ifndef NOBENCHMARK
  ::benchmark::Initialize(&argc, (char**) argv);
  if (::benchmark::ReportUnrecognizedArguments(argc, (char**) argv)) return 1;

#endif
  testing::InitGoogleTest(&argc, (char**) argv);
#ifndef NOBENCHMARK
  setup();
  ::benchmark::RunSpecifiedBenchmarks();
#endif
  return RUN_ALL_TESTS();
}

