libraries := graph
headers := graph/include
CPPFLAGS = -I $(headers)

.PHONY: clean $(libraries)

dfsa: dfsa.o $(libraries)
	gcc -o dfsa dfsa.o graph/graph.o graph/list.o $(CPPFLAGS)

dfsa.o: dfsa.c $(libraries)
	gcc -c dfsa.c $(CPPFLAGS)

dfsb: dfsb.o $(libraries)
	gcc -o dfsb dfsb.o graph/dgraph.o graph/list.o $(CPPFLAGS)

dfsb.o: dfsb.c $(libraries)
	gcc -c dfsb.c $(CPPFLAGS)

$(libraries):
	$(MAKE) --directory=$@ 

clean:
	rm -f *.out *.o
deepClean:
	rm -rf *.out *.o */*.out */*.o