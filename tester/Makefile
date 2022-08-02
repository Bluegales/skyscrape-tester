rush_files = $(wildcard ../ex00/*.c)

test: captured_rush
	g++ rush_tester.cc *.o -O3
	rm *.o

captured_rush: $(rush_files) rush_capture.c
	gcc -D main=captured_main $^ -c -O3

clean:
	rm *.o
