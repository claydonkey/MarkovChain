#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=x86_64-w64-mingw32-gcc
CCC=x86_64-w64-mingw32-g++
CXX=x86_64-w64-mingw32-g++
FC=x86_64-w64-mingw32-gfortran
AS=nasm

# Macros
CND_PLATFORM=x86_64-w64-mingw32-Windows
CND_DLIB_EXT=dll
CND_CONF=x86_64-w64-mingw32
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/MarkovStats.o \
	${OBJECTDIR}/markovEigen.o \
	${OBJECTDIR}/markovMx.o

# Test Directory
TESTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}/tests

# Test Files
TESTFILES= \
	${TESTDIR}/TestFiles/f1 \
	${TESTDIR}/TestFiles/f2

# Test Object Files
TESTOBJECTFILES= \
	${TESTDIR}/MarkovTestSuite/MarkovTestRunner.o \
	${TESTDIR}/MarkovTestSuite/MarkovTestSuite.o \
	${TESTDIR}/tests/main.o

# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libmarkovchain.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libmarkovchain.a: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libmarkovchain.a
	${AR} -rv ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libmarkovchain.a ${OBJECTFILES} 
	$(RANLIB) ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libmarkovchain.a

${OBJECTDIR}/MarkovStats.o: MarkovStats.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/mingw64/include -I/mingw64/include/Eigen -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/MarkovStats.o MarkovStats.cpp

${OBJECTDIR}/markovEigen.o: markovEigen.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/mingw64/include -I/mingw64/include/Eigen -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/markovEigen.o markovEigen.cpp

${OBJECTDIR}/markovMx.o: markovMx.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/mingw64/include -I/mingw64/include/Eigen -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/markovMx.o markovMx.cpp

# Subprojects
.build-subprojects:

# Build Test Targets
.build-tests-conf: .build-tests-subprojects .build-conf ${TESTFILES}
.build-tests-subprojects:

${TESTDIR}/TestFiles/f1: ${TESTDIR}/tests/main.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc} -o ${TESTDIR}/TestFiles/f1 $^ ${LDLIBSOPTIONS}   

${TESTDIR}/TestFiles/f2: ${TESTDIR}/MarkovTestSuite/MarkovTestRunner.o ${TESTDIR}/MarkovTestSuite/MarkovTestSuite.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc} -o ${TESTDIR}/TestFiles/f2 $^ ${LDLIBSOPTIONS}   `cppunit-config --libs`   


${TESTDIR}/tests/main.o: tests/main.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/mingw64/include -I/mingw64/include/Eigen -I. -std=c++14 -MMD -MP -MF "$@.d" -o ${TESTDIR}/tests/main.o tests/main.cpp


${TESTDIR}/MarkovTestSuite/MarkovTestRunner.o: MarkovTestSuite/MarkovTestRunner.cpp 
	${MKDIR} -p ${TESTDIR}/MarkovTestSuite
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/mingw64/include -I/mingw64/include/Eigen -std=c++14 `cppunit-config --cflags` -MMD -MP -MF "$@.d" -o ${TESTDIR}/MarkovTestSuite/MarkovTestRunner.o MarkovTestSuite/MarkovTestRunner.cpp


${TESTDIR}/MarkovTestSuite/MarkovTestSuite.o: MarkovTestSuite/MarkovTestSuite.cpp 
	${MKDIR} -p ${TESTDIR}/MarkovTestSuite
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/mingw64/include -I/mingw64/include/Eigen -std=c++14 `cppunit-config --cflags` -MMD -MP -MF "$@.d" -o ${TESTDIR}/MarkovTestSuite/MarkovTestSuite.o MarkovTestSuite/MarkovTestSuite.cpp


${OBJECTDIR}/MarkovStats_nomain.o: ${OBJECTDIR}/MarkovStats.o MarkovStats.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/MarkovStats.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -I/mingw64/include -I/mingw64/include/Eigen -std=c++14 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/MarkovStats_nomain.o MarkovStats.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/MarkovStats.o ${OBJECTDIR}/MarkovStats_nomain.o;\
	fi

${OBJECTDIR}/markovEigen_nomain.o: ${OBJECTDIR}/markovEigen.o markovEigen.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/markovEigen.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -I/mingw64/include -I/mingw64/include/Eigen -std=c++14 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/markovEigen_nomain.o markovEigen.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/markovEigen.o ${OBJECTDIR}/markovEigen_nomain.o;\
	fi

${OBJECTDIR}/markovMx_nomain.o: ${OBJECTDIR}/markovMx.o markovMx.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/markovMx.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -I/mingw64/include -I/mingw64/include/Eigen -std=c++14 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/markovMx_nomain.o markovMx.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/markovMx.o ${OBJECTDIR}/markovMx_nomain.o;\
	fi

# Run Test Targets
.test-conf:
	@if [ "${TEST}" = "" ]; \
	then  \
	    ${TESTDIR}/TestFiles/f1 || true; \
	    ${TESTDIR}/TestFiles/f2 || true; \
	else  \
	    ./${TEST} || true; \
	fi

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
