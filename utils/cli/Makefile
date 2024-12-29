#
# Kitten Command-Line Utility Makefile
# (C) 2024 Nazar Fedorenko
#	
# Licensed under the GNU GPLv3 license.
#	
# This program is free software: you can redistribute it and/or modify it 
# under the terms of the GNU General Public License as published by the 
# Free Software Foundation, either version 3 of the License, or (at your option) 
# any later version.
#
# This program is distributed in the hope that it will be useful, but 
# WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY 
# or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License 
# for more details.
#
# You should have received a copy of the GNU General Public License along 
# with this program. If not, see <https://www.gnu.org/licenses/>.
#	
# REMINDER: Kitten Library used by this utility is licensed under the
# BSD 2-Clause license.
#

#CC = gcc
#CXX = g++
CC = clang
CXX = clang++

CFLAGS = -O3 -DNDEBUG -I../../lib
LDFLAGS =

# Strip debug symbols when compiling with GCC;
# Clang doesn't include them by default
ifeq ($(CC),gcc)
	LDFLAGS += -s
endif

# Uncomment to enable AVX support
#CFLAGS += -mavx

kitten: KittenCLI.o Kitten.o
	$(CXX) $(LDFLAGS) $^ -o $@
	
Kitten.o: ../../lib/Kitten.c ../../lib/Kitten.h
	$(CC) -c $(CFLAGS) $< -o $@
	
KittenCLI.o: KittenCLI.cpp
	$(CXX) -c $(CFLAGS) -std=c++20 $< -o $@
	
clean:
	rm -f kitten Kitten.o KittenCLI.o