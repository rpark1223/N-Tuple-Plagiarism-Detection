CXX      = clang++
CXXFLAGS = -g3 -Wall -Wextra -std=c++11 -O2
LDFLAGS  = -g3

all: plag_det

plag_det: main.o Detector.o HashTable.o
	${CXX} ${LDFLAGS} -o plag_det main.o Detector.o HashTable.o

main.o: main.cpp
Detector.o: Detector.h Detector.cpp
HashTable.o: HashTable.h HashTable.cpp

clean:
	rm -rf plag_det *.o *.dSYM