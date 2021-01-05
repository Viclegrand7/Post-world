BIN := test
DBGDIR := debug
RLSDIR := bin
RLSOPT := 1

GRAPHDIR := ../Engines/GraphicsEngine/
GAMEDIR := ../Engines/GameEngine/
PHYSDIR := ../Engines/PhysicsEngine/

CC := g++
CFLAGS = -std=c++17 -g -Wall -Wextra -Werror -Wshadow -Wdouble-promotion -Wunreachable-code \
-Wuninitialized -Wfloat-equal -Weffc++ -Wduplicated-cond -Wduplicated-branches -Wpedantic -m64 \
-I $(INCDIR)
RLSFLAGS = -std=c++17 -m64 -O3 -DNDEBUG -I $(INCDIR)

DEPFLAGS = -MT $@ -MMD -MP -MF $(DEPDIR)/$*.Td
GCHDEPFLAGS = -MT $@ -MMD -MP -MF $(GCHDEPDIR)/$*.Td

ifeq (0, $(RLSOPT))
REALFLAGS = $(CFLAGS)
endif
ifeq (1, $(RLSOPT))
REALFLAGS = $(RLSFLAGS)
endif

LDLIBS := -lGL -lGLU -lSDL2 -lSDL2_image

###############################################################################################################""
OBJ := test.o

GCH := test.gch
###############################################################################################################""

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


all : Graphics Game Physics
	g++ #ADD THE COMMAND TO LINK THE .O
	#Fusion
###########################################

Graphics : 
	cd GRAPHDIR && make
Game : 
	cd GAMEDIR && make
Physics : 
	cd PHYSDIR && make

testDebug : GraphTestDebug GameTestDebug PhysTestDebug
GraphTestDebug : 
	cd GRAPHDIR && make testDebug
GameTestDebug : 
	cd GAMEDIR && make testDebug
PhysTestDebug : 
	cd PHYSDIR && make testDebug

testRelease : GraphTestRelease GameTestRelease PhysTestRelease
GraphTestRelease : 
	cd GRAPHDIR && make testRelease
GameTestRelease :
	cd GAMEDIR && make testRelease
PhysTestRelease : 
	cd PHYSDIR && make testRelease

debug : GraphDebug GameDebug PhysDebug
GraphDebug : 
	cd GRAPHDIR && make debug
GameDebug :
	cd GAMEDIR && make debug
PhysDebug : 
	cd PHYSDIR && make debug


.PHONY : clean testDebug testRelease nsfw love all Graphics Game Physics testDebug \
GraphTestDebug GameTestDebug PhysTestDebug testRelease GraphTestRelease GameTestRelease \
PhysTestRelease debug GraphDebug GameDebug PhysDebug


clean : 
	cd GRAPHDIR && make clean
	cd GAMEDIR && make clean
	cd PHYSDIR && make clean

nsfw :
	@echo "That was possibly the worst idea you could have..."

love : 
	@echo "not war"
###########################################
#Fusion actually


all : $(GCHDIR)/$(GCH) $(OBJDIR)/$(OBJ) 
ifeq (0, $(RLSOPT))
all : $(DBGDIR)/$(BIN)
endif

$(RLSDIR)/$(BIN) : $(OBJDIR)/$(OBJ) $(DEPDIR)/$(DEPFILES)
	$(CC) $(REALFLAGS) $(OBJDIR)/$(OBJ) $(LDLIBS) -o $(RLSDIR)/$(BIN)

$(DBGDIR)/$(BIN) : $(OBJDIR)/$(OBJ) $(DEPDIR)/$(DEPFILES)
	$(CC) $(REALFLAGS) $(OBJDIR)/$(OBJ) $(LDLIBS) -o $(DBGDIR)/$(BIN)


$(GCHDIR)/%.gch : $(INCDIR)/%.hh $(GCHDEPDIR)/%.d | $(GCHDIR) $(GCHDEPDIR)
	$(COMPINC) $(OUTPUT_OPTION) $<
	$(POSTINCLUDE)

$(OBJDIR)/%.o : $(SRCDIR)/%.cc $(DEPDIR)/%.d | $(DEPDIR)
	$(COMPILE) $(OUTPUT_OPTION) $<
	$(POSTCOMPILE)

$(DEPDIR) : ; @mkdir -p $@
$(GCHDIR) : ; @mkdir -p $@
$(GCHDEPDIR) : ; @mkdir -p $@

DEPFILES := $(OBJ:%.o=$(DEPDIR)/%.d) $(GCH:%.gch=$(GCHDEPDIR)/%.d)
$(DEPFILES):
sinclude $(wildcard $(DEPFILES))


.PHONY : clean testDebug testRelease nsfw love all
clean : 
	rm $(BIN) $(OBJDIR)/$(OBJ) $(GCHDIR)/$(GCH)

testDebug : REALFLAGS = $(CFLAGS)
testDebug : all $(DBGDIR)/$(BIN)

testRelease : REALFLAGS = $(RLSFLAGS)
testRelease : all $(RLSDIR)/$(BIN)

debug : REALFLAGS = $(CFLAGS)
debug : all

nsfw :
	@echo "That was possibly the worst idea you could have..."

love : 
	@echo "not war"