TARGET = pss_run
SRCS = $(shell ls *.cpp)
OBJS = $(SRCS:.cpp=.o) ## Main.o PlaySsengerCore.o NetworkManager.o Session.o

$(TARGET) : $(OBJS) 
	g++ -lm -lpthread -o $@ $(OBJS)
	make clean

.cpp.o:
	g++ -c -std=gnu++0x -lpthread $(SRCS)


clean:
	rm $(OBJS) 

