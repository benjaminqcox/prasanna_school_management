all: main

main: main.o libs
	gcc main.o -o main -L. school.a userInput.a

main.o: main.c
	gcc -c main.c -o main.o

userInput.o: userInput.c
	gcc -c userInput.c -o userInput.o

userInput.a: userInput.o
	ar rcs userInput.a userInput.o

school.o: school.c
	gcc -c school.c -o school.o

school.a: school.o
	ar rcs school.a school.o

libs: school.a userInput.a

clean:
	rm -f main *.o *.a