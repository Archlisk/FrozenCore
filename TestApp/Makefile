OBJECTS = \
	  Main.o \
	  FastNoise.o

INCLUDE_DIRS = \
	       ../Engine/Source/ \
	       ./Source/

OUT = ../Bin/TestApp

CXX = g++
CXX_FLAGS = -std=c++17 -O2 -include Core/FC.h `pkg-config --cflags freetype2`
INCLUDE_FLAGS = $(addprefix -I,$(INCLUDE_DIRS))

OBJECT_PATHS = $(addprefix Source/,$(OBJECTS))
DEPS = $(patsubst %.o,%.d,$(OBJECT_PATHS))

LNK = g++ 
LNK_FLAGS = -lglfw -lGLEW -lGL -lpthread -lfreetype

$(OUT): $(OBJECT_PATHS) ../Bin/Engine.a
	@echo Linking $(OUT)...
	@$(LNK) $(LNK_FLAGS) -o $(OUT) $(OBJECT_PATHS) ../Bin/Engine.a

clean:
	rm $(OBJECT_PATHS) $(DEPS) $(OUT)

-include $(DEPS)

%.o: %.cpp
	@echo Compiling $@...
	@$(CXX) $(CXX_FLAGS) $(INCLUDE_FLAGS) -MM -MT $@ -MF $(patsubst %.o,%.d,$@) $<
	@$(CXX) $(CXX_FLAGS) $(INCLUDE_FLAGS) -o $@ -c $<

