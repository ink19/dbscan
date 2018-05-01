CC = gcc
CFLAGS = -g

all: main

main: main.o dbscan.o

main.o: main.c dbscan.h

dbscan.o: dbscan.c dbscan.h

clean:
	rm -rf main *.o

run:
	./main ./data/a.data ./diff_data/a.csv 1.2 15
	./main ./data/long1.data ./diff_data/long1.csv 0.2 6
	./main ./data/spiral.data ./diff_data/spiral.csv 1 5
	./main ./data/moon.data ./diff_data/moon.csv 0.2 5
	./main ./data/square1.data ./diff_data/square1.csv 1 8
	./main ./data/sizes5.data ./diff_data/sizes5.csv 1 11
	./main ./data/smile.data ./diff_data/smile.csv 0.08 4