SRC_FILES := $(wildcard src/*.c)
EXCL_MAIN_SRC := $(filter-out src/main.c, $(SRC_FILES))


show: run
	feh im.ppm
run: raytracer
	./raytracer.out > im.ppm
	make cleano
raytracer: raytracer.o
	gcc *.o -lm -o raytracer.out
raytracer.o:
	gcc -Wall -Wextra -std=c2x -pedantic -lm -c src/*.c;

test.o:
	gcc -Wall -Wextra -std=c2x -pedantic -c tests/*.c $(EXCL_MAIN_SRC) -lm ;
test: test.o
	gcc *.o -lm -o test.out
	make cleano
run-test: test
	./test.out
cleano:
	rm *.o
