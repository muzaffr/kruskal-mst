CC = g++
CFLAGS = -Warray-bounds -Wmisleading-indentation -Wformat=2 -Wmaybe-uninitialized -Wsign-compare -Wconversion -Wshift-overflow=2 -Wshadow -Wdangling-else -D_GLIBCXX_DEBUG -O2 -std=c++17
INCLUDE = -Ipriority_queue -Idsu -Imst -Iio
IO = io/io.o
DSU = dsu/dsu.o
MST = mst/mst.o

kruskal: io mst
	$(CC) $(CFLAGS) $(INCLUDE) $(IO) $(MST) $(DSU) src/kruskal.cpp -o bin/kruskal

mst: dsu io $(MST)

dsu: $(DSU)

io:	$(IO)

%.o: %.cpp
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

clean:
	@find . -iname *.o | xargs rm -rf
	@find . -iname __pycache__ | xargs rm -rf
	@rm -rf bin/*
