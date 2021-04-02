CC = g++
CFLAGS = -Wall -O3 --std=c++11

main : main.o random.o blocking.o print.o
	$(CC) random.o blocking.o main.o -o main
main.o : main.cpp
	$(CC) -c $< -o  $@ $(CFLAGS)
%.o : %.cpp %.h
	$(CC) -c $< -o $@ $(CFLAGS)
clean :
	rm *.o main seed.out
