STD = c++17
CC = g++

BINARY = main.exe

main.exe: main.cpp
	$(CC) -std=$(STD) -Wno-psabi -fPIC -o main.exe main.cpp

clean:
	rm -f *.exe *.o

remake: clean main.exe

count:
	find . -type f \( -name "*.cpp" -o -name "*.h" \) -exec wc -l {} +

.PHONY: clean count remake
