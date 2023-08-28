CC = gcc
FFLAGS = -Wall -std=c99 -fopenmp
LFLAGS = -lgomp -lm
OBJECTS = dft_coarse.o

main.exe:  $(OBJECTS)
	$(CC) $(LFLAGS) $(OBJECTS) -lm -fopenmp -o main.exe

%.o: %.c
	$(CC) $(FFLAGS) -c  $<

clean:
	rm -f $(OBJECTS) *.exe *.data *.out *.txt *.m *.txt