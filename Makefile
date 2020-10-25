target: main.o list.o
	gcc -g3 -o main main.o list.o

main.o: main.c
	gcc -g3 -c main.c

list.o: list.c list.h
	gcc -g3 -c list.c

clean:
	rm main
	rm *.o