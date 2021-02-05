CC=g++
CCFLAGS= -Wall -Werror -std=c++11 -g
SRC= $(wildcard ../src/*.cc)
OBJ= $(SRC:.cc=.o)
TST= $(wildcard *.cc)
OBJ_TEST = $(filter-out ../main.o, $(OBJ)) $(TST:.cc=.o)

testcase : $(OBJ_TEST) 
	$(CC) $(CCFLAGS)  -o $@ $^

%.o: %.cc
	$(CC) $(CCFLAGS) -I../include -o $@ -c $<

clean :
	rm -f $(OBJ_TEST) testcase
