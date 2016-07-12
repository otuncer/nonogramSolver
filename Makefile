binname := nonogramSolver

CXX=g++
CXXFLAGS=-O3 -std=c++11

SRCS=Board.cpp CellState.cpp Fail.cpp InputReader.cpp Line.cpp LineQueue.cpp \
     main.cpp NonogramSolver.cpp
OBJS=$(patsubst %.cpp, %.o, $(SRCS))

all: $(binname)

$(binname): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(binname) $(OBJS)

depend: .depend

.depend: $(SRCS)
	rm -f ./.depend
	$(CXX) $(CXXFLAGS) -MM $^>>./.depend;

clean:
	rm -f $(OBJS)

dist-clean: clean
	rm -f *~ .depend $(binname)

include .depend
