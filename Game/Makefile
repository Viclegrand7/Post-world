BIN := RVZD
DBGDIR := debug
RLSDIR := bin


CC := g++
CFLAGS = -std=c++17 -g -Wall -Wextra -Werror -Wshadow -Wunreachable-code \
-Wuninitialized -Wduplicated-cond -Wduplicated-branches -Wpedantic -m64 \
-I $(INCDIR) -I /usr/include -I $(PHYSENGINCDIR) -I$(GAMEENGINCDIR) -I$(GRAPHENGINCDIR)
RLSFLAGS = -std=c++17 -m64 -O3 -DNDEBUG -I $(PHYSENGINCDIR) -I$(GAMEENGINCDIR) -I$(GRAPHENGINCDIR) -I /usr/include

DEPFLAGS = -MT $@ -MMD -MP -MF $(DEPDIR)/$*.Td
GCHDEPFLAGS = -MT $@ -MMD -MP -MF $(GCHDEPDIR)/$*.Td

ifeq (0, $(RLSOPT))
REALFLAGS = $(CFLAGS)
endif
ifeq (1, $(RLSOPT))
REALFLAGS = $(RLSFLAGS)
endif

LDLIBS := -lGL -lGLU -lSDL2 -lSDL2_image

###############################################################################################################
GCH := 

OBJ := $(patsubst %.gch, %.o, $(GCH))
###############################################################################################################

PHYSENGOBJ = $(wildcard $(PHYSENGDIR)/obj/*.o)  
GAMEENGOBJ = $(wildcard $(GAMEENGDIR)/obj/*.o) 
GRAPHENGOBJ = $(wildcard $(GRAPHENGDIR)/obj/*.o) 
#CHECK WHICH IS BETTER. IF NOT NEEDED, SECOND OPTION IS PREFERRED
ENGOBJ = $(wildcard $(PHYSENGDIR)/obj/*.o) $(wildcard $(GAMEENGDIR)/obj/*.o) $(wildcard $(GRAPHENGDIR)/obj/*.o) 


PHYSENGDIR := ../Engines/PhysicsEngine
GAMEENGDIR := ../Engines/GameEngine
GRAPHENGDIR := ../Engines/GraphicsEngine
PHYSENGINCDIR := $(PHYSENGDIR)/include
GAMEENGINCDIR := $(GAMEENGDIR)/include
GRAPHENGINCDIR := $(GRAPHENGDIR)/include

INCDIR := include
OBJDIR := obj
SRCDIR := src

DEPDIR := $(OBJDIR)/.deps
GCHDEPDIR := $(INCDIR)/.deps
GCHDIR := $(INCDIR)/.gch

POSTCOMPILE = mv -f $(DEPDIR)/$*.Td $(DEPDIR)/$*.d && touch $@
POSTINCLUDE = mv -f $(GCHDEPDIR)/$*.Td $(GCHDEPDIR)/$*.d && touch $@

COMPILE = $(CC) $(DEPFLAGS) $(REALFLAGS) $(TARGET_ARCH) -c
COMPINC = $(CC) $(GCHDEPFLAGS) $(REALFLAGS) $(TARGET_ARCH) -c

OBJS := $(patsubst %.o, $(OBJDIR)/%.o, $(OBJ))
GCHS := $(patsubst %.gch, $(GCHDIR)/%.gch, $(GCH))

all : $(GCHS) $(OBJS) tmpall
all : $(RLSDIR)/$(BIN) #Does it work?

tmpall :
	@cd $(PHYSENGDIR) && make
	@cd $(GAMEENGDIR) && make
	@cd $(GRAPHENGDIR) && make


debug : REALFLAGS = $(CFLAGS) 
debug : $(GCHS) $(OBJS) tmpdebug
debug : $(DBGDIR)/$(BIN)

tmpdebug : 
	@cd $(PHYSENGDIR) && make debug
	@cd $(GAMEENGDIR) && make debug
	@cd $(GRAPHENGDIR) && make debug


$(RLSDIR)/$(BIN) : $(patsubst %.o, $(OBJDIR)/%.o, $(OBJ)) $(ENGOBJ)
	$(CC) $(REALFLAGS) $^ $(LDLIBS) -o $@

$(DBGDIR)/$(BIN) : $(patsubst %.o, $(OBJDIR)/%.o, $(OBJ)) $(ENGOBJ)
	$(CC) $(REALFLAGS) $^ $(LDLIBS) -o $@


$(OBJDIR)/%.o : $(SRCDIR)/%.cc $(DEPDIR)/%.d | $(DEPDIR)
	$(COMPILE) -o $@ $<
	$(POSTCOMPILE)

$(GCHDIR)/%.gch : $(INCDIR)/%.hh $(GCHDEPDIR)/%.d | $(GCHDIR) $(GCHDEPDIR)
	$(COMPINC) -o $@ $<
	$(POSTINCLUDE)

$(DEPDIR) : ; @mkdir -p $@
$(GCHDIR) : ; @mkdir -p $@
$(GCHDEPDIR) : ; @mkdir -p $@

DEPFILES := $(OBJ:%.o=$(DEPDIR)/%.d) $(GCH:%.gch=$(GCHDEPDIR)/%.d)
$(DEPFILES):
include $(wildcard $(DEPFILES))


.PHONY : clean debug love all
clean : 
	rm -f $(DBGDIR)/$(BIN) $(RLSDIR)/$(BIN) $(patsubst %.o, $(OBJDIR)/%.o, $(OBJ)) $(patsubst %.gch, $(GCHDIR)/%.gch, $(GCH))
	@cd $(PHYSENGDIR) && make clean
	@cd $(GAMEENGDIR) && make clean
	@cd $(GRAPHENGDIR) && make clean

love : 
	@echo "not war"