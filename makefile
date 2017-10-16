all:
	gcc -o main main3.c funciones.c -lpthread -Wall
	echo "./main -i words.txt -h 100 -c 7 -n 10 -m 9 -s salida.txt"
	
