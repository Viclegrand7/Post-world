BIN := test
DBGDIR := debug
RLSDIR := bin


CC := g++
CFLAGS = -std=c++17 -g -Wall -Werror -Wshadow -Wunreachable-code \
-Wuninitialized -Wduplicated-cond -Wduplicated-branches -Wpedantic -m64 \
-I $(INCDIR) -I /usr/include -I $(GAMEINCDIR)
RLSFLAGS = -std=c++17 -m64 -O3 -DNDEBUG -I $(INCDIR) -I$(GAMEINCDIR) -I /usr/include

DEPFLAGS = -MT $@ -MMD -MP -MF $(DEPDIR)/$*.Td
GCHDEPFLAGS = -MT $@ -MMD -MP -MF $(GCHDEPDIR)/$*.Td

DBGFLAG := $(filter debug testDebug, $(MAKECMDGOALS))
REALFLAGS = $(if $(DBGFLAG), $(CFLAGS), $(RLSFLAGS))

LDLIBS := -lGL -lGLU -lSDL2 -lSDL2_image

###############################################################################################################
GCH := GrE_Camera.gch GrE_Player.gch GrE_Item.gch GrE_Weapon.gch GrE_Gun.gch GrE_PowerUp.gch \
GrE_Particule.gch GrE_Loader.gch GrE_Level.gch GrE_Board.gch GrE_Ennemy.gch

OBJ = $(filter-out main.o, $(patsubst $(SRCDIR)/%.cc, %.o, $(wildcard $(SRCDIR)/*.cc)))
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


.PHONY : clean debug testDebug testRelease nsfw love all
clean : 
	rm -f $(DBGDIR)/$(BIN) $(RLSDIR)/$(BIN) $(patsubst %.o, $(OBJDIR)/%.o, $(OBJ)) $(patsubst %.gch, $(GCHDIR)/%.gch, $(GCH))

testDebug : $(REALFLAGS) = $(CFLAGS)
testDebug : all $(DBGDIR)/$(BIN)

testRelease : $(REALFLAGS) = $(RLSFLAGS)
testRelease : all $(RLSDIR)/$(BIN)

debug : $(GCHS) $(OBJS)

nsfw : clean
	@echo "That was possibly the worst idea you could have..."
nsfw : $(REALFLAGS) += -DNSFW
nsfw : all

love : 
	@echo "not war"