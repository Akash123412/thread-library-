 final :
 	gcc -c main.c -o main.o
	gcc -c MyThread.c -o MyThread.o
	gcc main.o MyThread.o -o my_program

	./my_program