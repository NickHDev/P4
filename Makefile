CC = g++
CFLAGS = -g -Wall -std=c++11
SRCS = main.cpp scanner.cpp parser.cpp semantics.cpp
OBJS = main.o scanner.o parser.o semantics.o
DEPS = $(SRCS) main.h scanner.h parser.h token.h node.h semantics.h
TARGET = P4
.PHONY: all clean
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	/bin/rm -f *.o $(TARGET)

help:
	@echo "Usage: make [all|clean|help]"
	@echo "    all:    Build the $(TARGET) TARGETS"
	@echo "    clean:  Remove build artifacts"
	@echo "    help:   Print this help message"
