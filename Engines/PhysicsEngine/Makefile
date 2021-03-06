BIN := test
DBGDIR := debug
RLSDIR := bin
RLSOPT := 1


CC := g++
CFLAGS = -std=c++17 -g -Wall -Wextra -Werror -Wshadow -Wunreachable-code -Wno-error=deprecated-copy -Wno-deprecated-copy \
-Wuninitialized -Wduplicated-cond -Wduplicated-branches -Wpedantic -m64 \
-I $(INCDIR) -I /usr/include -I $(GAMEINCDIR)
RLSFLAGS = -std=c++17 -m64 -O3 -DNDEBUG -I $(INCDIR) -I$(GAMEINCDIR) -I /usr/include

DEPFLAGS = -MT $@ -MMD -MP -MF $(DEPDIR)/$*.Td
GCHDEPFLAGS = -MT $@ -MMD -MP -MF $(GCHDEPDIR)/$*.Td

DBGFLAG := $(filter debug testDebug, $(MAKECMDGOALS))
REALFLAGS = $(if $(DBGFLAG), $(CFLAGS), $(RLSFLAGS))

LDLIBS := -lGL -lGLU -lSDL2 -lSDL2_image

###############################################################################################################
GCH := PhE_Board.gch PhE_Collision.gch PhE_CollisionBox.gch PhE_CollisionQuad.gch PhE_CollisionSphere.gch PhE_Ennemy.gch PhE_Item.gch PhE_Player.gch 

OBJ := $(patsubst %.gch, %.o, $(GCH))
###############################################################################################################

GAMEINCDIR := ../../Game/include
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

all : $(GCHS) $(OBJS)
ifeq (0, $(RLSOPT))
all : $(DBGDIR)/$(BIN)
endif

$(RLSDIR)/$(BIN) : $(patsubst %.o, $(OBJDIR)/%.o, $(OBJ))
	$(CC) $(REALFLAGS) $^ $(LDLIBS) -o $@

$(DBGDIR)/$(BIN) : $(patsubst %.o, $(OBJDIR)/%.o, $(OBJ))
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


.PHONY : clean testDebug testRelease debug love all
clean : 
	rm -f $(DBGDIR)/$(BIN) $(RLSDIR)/$(BIN) $(patsubst %.o, $(OBJDIR)/%.o, $(OBJ)) $(patsubst %.gch, $(GCHDIR)/%.gch, $(GCH))

testDebug : REALFLAGS = $(CFLAGS)
testDebug : all $(DBGDIR)/$(BIN)

testRelease : REALFLAGS = $(RLSFLAGS)
testRelease : all $(RLSDIR)/$(BIN)

debug : REALFLAGS = $(CFLAGS)
debug : all

love : 
	@echo "not war"