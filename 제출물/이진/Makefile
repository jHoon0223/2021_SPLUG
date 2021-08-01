project : project.o Word.o User.o header.h
	gcc -o project project.o Word.o User.o

project.o : project.c
	gcc -c project.c

Word.o : Word.c
	gcc -c Word.c

User.o : User.c
	gcc -c User.c

clean :
	rm *.o project
