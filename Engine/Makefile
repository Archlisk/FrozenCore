OBJECTS = $(patsubst %.cpp,%.o,$(shell find ./ -name '*.cpp'))

INCLUDE_DIRS = \
	       ./

OUT = ../Bin/Engine

CXX = g++
CXX_FLAGS = -std=c++20 -O2 -rdynamic -DENGINE -include FC/FC.h `pkg-config --cflags freetype2`
INCLUDE_FLAGS = $(addprefix -I,$(INCLUDE_DIRS))

DEPS = $(patsubst %.o,%.d,$(OBJECTS))

LNK = g++
LNK_FLAGS = -lglfw -lGLEW -lGL -ldl `pkg-config --libs freetype2` -rdynamic

$(OUT): $(OBJECTS)
	@echo Linking $(OUT)...
	@$(LNK) $(LNK_FLAGS) -o $(OUT) $(OBJECTS)

clean:
	-rm $(OBJECTS) $(DEPS) $(OUT)

-include $(DEPS)

%.o: %.cpp
	@echo Compiling $@...
	@$(CXX) $(CXX_FLAGS) $(INCLUDE_FLAGS) -MM -MT $@ -MF $(patsubst %.o,%.d,$@) $<
	@$(CXX) $(CXX_FLAGS) $(INCLUDE_FLAGS) -o $@ -c $<
