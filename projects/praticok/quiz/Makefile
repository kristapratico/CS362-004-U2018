CFLAGS = -Wall -lm -w -std=c99

all: testme
	./testme

testme: testme.c
	gcc -o testme testme.c $(CFLAGS)

clean:
	rm -rf testme
