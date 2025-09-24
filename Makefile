runtime:
	gcc-14 -Wall -std=c23 src/runtime.c -o bin/runtime

run:
	./runtime test/empty.wasm

clean:
	rm runtime
