EXEC = turing
CC = g++
CFLAGS = -c 

$(EXEC) : turingmachinesimulator.o
	$(CC) -o $(EXEC) turingmachinesimulator.o

turingmachinesimulator.o: turingmachinesimulator.cc
	$(CC) $(CFLAGS) turingmachinesimulator.cc

clean :
	rm *.o
