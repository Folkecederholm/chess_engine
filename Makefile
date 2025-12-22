TARGET = exec

$(TARGET): build/main.o build/test.a build/trace_board_state.a
	clang -o $@ build/main.o build/test.a build/trace_board_state.a

build/main.o: src/main.c
	clang -c src/main.c -o $@

build/test.a: src/test.rs
	rustc src/test.rs -o $@ --crate-type=staticlib -C panic=abort

build/trace_board_state.a: build/trace_board_state_pub.o build/trace_board_state_boil.o
	#clang -c build/trace_board_state_pub.o build/trace_board_state_boil.o -o $@
	ar rcs $@ $^

build/trace_board_state_pub.o: src/trace_board_state/pub.c
	clang -c src/trace_board_state/pub.c -o $@
build/trace_board_state_boil.o: src/trace_board_state/boil.c
	clang -c src/trace_board_state/boil.c -o $@

clean:
	rm build/*

test: $(TARGET)
	./$(TARGET)

