.PHONY: test

runtime:
	mkdir -p bin
	gcc-14 -Wall -std=c23 -g lib/leb128.c src/runtime.c -o bin/runtime

test:
	mkdir -p bin
	gcc-14 -Wall -std=c23 -g lib/leb128.c test/test.c -o bin/test
	./bin/test

run:
	./bin/runtime test/hello_world.wasm

clean:
	rm -rf bin
