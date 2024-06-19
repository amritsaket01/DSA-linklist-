all:   main.o driver.o 
	gcc main.c driver.c -o result.exe

driver.o : driver.c
	gcc -c driver.c

main.o : main.c   
	gcc -c main.c


