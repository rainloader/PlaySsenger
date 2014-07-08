TARGET = pss_run
SRCS = $(shell ls *.cpp)
OBJS = $(SRCS:.cpp=.o) ## Main.o PlaySsengerCore.o NetworkManager.o

$(TARGET) : $(OBJS) 
	g++ -lm -o $@ $(OBJS)
	make clean

.cpp.o:
	g++ -c -std=gnu++0x $(SRCS)



Main.o : Main.cpp

PlaySsengerCore.o : PlaySsengerCore.cpp

NetworkManager.o : NetworkManager.cpp

Session.o : Session.cpp

clean:
	rm $(OBJS) 

