LIBS = 
LOCATELIB = 
CC = g++
CFLAGS = -Wall -g
NOMAPP = game
FICHIERS = main.cpp Character.o Spells.o Board.o Inventory.o Item.o

$(NOMAPP):	$(FICHIERS)
	@ $(CC) $(CFLAGS) -o $(@) $(^) $(LIBS)

Character.o:	Character.cpp Spells.h Item.h Inventory.h
	@ $(CC) $(CFLAGS) -c $(@:.o=.cpp) $(LOCATEGLUT)

Spells.o:	Spells.cpp 
	@ $(CC) $(CFLAGS) -c $(@:.o=.cpp) $(LOCATEGLUT)

Board.o:	Board.cpp Character.h 
	@ $(CC) $(CFLAGS) -c $(@:.o=.cpp)

Item.o:	Item.cpp 
	@ $(CC) $(CFLAGS) -c $(@:.o=.cpp)

Inventory.o:	Inventory.cpp Item.h
	@ $(CC) $(CFLAGS) -c $(@:.o=.cpp)		

clean:	
	@ rm -rf *.o $(NOMAPP)



#CFLAGS = -Wall
#CC=gcc
#SRC = $(wildcard *.c)
#OBJ = ${SRC:.c=.o}
#LIBS = -lglut -lGLU -lGL -lm
#EXEC = main

#main: $(OBJ)
#	${CC} $(CFLAGS) $(OBJ) -o $@ $(LIBS)
#	-rm -f ${OBJ}
#	./$(EXEC)

#%.o: %.c
#	${CC} ${CFLAGS} $(LIBS) -c $<

#.depend:
#	gcc -MM ${SOURCES_LIB} > $@
#-include .depend

#clean:
#	-rm -f ${OBJ} main