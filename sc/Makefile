CC := g++ -std=c++1z
MAIN := sc
OBJS := $(MAIN).o Token_stream.o
SRCS := $(MAIN).cpp Token_stream.cpp

all: $(MAIN)

$(MAIN).o: $(SRCS)
	$(CC) -c $(MAIN).cpp -o $(MAIN).o

$(MAIN): $(OBJS)
ifeq ($(OS),Windows_NT)
	$(CC) -o $(MAIN).exe $(OBJS)
else
	$(CC) -o $(MAIN) $(OBJS)
endif

Token_stream.o: Token_stream.cpp
	$(CC) -c Token_stream.cpp -o Token_stream.o

clean:
	rm -f $(MAIN) $(MAIN).exe $(OBJS)