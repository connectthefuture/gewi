CXX=g++
CXXFLAGS=-g -Wall -Werror -Wpedantic
LDFLAGS=-lGLEW -lGL -lglfw3 -lX11 -lXxf86vm -lpthread -lXrandr -lXi -lSOIL

UTILS_CPP := $(wildcard utils/*.cpp)
UTILS_OBJ := $(UTILS_CPP:.cpp=.o)

all: main.out

main.out: main.o utils.a
	$(CXX) main.o utils.a $(LDFLAGS) -o $@

utils.a: $(UTILS_OBJ)
	ar r $@ $(UTILS_OBJ) -s

gewi.a:

clean:
	rm -rf *.o utils.a gewi.a $(UTILS_OBJ)