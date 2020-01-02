CC = gcc -Wall -Wextra


interpretor : interpretor.c matrix.o cursor.o stack.o debugging.o
	$(CC) $^ -o $@ -g -lm

debugger : debugger.c matrix.o cursor.o stack.o debugging.o
	$(CC) $^ -o $@ -g -lm

debugging.o : debugging.c debugging.h stack.o cursor.o matrix.o
	$(CC) -c $< -o $@ -g -lm

matrix.o : matrix.c matrix.h
	$(CC) -c $< -o $@

stack.o : stack.c stack.h
	$(CC) -c $< -o $@

cursor.o : cursor.c cursor.h
	$(CC) -c $< -o $@
	

clean :
	rm -vf interpretor debugger *.o

re :
	clear; make clean; make interpretor debugger




 