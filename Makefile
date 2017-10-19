#David SAmuel, makefile

CXX=clang++ $(CXXFLAGS)
CXXFLAGS= -Wall -g
OFILES = hashTable.o wordPuzzle.o timer.o

.SUFFIXES: .o .cpp

a.out: $(OFILES)
	$(CXX) $(OFILES)

clean:
	-rm -f *.o *~
hashTable.o: hashTable.h hashTable.cpp
timer.o: timer.cpp timer.h
wordPuzzle.o: wordPuzzle.cpp hashTable.h timer.h


