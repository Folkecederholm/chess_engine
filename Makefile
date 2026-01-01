CC = clang
TARGET = exec

$(TARGET): build/main.o build/test.a build/trace_board_state.a build/best_move.o build/repl.o
	$(CC) -o $@ $^

build/main.o: src/main.c
	$(CC) -c src/main.c -o $@

build/test.a: src/find_moves/pub.rs src/find_moves/*
	rustc $< -o $@ --crate-type=staticlib -C panic=abort

build/trace_board_state.a: build/trace_board_state_pub.o build/trace_board_state_boil.o
	#$(CC) -c build/trace_board_state_pub.o build/trace_board_state_boil.o -o $@
	ar rcs $@ $^

build/trace_board_state_pub.o: src/trace_board_state/pub.c
	$(CC) -c src/trace_board_state/pub.c -o $@
build/trace_board_state_boil.o: src/trace_board_state/boil.c
	$(CC) -c src/trace_board_state/boil.c -o $@

build/best_move.o: src/best_move/best_move.c
	$(CC) -c $< -o $@

build/repl.o: src/repl/repl.c
	$(CC) -c $< -o $@

clean:
	rm build/* -f

test: $(TARGET)
	./$(TARGET)

recompile:
	make clean
	make
