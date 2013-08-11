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

OBJS=page.o

OBJS+=common/colors.o common/point.o

OBJS+=drawns/drawn_object.o
OBJS+=drawns/segmented_bend.o
OBJS+=drawns/pipe_bend.o

OBJS+=contexts/drawing_context.o
OBJS+=contexts/cairo_drawing_context.o
OBJS+=contexts/cairo_pdf_drawing_context.o
OBJS+=contexts/cairo_svg_drawing_context.o

TESTOBJS=

# Source and clean files and globs
SRCS=$(wildcard *.cpp *.h)
SRCS+=$(wildcard common/*.cpp common/*.h)
SRCS+=$(wildcard drawns/*.cpp drawns/*.h)
SRCS+=$(wildcard drawns/*.cpp drawns/*.h)
#SRCS+=$(wildcard tests/*.cpp)

SRCGLOB=*.cpp *.h
SRCGLOB+=common/*.cpp common/*.h
SRCGLOB+=drawns/*.cpp drawns/*.h
SRCGLOB+=contexts/*.cpp contexts/*.h
#SRCGLOB+=tests/*.cpp *.h

CLNGLOB=jcalc unittests outfile*
CLNGLOB+=*~ *.o *.gcov *.out *.gcda *.gcno
CLNGLOB+=common/*~ common/*.o common/*.gcov common/*.out
CLNGLOB+=common/*.gcda common/*.gcno
CLNGLOB+=drawns/*~ drawns/*.o drawns/*.gcov drawns/*.out
CLNGLOB+=drawns/*.gcda drawns/*.gcno
CLNGLOB+=contexts/*~ contexts/*.o contexts/*.gcov contexts/*.out
CLNGLOB+=contexts/*.gcda contexts/*.gcno
#CLNGLOB+=tests/*~ tests/*.o tests/*.gcov tests/*.out tests/*.gcda tests/*.gcno


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
	@echo "Linking $(OUT)..."
	@$(CXX) -o $(OUT) $(MAINOBJ) $(OBJS) $(LDFLAGS) 
	@echo "Done."

# Unit tests executable
testmain: $(TESTMAINOBJ) $(TESTOBJS) $(OBJS)
	$(CXX) -o $(TESTOUT) $(TESTMAINOBJ) $(TESTOBJS) $(OBJS) $(LDFLAGS) 


# Object files targets section
# ============================

# Main program

main.o: main.cpp jcalc.h context.h page.h contexts/drawing_context.h \
	common/jcalc_exceptions.h
	@echo "Compiling $<..."
	@$(CXX) $(CXXFLAGS) -c -o $@ $<

page.o: page.cpp page.h context.h contexts/drawing_context.h \
	drawns/pipe_bend.h drawns/drawn_object.h
	@echo "Compiling $<..."
	@$(CXX) $(CXXFLAGS) -c -o $@ $<

common/point.o: common/point.cpp common/point.h
	@echo "Compiling $<..."
	@$(CXX) $(CXXFLAGS) -c -o $@ $<

common/colors.o: common/colors.cpp common/colors.h
	@echo "Compiling $<..."
	@$(CXX) $(CXXFLAGS) -c -o $@ $<

drawns/drawn_object.o: drawns/drawn_object.cpp drawns/drawn_object.h \
	common/colors.h common/point.h common/jcalc_exceptions.h \
	common/math_helper.h
	@echo "Compiling $<..."
	@$(CXX) $(CXXFLAGS) -c -o $@ $<

drawns/segmented_bend.o: drawns/segmented_bend.cpp drawns/segmented_bend.h \
	drawns/drawn_object.h \
	common/colors.h common/point.h common/jcalc_exceptions.h \
	common/math_helper.h
	@echo "Compiling $<..."
	@$(CXX) $(CXXFLAGS) -c -o $@ $<

drawns/pipe_bend.o: drawns/pipe_bend.cpp drawns/pipe_bend.h \
	drawns/segmented_bend.h drawns/drawn_object.h \
	common/colors.h common/point.h common/jcalc_exceptions.h \
	common/math_helper.h
	@echo "Compiling $<..."
	@$(CXX) $(CXXFLAGS) -c -o $@ $<

contexts/drawing_context.o: contexts/drawing_context.cpp \
	contexts/drawing_context.h contexts/null_drawing_context.h \
	contexts/cairo_pdf_drawing_context.h \
	contexts/cairo_svg_drawing_context.h \
	common/colors.h common/point.h common/jcalc_exceptions.h \
	common/math_helper.h
	@echo "Compiling $<..."
	@$(CXX) $(CXXFLAGS) $(ICAIRO) -c -o $@ $<

contexts/null_drawing_context.o: contexts/null_drawing_context.cpp \
	contexts/null_drawing_context.h contexts/drawing_context.h \
	common/colors.h common/point.h common/jcalc_exceptions.h \
	common/math_helper.h
	@echo "Compiling $<..."
	@$(CXX) $(CXXFLAGS) -c -o $@ $<

contexts/cairo_drawing_context.o: contexts/cairo_drawing_context.cpp \
	contexts/cairo_drawing_context.h contexts/drawing_context.h \
	common/colors.h common/point.h common/jcalc_exceptions.h \
	common/math_helper.h
	@echo "Compiling $<..."
	@$(CXX) $(CXXFLAGS) $(ICAIRO) -c -o $@ $<

contexts/cairo_pdf_drawing_context.o: contexts/cairo_pdf_drawing_context.cpp \
	contexts/cairo_pdf_drawing_context.h contexts/cairo_drawing_context.h \
	contexts/drawing_context.h \
	common/colors.h common/point.h common/jcalc_exceptions.h \
	common/math_helper.h
	@echo "Compiling $<..."
	@$(CXX) $(CXXFLAGS) $(ICAIRO) -c -o $@ $<

contexts/cairo_svg_drawing_context.o: contexts/cairo_svg_drawing_context.cpp \
	contexts/cairo_svg_drawing_context.h contexts/cairo_drawing_context.h \
	contexts/drawing_context.h \
	common/colors.h common/point.h common/jcalc_exceptions.h \
	common/math_helper.h
	@echo "Compiling $<..."
	@$(CXX) $(CXXFLAGS) $(ICAIRO) -c -o $@ $<


# Unit tests

tests/unittests.o: tests/testmain.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<
