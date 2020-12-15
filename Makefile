test-c: point_search.c point_alg.c test.c
	gcc point_search.c point_alg.c test.c -o test-c.out -O3

test-debug-c: point_search.c point_alg.c test.c
	gcc point_search.c point_alg.c test.c -o test-debug-c.out -g -O3

test-c++: point_search.c point_alg.c test.c
	g++ point_search.c point_alg.c test.c -o test-c++.out -O3

test-debug-c++: point_search.c point_alg.c test.c
	g++ point_search.c point_alg.c test.c -o test-debug-c++.out -g -O3

unsafe-test-c: point_search.c point_alg.c test.c
	gcc point_search.c point_alg.c test.c -o unsafe-test-c.out -Ofast

unsafe-test-c++: point_search.c point_alg.c test.c
	g++ point_search.c point_alg.c test.c -o unsafe-test-c++.out -Ofast

dll-c: point_search.c point_alg.c dllmain.c
	gcc -c -DBUILDING_EXAMPLE_DLL dllmain.c point_search.c point_alg.c -Ofast -mtune=native
	gcc -shared -o solution.dll dllmain.o point_search.o point_alg.o -Wl,--out-implib,solution.a -Ofast -mtune=native

dll-c++: point_search.c point_alg.c
	g++ -c -DBUILDING_EXAMPLE_DLL dllmain.c point_search.c point_alg.c -Ofast -mtune=native
	g++ -shared -o solution.dll dllmain.o point_search.o point_alg.o -Wl,--out-implib,solution.a -Ofast -mtune=native

clean:
	rm -f *.out
	rm -f *.o
	rm -f *.a
	rm -f *.dll