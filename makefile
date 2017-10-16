all:
	gcc -o main.out main3.c funciones.c -lpthread -Wall
	echo "./main.out -i words.txt -h 100 -c 7 -n 10 -m 9 -s salida.txt"
	
