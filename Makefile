#!/usr/bin/make

CC = g++

  # compiler flags:
  #  -g     - this flag adds debugging information to the executable file
  #  -Wall  - this flag is used to turn on most compiler warnings
CFLAGS  = -std=c++17 -g -Wall

  # The build target
TARGET = idxs

all: $(TARGET)

$(TARGET): main.cpp
	$(CC) $(CFLAGS) -o $(TARGET) main.cpp 

clean:
	$(RM) $(TARGET)
