ifeq ($(OS),Windows_NT)
#LINKER_FLAGS =
	COMPILER_FLAGS = -std=c++11 -Wall
#INCLUDE_PATHS = 
#LIBRARY_PATHS = 

	RM = del /Q
	FixPath = $(subst /,\,$1)
else
#LINKER_FLAGS = 
	COMPILER_FLAGS = -std=c++11 -Wall
#INCLUDE_PATHS =
#LIBRARY_PATHS =
	
	RM = rm -f
	FixPath = $1
endif

OBJS = headerGen.cpp main.cpp

OBJ_NAME = headerGen

all : $(OBJS)
	g++ $(OBJS) $(COMPILER_FLAGS) -o $(OBJ_NAME)
#g++ $(OBJS) $(COMPILER_FLAGS) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(LINKER_FLAGS) -o $(OBJ_NAME)

clean:
	$(RM) headerGen.exe