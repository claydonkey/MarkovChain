#ifndef DEBUG_H
#define DEBUG_H

#include <iostream>
#include <fstream>
#include <ostream>
#include <complex>
#include  <Eigen/Core>

#define SAVEFILE
#define DEBUGTITLES 1

int debugTitles = DEBUGTITLES;
bool schur = false;
bool showCompute2x2 = false;
bool showHouseholder = false;
int dFlags2[] = {schur, true, true, showCompute2x2, true, false, showHouseholder, false};

int cnt = 1;

typedef enum {
    IMAG = 0,
    REAL,
    DEFAULT
} PRINTTYPE;

using namespace std;
using namespace Eigen;

PRINTTYPE pT = IMAG;

#ifdef SAVEFILE
ofstream datFile;
#if DEBUGTITLES == 0
Eigen::IOFormat HeavyFmt(7, Eigen::DontAlignCols, "  ", " ", "", "", "", "\n");
Eigen::IOFormat HeavyFmt(7, 0, " ", "\n", "[", "]", "", "\n");
#else
//Eigen::IOFormat HeavyFmt(7, Eigen::DontAlignCols, "  ", " ", "", "", "", "\n");
Eigen::IOFormat HeavyFmt(7, 0, " ", "\n", "[", "]", "", "\n");
#endif
#else
#define   datFile cout
Eigen::IOFormat HeavyFmt(7, 0, " ", "\n", "[", "]", "", "\n\n");

#endif

auto gettitle(const char * s) {
    std::stringstream fmt;

    fmt << "****************************************************** " << cnt++ << " *** " << s << " ******************************************************\n";
    return fmt.str();

}

template<typename Derived>
void debugPrint(const Eigen::DenseBase<Derived>& M, const char * s, int level) {
    const char * S;
    if (debugTitles == 1)
	S = s;
    else
	S = "";

    if (dFlags2[level]) {
	if (debugTitles == 1)
	    datFile << gettitle(s) << M.format(HeavyFmt);
	else
	    datFile << M.format(HeavyFmt);
    }

}

template<typename Derived>
void debugPrint(Eigen::PermutationBase<Derived>& M, const char * s, int level) {
    const char * S;
    if (debugTitles == 1)
	S = s;
    else
	S = "";

    if (dFlags2[level]) {
	if (debugTitles == 1)
	    datFile << gettitle(s) << M.toDenseMatrix().format(HeavyFmt);
	else
	    datFile << M.toDenseMatrix().format(HeavyFmt);
    }

}




template<typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
void debugPrint(T M, const char * s, int level) {
    const char * S;
    if (debugTitles == 1)
	S = s;
    else
	S = "";

    if (dFlags2[level]) {
	if (debugTitles == 1)
	    datFile << gettitle(s) << M << endl;
	else
	    datFile << M;
    }

}

void debugPrint(const char * M, const char * s, int level) {
    const char * S;
    if (debugTitles == 1)
	S = s;
    else
	S = "";
    if (dFlags2[level]) {
	if (debugTitles == 1)
	    datFile << gettitle(s) << M << endl;
	else
	    datFile << M;
    }

}

void debugPrint(complex<double> M, const char * s, int level) {
    const char * S;
    if (debugTitles == 1)
	S = s;
    else
	S = "";
    if (dFlags2[level]) {
	if (debugTitles == 1)
	    datFile << gettitle(s) << M << endl;
	else
	    datFile << M;
    }

}

#endif /* DEBUG_H */

