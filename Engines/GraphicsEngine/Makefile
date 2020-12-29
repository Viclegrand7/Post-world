BIN = test


CC = g++


CFLAGS = -std=c++17 -g -Wall -Wextra -Werror -Wshadow -Wdouble-promotion -Wunreachable-code \
-Wuninitialized -Wfloat-equal -Weffc++ -Wduplicated-cond -Wduplicated-branches -m64

LDFLAGS
LDLIBS


RLSFLAGS = -std=c++17 -m64 -O3 -DNDEBUG
DEPDIR := obj/.deps
DEPFLAGS = -MT $@ -MMD -MP -MF $(DEPDIR)/$*.Td
POSTCOMPILE = mv -f $(DEPDIR)/$*.Td $(DEPDIR)/$*.d && touch $@

COMPILE.h = $(CC) $(DEPFLAGS) $(CFLAGS) $(CPPFLAGS) $(TARGET_ARCH) -c
COMPILE.c = $(CC) $(DEPFLAGS) $(CFLAGS) $(CPPFLAGS) $(TARGET_ARCH) -c

LINK.o = $(CC) $(LDFLAGS) $(TARGET_ARCH) 



cd obj

g++ -c ../src/*.cc -std=c++17 -g -Wall -m64 -I ../include -I ../SDL2

cd .. && g++ ./obj/*.o -o debug/main -lGL -lGLU -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf -lSDL2_net






(optimisé)
cd obj

g++ -c ../src/*.cc -std=c++17 -m64 -O3 -Wall -I ../include -I ../SDL2 -DNDEBUG && cd ..

g++ ./obj/*.o -o bin/main -s -lGL -lGLU -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf -lSDL2_net -DNDEBUG






testDebug:
testRelease:
make debug:
all:



%.o : %.c
%.o : %.c $(DEPDIR)/%.d | $(DEPDIR)
        $(COMPILE.c) $(OUTPUT_OPTION) $<
        $(POSTCOMPILE)

$(DEPDIR): ; @mkdir -p $@

DEPFILES := $(SRCS:%.c=$(DEPDIR)/%.d)
$(DEPFILES):
include $(wildcard $(DEPFILES))