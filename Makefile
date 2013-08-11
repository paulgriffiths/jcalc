# JCalc
# =====
# Copyright 2013 Paul Griffiths
# Email: mail@paulgriffiths.net
#
# Distributed under the terms of the GNU General Public License.
# http://www.gnu.org/licenses/


# Variables section
# =================

# Executable names
OUT=jcalc
TESTOUT=unittests

# Compiler executable name
CXX=g++

# Compiler flags
CXXFLAGS=-std=c++11 -pedantic -Wall -Wextra -Weffc++
CXX_POSIX_FLAGS=-Wall -Wextra -Weffc++
CXX_DEBUG_FLAGS=-ggdb -DDEBUG -DDEBUG_ALL
CXX_RELEASE_FLAGS=-O3 -DNDEBUG

# Include flags
ICAIRO=-isystem/usr/lib/cairomm-1.0/include -isystem/usr/include/cairomm-1.0
ICAIRO+=-isystem/usr/include/sigc++-2.0
ICAIRO+=-isystem/usr/lib/x86_64-linux-gnu/sigc++-2.0/include
ICAIRO+=-isystem/usr/include/cairo -isystem/usr/include/freetype2

# Linker flags
LDFLAGS=-lcairo -lcairomm-1.0
LD_TEST_FLAGS=-lCppUTest -lCppUTestExt

# Object code files
MAINOBJ=main.o
TESTMAINOBJ=tests/unittests.o

OBJS=page.o drawing_context.o cairo_drawing_context.o colors.o
OBJS+=cairo_pdf_drawing_context.o cairo_svg_drawing_context.o
OBJS+=drawn_object.o drawn_circle_cross.o
OBJS+=segmented_bend.o point.o

TESTOBJS=

# Source and clean files and globs
SRCS=$(wildcard *.cpp *.h)
SRCS+=$(wildcard tests/*.cpp)

SRCGLOB=*.cpp *.h
SRCGLOB+=tests/*.cpp

CLNGLOB=jcalc unittests
CLNGLOB+=*~ *.o *.gcov *.out *.gcda *.gcno
CLNGLOB+=tests/*~ tests/*.o tests/*.gcov tests/*.out tests/*.gcda tests/*.gcno


# Build targets section
# =====================

default: debug

# debug - builds objects with debugging info
.PHONY: debug
debug: CXXFLAGS+=$(CXX_DEBUG_FLAGS)
debug: main

# release - builds with optimizations and without debugging info
.PHONY: release
release: CXXFLAGS+=$(CXX_RELEASE_FLAGS)
release: main

# tests - builds unit tests
.PHONY: tests
tests: CXXFLAGS+=$(CXX_DEBUG_FLAGS)
tests: LDFLAGS+=$(LD_TEST_FLAGS)
tests: testmain

# clean - removes ancilliary files from working directory
.PHONY: clean
clean:
	-@rm $(CLNGLOB) 2>/dev/null

# lint - runs cpplint with specified options
.PHONY: lint
lint:
	@cpplint --verbose=5 --filter=-runtime/references,-build/header_guard,\
-readability/streams,-build/include,-legal/copyright,\
-runtime/threadsafe_fn,-whitespace/blank_line,-runtime/int,\
-build/namespaces \
$(SRCGLOB)

# check - runs cppcheck with specified options
.PHONY: check
check:
	@cppcheck --enable=all $(SRCGLOB)


# Executable targets section
# ==========================

# Main executable
main: $(MAINOBJ) $(OBJS)
	$(CXX) -o $(OUT) $(MAINOBJ) $(OBJS) $(LDFLAGS) 

# Unit tests executable
testmain: $(TESTMAINOBJ) $(TESTOBJS) $(OBJS)
	$(CXX) -o $(TESTOUT) $(TESTMAINOBJ) $(TESTOBJS) $(OBJS) $(LDFLAGS) 


# Object files targets section
# ============================

# Main program

main.o: main.cpp jcalc.h page.h
	$(CXX) $(CXXFLAGS) $(ICAIRO) -c -o $@ $<

page.o: page.cpp page.h drawing_context.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<

point.o: point.cpp point.h drawing_context.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<

colors.o: colors.cpp colors.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<

drawing_context.o: drawing_context.cpp drawing_context.h
	$(CXX) $(CXXFLAGS) $(ICAIRO) -c -o $@ $<

drawn_object.o: drawn_object.cpp drawn_object.h
	$(CXX) $(CXXFLAGS) $(ICAIRO) -c -o $@ $<

drawn_circle_cross.o: drawn_circle_cross.cpp drawn_circle_cross.h
	$(CXX) $(CXXFLAGS) $(ICAIRO) -c -o $@ $<

segmented_bend.o: segmented_bend.cpp segmented_bend.h
	$(CXX) $(CXXFLAGS) $(ICAIRO) -c -o $@ $<

cairo_drawing_context.o: cairo_drawing_context.cpp \
	cairo_drawing_context.h drawing_context.h
	$(CXX) $(CXXFLAGS) $(ICAIRO) -c -o $@ $<

cairo_pdf_drawing_context.o: cairo_pdf_drawing_context.cpp \
	cairo_pdf_drawing_context.h drawing_context.h
	$(CXX) $(CXXFLAGS) $(ICAIRO) -c -o $@ $<

cairo_svg_drawing_context.o: cairo_svg_drawing_context.cpp \
	cairo_svg_drawing_context.h drawing_context.h
	$(CXX) $(CXXFLAGS) $(ICAIRO) -c -o $@ $<


# Unit tests

tests/unittests.o: tests/testmain.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

