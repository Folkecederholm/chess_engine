TARGET = exec

$(TARGET): build/main.o build/test.a build/trace_board_state.o
	clang -o $@ build/main.o build/test.a build/trace_board_state.o

build/main.o: src/main.c
	clang -c src/main.c -o $@

build/test.a: src/test.rs
	rustc src/test.rs -o $@ --crate-type=staticlib -C panic=abort

build/trace_board_state.o: src/trace_board_state/trace_board_state.c
	clang -c src/trace_board_state/trace_board_state.c -o $@

clean:
	rm build/*

test: $(TARGET)
	./$(TARGET)

