default: examples

examples:
	make -C examples/

clean:
	rm -f *.exe *.o
	make clean -C examples

count:
	find . -type f \( -name "*.cpp" -o -name "*.h" \) -exec wc -l {} +

.PHONY: default examples clean count
