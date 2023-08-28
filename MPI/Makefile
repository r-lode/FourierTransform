CC = mpicc
FFLAGS = -Wall -std=c99 
LFLAGS = -lgomp -lm
OBJECTS = dft_mpi.o

main.exe:  $(OBJECTS)
	$(CC) $(LFLAGS) $(OBJECTS) -lm  -o main.exe

%.o: %.c
	$(CC) $(FFLAGS) -c  $<

clean:
	rm -f $(OBJECTS) *.exe *.data *.out *.txt *.m *.txt  