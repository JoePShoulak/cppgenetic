STD = c++17
CC = g++

BINARY = main.exe

main.exe: main.cpp
	g++ -std=c++17 -Wno-psabi -fPIC -o main.exe main.cpp

clean:
	rm -f *.exe *.o

remake: clean make

count:
	find . -type f \( -name "*.cpp" -o -name "*.h" \) ! -path "./ext/*" ! -path "./tests/*" ! -name pugixml.cpp -exec wc -l {} +

# tests: $(BINARY)
# 	$(MAKE) -C tests/
# 	./tests/bin/run_tests.exe

.PHONY: clean count remake
