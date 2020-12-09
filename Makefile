test: *.c
	g++ *.c -o test

test_debug: *c
	g++ *.c -o test_debug -g