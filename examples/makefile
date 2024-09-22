STD = c++17
CC = g++

SRCS = $(wildcard *.cpp)
BINS = $(patsubst %.cpp,%,$(SRCS))

all: $(BINS)

%: %.cpp
	$(CC) -std=$(STD) -fPIC -o $@ $<

clean:
	rm -f $(BINS) *.o

.PHONY: clean all
