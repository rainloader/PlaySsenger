TARGET = pss_run
SRCS = $(shell ls *.cpp)
OBJS = $(SRCS:.cpp=.o) 

$(TARGET) : $(OBJS) 
	g++ -lm -std=c++0x -lpthread -o $@ $(OBJS)
	make clean

.cpp.o:
	g++ -c -std=c++0x -lpthread $(SRCS)


clean:
	rm $(OBJS) 

