test-c: *.c
	gcc *.c -o test-c.out -O3

test-debug-c: *c
	gcc *.c -o test-debug-c.out -g -O3

test-c++:
	g++ *.c -o test-c++.out -O3

test-debug-c++:
	g++ *.c -o test-debug-c++.out -g -O3

unsafe-test-c:
	gcc *.c -o unsafe-test-c.out -Ofast

unsafe-test-c++:
	g++ *.c -o unsafe-test-c++.out -Ofast

clean:
	rm -f *.out