hw1: hw1.o hexdump.o enc-base64.o dec-base64.o
	gcc -o hw1 -g hw1.o hexdump.o enc-base64.o dec-base64.o

hw1.o: hw1.c hexdump.h enc-base64.h dec-base64.h
	gcc -g -c -Wall hw1.c

hexdump.o: hexdump.c hexdump.h
	gcc -g -c -Wall hexdump.c

enc-base64.o: enc-base64.c enc-base64.h
	gcc -g -c -Wall enc-base64.c

dec-base64.o: dec-base64.c dec-base64.h
	gcc -g -c -Wall dec-base64.c

clean:
	rm -f *.o hw1
