default: examples

clean:
	rm -f *.exe *.o
	make clean -C examples

count:
	find . -type f \( -name "*.cpp" -o -name "*.h" \) -exec wc -l {} +

examples:
	make -C examples/

.PHONY: clean count examples default
