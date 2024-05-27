run: main
	./out/main

main: out/main.o
	gcc -o out/main out/main.o

out/main.o: clean
	mkdir -p out
	gcc -c src/main.c -o out/main.o

clean:
	rm -f main out/main.o. out/main_d out/main_d.o

debug: out/main.o
	gcc -o out/main_d out/main.o -g


gdb: debug
	gdb ./out/main_d --eval-command="run"

.PHONY: clean debug run gdb