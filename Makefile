# define some Makefile variables for the compiler and compiler flags
# to use Makefile variables later in the Makefile: $()
#
#  -g    adds debugging information to the executable file
#  -Wall turns on most, but not all, compiler warnings
#
# for C++ define  CC = g++
CC = gcc
CFLAGS  = -g -Wall

# typing 'make' will invoke the first target entry in the file 
# (in this case the default target entry)
# you can name this target entry anything, but "default" or "all"
# are the most commonly used names by convention
#
default: huffmanTree.out 

# To create the executable file count we need the object files
#
huffmanTree.out:  huffmanTree.o hashMap.o huffmanNode.o minHeap.o 
	$(CC) $(CFLAGS) -o huffmanTree.out huffmanTree.o hashMap.o huffmanNode.o minHeap.o

huffmanTree.o:  huffmanTree.c hashMap.h huffmanNode.h minHeap.h 
	$(CC) $(CFLAGS) -c huffmanTree.c

hashMap.o:  hashMap.c hashMap.h 
	$(CC) $(CFLAGS) -c hashMap.c

huffmanNode.o:  huffmanNode.c huffmanNode.h 
	$(CC) $(CFLAGS) -c huffmanNode.c

minHeap.o: minHeap.c minHeap.h
	$(CC) $(CFLAGS) -c minHeap.c

# To start over from scratch, type 'make clean'.  This
# removes the executable file, as well as old .o object
# files and *~ backup files:
#
clean: 
	$(RM) huffmanTree *.o *~ *.out
