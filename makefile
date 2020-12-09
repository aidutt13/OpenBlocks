target 	:= blocks
objs 	:= Main.o 

CXX 	:= clang++
LIBS 	:= -lGLEW -lX11 -lGLU -lGL -lpng16 -lz -lpthread
CFLAGS 	:= -Wall -Wextra --std=c++17 -O3 $(LIBS)

SRCDIR = src
OBJDIR = obj
DEPSDIR = deps
INCDIR = include

OBJ := $(patsubst %.o, $(OBJDIR)/%.o, $(objs))

all: $(target)

deps := $(patsubst $(OBJDIR)/%.o, $(DEPSDIR)/%.d, $(OBJ))
-include $(deps)
DEPFLAGS = -MMD -MF $(patsubst $(OBJDIR)/%.o, $(DEPSDIR)/%.d, $@)

$(target): $(OBJ)
	$(CXX) $(CFLAGS) -o $@ $^

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) $(CFLAGS) -c $< $(DEPFLAGS) -I$(INCDIR)


clean:
	@echo Removing obj files...
	@rm -f $(OBJ) $(target) $(DEPSDIR)/$(deps)

.PHONY: clean print