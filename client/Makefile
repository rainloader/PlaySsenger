TARGET = psc_run
SRCS = $(shell ls *.cpp)
OBJS = $(SRCS:.cpp=.o)
$(TARGET) : $(OBJS)
	g++ -lm -std=c++0x -o $@ $(OBJS) $(shell ls ../common/*.o) -lpthread

.cpp.o:
	g++ -c -std=c++0x $(SRCS) -lpthread

clean:
	rm $(OBJS) 
