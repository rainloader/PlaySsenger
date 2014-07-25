SRCS = $(shell ls *.cpp)
OBJS = $(SRCS:.cpp=.o)

TARGET:
	g++ -c -std=c++0x -lpthread $(SRCS)

clean:
	rm $(OBJS)
