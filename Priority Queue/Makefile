useHeap.exe: useHeap.o heap.o hash.o
	g++ -o useHeap.exe useHeap.o heap.o hash.o

useHeap.o: useHeap.cpp
	g++ -c -std=c++17 useHeap.cpp

heap.o: heap.cpp heap.h
	g++ -c -std=c++17 heap.cpp

hash.o: hash.cpp hash.h
	g++ -c -std=c++17 hash.cpp

debug:
	g++ -g -std=c++17 -o useHeapDebug.exe useHeap.cpp heap.cpp hash.cpp

clean:
	rm -f *.exe *.o *.stackdump *~

backup:
	test -d backups || mkdir backups
	cp *.cpp backups
	cp *.h backups
	cp Makefile backups