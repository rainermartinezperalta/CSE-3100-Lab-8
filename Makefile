CC=cc
CFLAGS=-g

all: dltest hmtest

dltest: dllist.o dltest.o
	$(CC) $(CLFAGS) -o $@  $^

hmtest: dllist.o hashMap.o hmtest.o
	$(CC) $(CLFAGS) -o $@  $^ -pthread

dllist.o : dllist.c dllist.h
	$(CC) $(CFLAGS) -c $<

hashMap.o : hashMap.c  hashMap.h dllist.h
	$(CC) $(CFLAGS) -c $< -pthread

hmtest.o : hmtest.c hashMap.h dllist.h
	$(CC) $(CFLAGS) -c $^ -pthread

dltest.o : dltest.c dllist.h
	$(CC) $(CFLAGS) -c $<

clean:
	rm -rf *.o dltest hmtest *.gch
