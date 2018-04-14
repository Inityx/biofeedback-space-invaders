CXX=clang++
CXXFLAGS=-g --std=c++17

NAME=bfsi

TARGET=build/$(NAME)
TARGET_LIBS=$(wildcard src/lib/*.hpp)

all: $(TARGET) | build

run: all
	$(TARGET)

$(TARGET): src/main.cpp $(TARGET_LIBS)
	$(CXX) $(CFLAGS) $< -o $@

build:
	mkdir build

clean:
	rm $(TARGET) -f
