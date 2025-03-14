CXX = g++
CXXFLAGS = -ggdb -std=c++20 -Wall -Wextra -Werror -Wfatal-errors -pedantic -Isrc
GTEST_CXXFLAGS = $(shell pkg-config --cflags gtest 2>/dev/null || echo "-I/usr/include")
GTEST_LDFLAGS = $(shell pkg-config --libs gtest 2>/dev/null || echo "-lgtest -lgtest_main -pthread")

all: student_gtests

dijkstras.o: src/dijkstras.cpp src/dijkstras.h
	$(CXX) $(CXXFLAGS) -c src/dijkstras.cpp -o dijkstras.o

ladder.o: src/ladder.cpp src/ladder.h
	$(CXX) $(CXXFLAGS) -c src/ladder.cpp -o ladder.o

student_gtests: gtest/student_gtests.cpp dijkstras.o ladder.o
	$(CXX) $(CXXFLAGS) $(GTEST_CXXFLAGS) gtest/student_gtests.cpp dijkstras.o ladder.o -o student_gtests $(GTEST_LDFLAGS) -lgtest_main

clean:
	rm -f *.o student_gtests
