CXX=clang++
CXXFLAGS=-g --std=c++17

NAME=bfsi

TARGET=build/$(NAME)
LIBS=$(shell find . -type f -iname '*.hpp')
$(info LIBS $(LIBS))

all: $(TARGET) | build

run: all
	$(TARGET)

$(TARGET): src/main.cpp $(LIBS)
	$(CXX) $(CXXFLAGS) $< -o $@

build:
	mkdir build

clean:
	rm $(TARGET) -f
