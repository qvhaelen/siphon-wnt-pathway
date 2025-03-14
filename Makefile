CC=g++
CFLAGS= -c  -O3
LDFLAGS= 

objects := $(patsubst %.cc,%.o,$(wildcard *.cc))


all: siphon_persistence

siphon_persistence: $(objects)
	$(CC)  -o siphon_persistence $(objects)

%.o: %.cc
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm *.o 
