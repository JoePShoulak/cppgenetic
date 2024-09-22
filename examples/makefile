STD = c++17
CC = g++

BINARY = main.exe

wordsearch: wordsearch.cpp
	$(CC) -std=$(STD) -Wno-psabi -fPIC -o wordsearch.exe wordsearch.cpp

clean:
	rm -f *.exe *.o

remake: clean main.exe

count:
	find . -type f \( -name "*.cpp" -o -name "*.h" \) -exec wc -l {} +

.PHONY: clean count remake
