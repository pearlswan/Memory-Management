bench : mem.h mem_impl.h bench.c freemem.o getmem.o print_heap.o check_heap.o get_mem_stats.o
	gcc -Wall -std=c11 -o bench mem.h mem_impl.h bench.c freemem.o getmem.o print_heap.o check_heap.o get_mem_stats.o

getmem.o : mem.h mem_impl.h getmem.c
	gcc -Wall -std=c11 -g -c mem.h mem_impl.h getmem.c

freemem.o : mem.h mem_impl.h freemem.c
	gcc -Wall -std=c11 -g -c mem.h mem_impl.h freemem.c

print_heap.o : mem_impl.h print_heap.c
	gcc -Wall -std=c11 -g -c mem_impl.h print_heap.c

check_heap.o : mem_impl.h check_heap.c
	gcc -Wall -std=c11 -g -c mem_impl.h check_heap.c

get_mem_stats.o : mem_impl.h get_mem_stats.c
	gcc -Wall -std=c11 -g -c mem_impl.h get_mem_stats.c

clean :
	rm -f bench getmem.o freemem.o print_heap.o check_heap.o get_mem_stats.o mem_impl.h.gch mem.h.gch

test :
	./bench

dist :
	tar -cvf hw5.tar bench.c check_heap.c freemem.c getmem.c get_mem_stats.c Makefile mem.h mem_impl.h print_heap.c README.md 
