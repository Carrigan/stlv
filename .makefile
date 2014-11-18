all: stlv_test_main

stlv_test_main: main.o stlv_test.o stlv.o
	gcc main.o stlv_test.o stlv.o -o main.exe

main.o: stlv.o stlv_test.o
	gcc -c main.c

stlv_test.o:
	gcc -c stlv_test.c

stlv.o: 
	gcc -c stlv.c

clean:
	rm -f *.o