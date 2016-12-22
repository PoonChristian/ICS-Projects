CC=gcc
CFLAGS=-c
CXXFLAGS=-ggdb
OBJECTS=my_ls.o main.o

my_ls: my_ls.o main.o	
	$(CC) $(CXXFLAGS) $(OBJECTS) -o my_ls
my_ls.o: my_ls.c my_ls.h
	$(CC) $(CXXFLAGS) $(CFLAGS) my_ls.c
main.o: main.c my_ls.h
	$(CC) $(CXXFLAGS) $(CFLAGS) main.c
clean:
	rm -rf $(OBJECTS) my_ls
