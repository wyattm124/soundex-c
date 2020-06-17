CC = gcc
DEBUGFLAGS = -g -Wall

#This is a simple make file to run the compile the implementation of Soundex
# and clean the folder

all: SoundexC

SoundexC: Soundex.c
	$(CC) Soundex.c -o Sndx

e:
	vim Soundex.c

clean:
	rm -f Sndx test_out

test:
	./wiki_tests
