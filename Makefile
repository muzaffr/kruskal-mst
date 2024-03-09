CC = g++
CFLAGS = -Warray-bounds -Wmisleading-indentation -Wformat=2 -Wmaybe-uninitialized -Wsign-compare -Wconversion -Wshift-overflow=2 -Wshadow -Wdangling-else -D_GLIBCXX_DEBUG -O2 -std=c++17
INCLUDE = -Ipriority_queue -Iio
IO = io/io.o

all: orig stl

orig: pq_orig sort_orig

stl: sort_stl_sort sort_stl_heap_sort pq_stl_pq pq_stl_set

pq: pq_orig pq_stl_pq pq_stl_set

sort: sort_orig sort_stl_sort sort_stl_heap_sort

pq_orig: io
	$(CC) $(CFLAGS) $(INCLUDE) $(IO) src/pq_orig.cpp -o bin/pq_orig

sort_orig: io
	$(CC) $(CFLAGS) $(INCLUDE) $(IO) src/sort_orig.cpp -o bin/sort_orig

pq_stl_pq: io
	$(CC) $(CFLAGS) $(INCLUDE) $(IO) src/pq_stl_pq.cpp -o bin/pq_stl_pq

pq_stl_set: io
	$(CC) $(CFLAGS) $(INCLUDE) $(IO) src/pq_stl_set.cpp -o bin/pq_stl_set

sort_stl_sort: io
	$(CC) $(CFLAGS) $(INCLUDE) $(IO) src/sort_stl_sort.cpp -o bin/sort_stl_sort

sort_stl_heap_sort: io
	$(CC) $(CFLAGS) $(INCLUDE) $(IO) src/sort_stl_heap_sort.cpp -o bin/sort_stl_heap_sort

# %_orig %_stl_%: io
# 	$(CC) $(CFLAGS) $(INCLUDE) $(IO) src/$@.cpp -o bin/$@

io:	$(IO)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@find . -iname *.o | xargs rm -rf
	@find . -iname __pycache__ | xargs rm -rf
	@rm -rf bin/*
