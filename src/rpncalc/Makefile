#
# Makefile - Copyright (c) 2023 - Olivier Poncet
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 2 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.
#

# ----------------------------------------------------------------------------
# global environment
# ----------------------------------------------------------------------------

FLAGS    = -g -Og -Wall
CC       = gcc
CFLAGS   = -std=c99 $(FLAGS)
CXX      = g++
CXXFLAGS = -std=c++14 $(FLAGS)
CPPFLAGS = -I.
LD       = g++
LDFLAGS  = -L.
CP       = cp
CPFLAGS  = -f
RM       = rm
RMFLAGS  = -f

# ----------------------------------------------------------------------------
# default rules
# ----------------------------------------------------------------------------

.c.o :
	$(CC) -c $(CFLAGS) $(CPPFLAGS) $<

.cc.o :
	$(CXX) -c $(CXXFLAGS) $(CPPFLAGS) $<

# ----------------------------------------------------------------------------
# global targets
# ----------------------------------------------------------------------------

all : build

build : build_rpncalc
	@echo "=== $@ ok ==="

clean : clean_rpncalc
	@echo "=== $@ ok ==="

check : check_rpncalc
	@echo "=== $@ ok ==="

# ----------------------------------------------------------------------------
# rpncalc files
# ----------------------------------------------------------------------------

RPNCALC_BIN = rpncalc.bin

RPNCALC_OPTS = --verbose

RPNCALC_SRCS = \
	State.cc \
	Logger.cc \
	Console.cc \
	Runnable.cc \
	Listener.cc \
	Parser.cc \
	Buffer.cc \
	ByteCode.cc \
	HostCode.cc \
	Compiler.cc \
	BasicBlock.cc \
	Calculator.cc \
	Program.cc \
	main.cc \
	$(NULL)

RPNCALC_HDRS = \
	State.h \
	Logger.h \
	Console.h \
	Runnable.h \
	Listener.h \
	Parser.h \
	Buffer.h \
	ByteCode.h \
	HostCode.h \
	Compiler.h \
	BasicBlock.h \
	Calculator.h \
	Program.h \
	main.h \
	$(NULL)

RPNCALC_OBJS = \
	State.o \
	Logger.o \
	Console.o \
	Runnable.o \
	Listener.o \
	Parser.o \
	Buffer.o \
	ByteCode.o \
	HostCode.o \
	Compiler.o \
	BasicBlock.o \
	Calculator.o \
	Program.o \
	main.o \
	$(NULL)

RPNCALC_LIBS = \
	-lpthread -lm \
	$(NULL)

# ----------------------------------------------------------------------------
# build rpncalc
# ----------------------------------------------------------------------------

build_rpncalc : $(RPNCALC_BIN)

$(RPNCALC_BIN) : $(RPNCALC_OBJS)
	$(LD) $(LDFLAGS) -o $(RPNCALC_BIN) $(RPNCALC_OBJS) $(RPNCALC_LIBS)

# ----------------------------------------------------------------------------
# clean rpncalc
# ----------------------------------------------------------------------------

clean_rpncalc :
	$(RM) $(RMFLAGS) $(RPNCALC_OBJS) $(RPNCALC_BIN)

# ----------------------------------------------------------------------------
# check rpncalc
# ----------------------------------------------------------------------------

check_rpncalc : \
	check_add \
	check_sub \
	check_mul \
	check_div \
	check_mod \
	check_fibonacci

check_add : build_rpncalc
	@echo "=== $@ ==="
	@echo ""
	./$(RPNCALC_BIN) $(RPNCALC_OPTS) "3 add" compile "9 run" execute run
	@echo ""

check_sub : build_rpncalc
	@echo "=== $@ ==="
	@echo ""
	./$(RPNCALC_BIN) $(RPNCALC_OPTS) "3 sub" compile "9 run" execute run
	@echo ""

check_mul : build_rpncalc
	@echo "=== $@ ==="
	@echo ""
	./$(RPNCALC_BIN) $(RPNCALC_OPTS) "3 mul" compile "9 run" execute run
	@echo ""

check_div : build_rpncalc
	@echo "=== $@ ==="
	@echo ""
	./$(RPNCALC_BIN) $(RPNCALC_OPTS) "3 div" compile "9 run" execute run
	@echo ""

check_mod : build_rpncalc
	@echo "=== $@ ==="
	@echo ""
	./$(RPNCALC_BIN) $(RPNCALC_OPTS) "3 mod" compile "9 run" execute run
	@echo ""

check_fibonacci : build_rpncalc
	@echo "=== $@ ==="
	@echo ""
	./$(RPNCALC_BIN) $(RPNCALC_OPTS) "fib" compile "0 1" execute run run run run run run run run run run run run run run run
	@echo ""

# ----------------------------------------------------------------------------
# dependencies
# ----------------------------------------------------------------------------

State.o : State.cc \
	$(RPNCALC_HDRS)

Logger.o : Logger.cc \
	$(RPNCALC_HDRS)

Console.o : Console.cc \
	$(RPNCALC_HDRS)

Runnable.o : Runnable.cc \
	$(RPNCALC_HDRS)

Listener.o : Listener.cc \
	$(RPNCALC_HDRS)

Parser.o : Parser.cc \
	$(RPNCALC_HDRS)

Buffer.o : Buffer.cc \
	$(RPNCALC_HDRS)

ByteCode.o : ByteCode.cc \
	$(RPNCALC_HDRS)

HostCode.o : HostCode.cc \
	$(RPNCALC_HDRS)

Compiler.o : Compiler.cc \
	$(RPNCALC_HDRS)

BasicBlock.o : BasicBlock.cc \
	$(RPNCALC_HDRS)

Calculator.o : Calculator.cc \
	$(RPNCALC_HDRS)

Program.o : Program.cc \
	$(RPNCALC_HDRS)

main.o : main.cc \
	$(RPNCALC_HDRS)

# ----------------------------------------------------------------------------
# End-Of-File
# ----------------------------------------------------------------------------
