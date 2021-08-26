CXX		=g++
SRCS		=$(wildcard *.cpp) $(wildcard *.c)
OBJS		=$(SRCS:.cpp=.o)
TARGET		=out
LIBS		=-lprint
LIB_DIRS	=-L./lib
INC		=-I./include

all:$(TARGET) 
#	$(CXX) -o $(TARGET) $(OBJS) $(INC) $(LIB_DIRS) $(LIBS)
	$(CXX) -o $(TARGET) $(OBJS) $(INC) $(LIB_DIRS)
#	$(CXX) -o $(TARGET) $(OBJS) $(INC)

$(TARGET):$(SRCS) 
#	$(CXX) -c $(SRCS) $(INC) $(LIB_DIRS) $(LIBS)
	$(CXX) -c $(SRCS) $(INC) $(LIB_DIRS)
#	$(CXX) -c $(SRCS) $(INC)

clean:
	rm -f $(TARGET)
	rm -f *.o
