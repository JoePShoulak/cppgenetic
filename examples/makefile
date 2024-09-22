STD = c++17
CC = g++

wordsearch: wordsearch.cpp
	$(CC) -std=$(STD) -Wno-psabi -fPIC -o wordsearch.exe wordsearch.cpp

clean:
	rm -f *.exe *.o

.PHONY: clean
