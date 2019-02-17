sum.exe : fun1.o fun2.o main.o
	gcc -o sum.exe main.o fun1.o fun2.o
main.o : fun1.h fun2.h main.c
	gcc -c main.c
fun1.o : fun1.h fun1.c
	gcc -c fun1.c
fun2.o : fun2.h fun2.c
	gcc -c fun2.c