all: main

main: main.o libs
	gcc main.o -o main -L. school.a

main.out: main.c
	gcc -c main.c -o main.o

school.out: school.c
	gcc -c school.c -o school.o

school.a: school.o
	ar rcs school.a school.o

libs: school.a

clean:
	rm -f main *.o *.a