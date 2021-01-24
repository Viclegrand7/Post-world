BIN := test
DBGDIR := debug
RLSDIR := bin
RLSOPT := 1


CC := g++
CFLAGS = -std=c++17 -g -Wall -Wextra -Werror -Wshadow -Wunreachable-code \
-Wuninitialized -Wduplicated-cond -Wduplicated-branches -Wpedantic -m64 \
-I $(INCDIR) -I /usr/include -I $(GAMEINCDIR)
RLSFLAGS = -std=c++17 -m64 -O3 -DNDEBUG -I $(INCDIR) -I /usr/include

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

OBJ := $(patsubst %.hh, %.o, $(GCH))
###############################################################################################################

GAMEINCDIR := ../../Game/include
INCDIR := include
OBJDIR := obj
SRCDIR := src

DEPDIR := $(OBJDIR)/.deps
GCHDEPDIR := $(INCDIR)/.deps
GCHDIR := $(INCDIR)/.hh

POSTCOMPILE = mv -f $(DEPDIR)/$*.Td $(DEPDIR)/$*.d && touch $@
POSTINCLUDE = mv -f $(GCHDEPDIR)/$*.Td $(GCHDEPDIR)/$*.d && touch $@

COMPILE = $(CC) $(DEPFLAGS) $(REALFLAGS) $(TARGET_ARCH) -c
COMPINC = $(CC) $(GCHDEPFLAGS) $(REALFLAGS) $(TARGET_ARCH) -c

OBJS := $(patsubst %.o, $(OBJDIR)/%.o, $(OBJ))
GCHS := $(patsubst %.hh, $(GCHDIR)/%.hh, $(GCH))

all : $(GCHS) $(OBJS)
ifeq (0, $(RLSOPT))
all : $(DBGDIR)/$(BIN)
endif

$(RLSDIR)/$(BIN) : $(patsubst %.o, $(OBJDIR)/%.o, $(OBJ))
	$(CC) $(REALFLAGS) $^ $(LDLIBS) -o $@

$(DBGDIR)/$(BIN) : $(patsubst %.o, $(OBJDIR)/%.o, $(OBJ))
	$(CC) $(REALFLAGS) $^ $(LDLIBS) -o $@


$(OBJDIR)/%.o : $(SRCDIR)/%.cpp $(DEPDIR)/%.d | $(DEPDIR)
	$(COMPILE) -o $@ $<
	$(POSTCOMPILE)

$(GCHDIR)/%.hh : $(INCDIR)/%.hh $(GCHDEPDIR)/%.d | $(GCHDIR) $(GCHDEPDIR)
	$(COMPINC) -o $@ $<
	$(POSTINCLUDE)

$(DEPDIR) : ; @mkdir -p $@
$(GCHDIR) : ; @mkdir -p $@
$(GCHDEPDIR) : ; @mkdir -p $@

DEPFILES := $(OBJ:%.o=$(DEPDIR)/%.d) $(GCH:%.hh=$(GCHDEPDIR)/%.d)
$(DEPFILES):
include $(wildcard $(DEPFILES))


.PHONY : clean testDebug testRelease debug love all
clean : 
	rm -f $(DBGDIR)/$(BIN) $(RLSDIR)/$(BIN) $(patsubst %.o, $(OBJDIR)/%.o, $(OBJ)) $(patsubst %.hh, $(GCHDIR)/%.hh, $(GCH))

testDebug : REALFLAGS = $(CFLAGS)
testDebug : all $(DBGDIR)/$(BIN)

testRelease : REALFLAGS = $(RLSFLAGS)
testRelease : all $(RLSDIR)/$(BIN)

debug : REALFLAGS = $(CFLAGS)
debug : all

love : 
	@echo "not war"