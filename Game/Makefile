BIN := RVZD
DBGDIR := debug
RLSDIR := bin


CC := g++
CFLAGS = -std=c++17 -g -Wall -Werror -Wshadow -Wunreachable-code \
-Wuninitialized -Wduplicated-cond -Wduplicated-branches -Wpedantic -m64 \
-I $(INCDIR) -I /usr/include -I $(PHYSENGINCDIR) -I$(GAMEENGINCDIR) -I$(GRAPHENGINCDIR)
RLSFLAGS = -std=c++17 -m64 -O3 -DNDEBUG -I $(PHYSENGINCDIR) -I$(GAMEENGINCDIR) -I$(GRAPHENGINCDIR) -I /usr/include

DEPFLAGS = -MT $@ -MMD -MP -MF $(DEPDIR)/$*.Td -I $(INCDIR) -I /usr/include -I $(PHYSENGINCDIR) -I$(GAMEENGINCDIR) -I$(GRAPHENGINCDIR)
GCHDEPFLAGS = -MT $@ -MMD -MP -MF $(GCHDEPDIR)/$*.Td -I $(INCDIR) -I /usr/include -I $(PHYSENGINCDIR) -I$(GAMEENGINCDIR) -I$(GRAPHENGINCDIR)

DBGFLAG := $(filter test, $(MAKECMDGOALS))
REALFLAGS = $(if $(DBGFLAG), $(CFLAGS), $(RLSFLAGS))

LDLIBS := -lGL -lGLU -lSDL2 -lSDL2_image

###############################################################################################################
GCH = $(patsubst $(INCDIR)/%.hh, %.gch, $(wildcard $(INCDIR)/*.hh))

OBJ = $(patsubst $(SRCDIR)/%.cc, %.o, $(wildcard $(SRCDIR)/*.cc))

###############################################################################################################

ENGOBJ  = $(filter-out $(PHYSENGDIR)/obj/main.o, $(patsubst $(PHYSENGDIR)/src/%.cc, $(PHYSENGDIR)/obj/%.o, $(wildcard $(PHYSENGDIR)/src/*.cc)))
ENGOBJ += $(filter-out $(GAMEENGDIR)/obj/main.o, $(patsubst $(GAMEENGDIR)/src/%.cc, $(GAMEENGDIR)/obj/%.o, $(wildcard $(GAMEENGDIR)/src/*.cc))) 
ENGOBJ += $(filter-out $(GRAPHENGDIR)/obj/main.o, $(patsubst $(GRAPHENGDIR)/src/%.cc, $(GRAPHENGDIR)/obj/%.o, $(wildcard $(GRAPHENGDIR)/src/*.cc)))


PHYSENGDIR := ../Engines/PhysicsEngine
GAMEENGDIR := ../Engines/GameEngine
GRAPHENGDIR := ../Engines/GraphicsEngine
PHYSENGINCDIR := $(PHYSENGDIR)/include
GAMEENGINCDIR := $(GAMEENGDIR)/include
GRAPHENGINCDIR := $(GRAPHENGDIR)/include

INCDIR := include
OBJDIR := obj
SRCDIR := src
TSTDIR := ../Engines/GameEngine

DEPDIR := $(OBJDIR)/.deps
GCHDEPDIR := $(INCDIR)/.deps
GCHDIR := $(INCDIR)/.gch

POSTCOMPILE = mv -f $(DEPDIR)/$*.Td $(DEPDIR)/$*.d && touch $@
POSTINCLUDE = mv -f $(GCHDEPDIR)/$*.Td $(GCHDEPDIR)/$*.d && touch $@

COMPILE = $(CC) $(DEPFLAGS) $(REALFLAGS) $(TARGET_ARCH) -c
COMPINC = $(CC) $(GCHDEPFLAGS) $(REALFLAGS) $(TARGET_ARCH) -c

OBJS := $(patsubst %.o, $(OBJDIR)/%.o, $(OBJ))
GCHS := $(patsubst %.gch, $(GCHDIR)/%.gch, $(GCH))

all : tmpall $(GCHS) $(OBJS)
all : $(RLSDIR)/$(BIN) #Does it work?

testcase :
	cd $(TSTDIR)/ ; make testcase

tmpall :
	@cd $(PHYSENGDIR) && make
	@cd $(GAMEENGDIR) && make
	@cd $(GRAPHENGDIR) && make


debug : REALFLAGS = $(CFLAGS) 
debug : tmpdebug $(GCHS) $(OBJS) 
debug : $(DBGDIR)/$(BIN)

tmpdebug : 
	@cd $(PHYSENGDIR) && make debug
	@cd $(GAMEENGDIR) && make debug
	@cd $(GRAPHENGDIR) && make debug


$(RLSDIR)/$(BIN) : $(patsubst %.o, $(OBJDIR)/%.o, $(OBJ))
	$(CC) $(REALFLAGS) $^ $(ENGOBJ) $(LDLIBS) -o $@

$(DBGDIR)/$(BIN) : $(patsubst %.o, $(OBJDIR)/%.o, $(OBJ))
	$(CC) $(REALFLAGS) $^ $(ENGOBJ) $(LDLIBS) -o $@


$(OBJDIR)/%.o : $(SRCDIR)/%.cc $(DEPDIR)/%.d | $(DEPDIR)
	$(COMPILE) -o $@ $<
	$(POSTCOMPILE)

$(GCHDIR)/%.gch : $(INCDIR)/%.hh $(GCHDEPDIR)/%.d | $(GCHDIR) $(GCHDEPDIR)
	$(COMPINC) -o $@ $<
	$(POSTINCLUDE)

$(DEPDIR) : ; @mkdir -p $@
$(GCHDIR) : ; @mkdir -p $@
$(GCHDEPDIR) : ; @mkdir -p $@
$(RLSDIR) : ; @mkdir -p $@
$(DBGDIR) : ; @mkdir -p $@

DEPFILES := $(OBJ:%.o=$(DEPDIR)/%.d) $(GCH:%.gch=$(GCHDEPDIR)/%.d)
$(DEPFILES):
include $(wildcard $(DEPFILES))


.PHONY : clean cleantest debug love all
clean : 
	rm -f $(DBGDIR)/$(BIN) $(RLSDIR)/$(BIN) $(patsubst %.o, $(OBJDIR)/%.o, $(OBJ)) $(patsubst %.gch, $(GCHDIR)/%.gch, $(GCH))
	@cd $(PHYSENGDIR) && make clean
	@cd $(GAMEENGDIR) && make clean
	@cd $(GRAPHENGDIR) && make clean

cleantest :
	cd $(TSTDIR)/ ; make cleantest

love : 
	@echo "not war"