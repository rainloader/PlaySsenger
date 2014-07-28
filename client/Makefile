TARGET = psc_run
SRCS = $(shell ls *.cpp)
OBJS = $(SRCS:.cpp=.o)
$(TARGET) : $(OBJS)
	g++ -lm -std=c++0x -o $@ $(OBJS) $(shell ls ../common/*.o)

.cpp.o:
	g++ -c -std=c++0x $(SRCS)

clean:
	rm $(OBJS) 
