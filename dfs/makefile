libraries := graph
headers := graph/include
CPPFLAGS = -I $(headers)

.PHONY: clean $(libraries) components.o dfsacat.o dfsbcat.o

dfsa: dfsa.o $(libraries)
	gcc -o dfsa dfsa.o graph/graph.o graph/list.o $(CPPFLAGS)

dfsa.o: dfsa.c $(libraries)
	gcc -c dfsa.c $(CPPFLAGS)

dfsb: dfsb.o $(libraries)
	gcc -o dfsb dfsb.o graph/dgraph.o graph/list.o $(CPPFLAGS)

dfsb.o: dfsb.c $(libraries)
	gcc -c dfsb.c $(CPPFLAGS)

components: components.o $(libraries)
	gcc -o components components.o graph/graph.o graph/list.o $(CPPFLAGS)

components.o:
	gcc -c components.c $(CPPFLAGS)

dfsacat: dfsacat.o $(libraries)
	gcc -o dfsacat dfsacat.o graph/graph.o graph/list.o $(CPPFLAGS)

dfsacat.o:
	gcc -c dfsacat.c $(CPPFLAGS)

dfsbcat: dfsbcat.o $(libraries)
	gcc -o dfsbcat dfsbcat.o graph/dgraph.o graph/list.o $(CPPFLAGS)

dfsbcat.o:
	gcc -c dfsbcat.c $(CPPFLAGS)

$(libraries):
	$(MAKE) --directory=$@ 

clean:
	rm -f *.out *.o
deepClean:
	rm -rf *.out *.o */*.out */*.o