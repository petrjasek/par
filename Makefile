PP=g++
PFLAGS=-std=c++98 -pedantic -Wall
SOURCES=hg.cpp

all: hg

hg: $(SOURCES)
	$(PP) $(PFLAGS) $(SOURCES) -o hg

run: hg
	./hg graf.out

clean:
	rm -f hg *~
