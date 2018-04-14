CXX=clang++
CXXFLAGS=-g --std=c++17

NAME=bfsi

TARGET=build/$(NAME)
TARGET_LIBS=$(wildcard src/*.hpp)

all: $(TARGET) | build

run: all
	$(TARGET)

$(TARGET): src/main.cpp $(TARGET_LIBS)
	$(CXX) $(CXXFLAGS) $< -o $@

build:
	mkdir build

clean:
	rm $(TARGET) -f
