# In order to execute this "makefile" just type "make"

OBJS 	= mainSample.o SkipFunctions.o HashFunctions.o ListsFunctions.o ListNodeFunctions.o
SOURCE	= mainSample.cpp SkipFunctions.cpp HashFunctions.cpp ListsFunctions.cpp ListNodeFunctions.cpp
HEADER  = HashTable.h SkipList.h Node.h Record.h HashList.h ListNode.h GeneralList.h Declars.h
OUT  	= stucs
CC	= g++
FLAGS   = -g -c 

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT)

# create/compile the individual files
mainSample.o: mainSample.cpp
	$(CC) $(FLAGS) mainSample.cpp

SkipFunctions.o: SkipFunctions.cpp
	$(CC) $(FLAGS) SkipFunctions.cpp

HashFunctions.o: HashFunctions.cpp
	$(CC) $(FLAGS) HashFunctions.cpp

ListsFunctions.o: ListsFunctions.cpp
	$(CC) $(FLAGS) ListsFunctions.cpp

ListNodeFunctions.o: ListNodeFunctions.cpp
	$(CC) $(FLAGS) ListNodeFunctions.cpp	

# clean 
clean:
	rm -f $(OBJS) $(OUT)

#accounting
count:
	wc $(SOURCE) $(HEADER)