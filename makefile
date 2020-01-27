TARGET=test_price

# all .c files in this directory are my sources
SOURCES=$(wildcard *.cpp)

OBJS=$(SOURCES:.cpp=.o)

#INC_DIR=../include
CC=g++
CFLAGS= -c -pedantic -Wall -Werror -Wconversion -ansi -o #-I$(INC_DIR)
CXXFLAGS=$(CFLAGS)
LDFLAGS= -g
LDLIBS = -lgtest -lgtest_main -pthread

.PHONY: clean run gdb

$(TARGET): $(OBJS)

#include .depends

#.depends:
#	$(CC) -MM -I$(INC_DIR) $(SOURCES) > .depends

clean:
	rm -f $(OBJS) $(TARGET) .depends

run: $(TARGET)
	./$(TARGET)

run_randomized: $(TARGET)
	./$(TARGET) --gtest_filter=SchoolAdvancedTests.RandomizeGrouping --gtest_repeat=100

# Do not forget to add '-g' to CFLAGS
gdb: $(TARGET)
	gdb -q ./$(TARGET)
