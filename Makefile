CXX=g++
CXXFLAGS=-g -Wall -Werror -Wpedantic -std=c++11
LDFLAGS=-lGLEW -lGL -lglfw3 -lX11 -lXxf86vm -lpthread -lXrandr -lXi -lSOIL

UTILS_CPP := $(wildcard utils/*.cpp)


GEWI_CORE_CPP := $(wildcard gewi/core/*.cpp)
GEWI_LAYOUT_CPP := $(wildcard gewi/layout/*.cpp)
GEWI_RENDER_CPP := $(wildcard gewi/render/*.cpp)
GEWI_INTERACTION_CPP := $(wildcard gewi/interaction/*.cpp)
GEWI_WIDGETS_CPP := $(wildcard gewi/widgets/*.cpp)

UTILS_OBJ := $(UTILS_CPP:.cpp=.o)
GEWI_CORE_OBJ := $(GEWI_CORE_CPP:.cpp=.o)
GEWI_LAYOUT_OBJ := $(GEWI_LAYOUT_CPP:.cpp=.o)
GEWI_INTERACTION_OBJ := $(GEWI_INTERACTION_CPP:.cpp=.o)
GEWI_RENDER_OBJ := $(GEWI_RENDER_CPP:.cpp=.o)
GEWI_WIDGETS_OBJ := $(GEWI_WIDGETS_CPP:.cpp=.o)


all: main.out

main.out: main.o utils.a gewi.a
	$(CXX) $^ $(LDFLAGS) -o $@

utils.a: $(UTILS_OBJ)
	ar r $@ $^ -s

gewi.a: $(GEWI_CORE_OBJ) $(GEWI_RENDER_OBJ) $(GEWI_LAYOUT_OBJ) $(GEWI_INTERACTION_OBJ) $(GEWI_WIDGETS_OBJ)
	ar r $@ $^ -s
clean:
	rm -rf *.o utils.a gewi.a $(UTILS_OBJ) $(GEWI_CORE_OBJ) $(GEWI_RENDER_OBJ) $(GEWI_LAYOUT_OBJ) $(GEWI_INTERACTION_OBJ) $(GEWI_WIDGETS_OBJ)