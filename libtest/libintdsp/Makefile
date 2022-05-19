
all:
	$(CC) -c -I. -I_source _source/graph.c _source/nodes.c _source/init.c
	ar rcs libintdsp.a init.o graph.o nodes.o 

clean:
	rm -rf *.o *.a
