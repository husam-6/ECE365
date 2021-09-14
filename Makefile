spell.exe: spellcheck.o hash.o
	g++ -o spell.exe spellcheck.o hash.o

spellcheck.o: spellCheck.cpp hash.h
	g++ -c -std=c++17 spellCheck.cpp

hash.o: hash.cpp hash.h
	g++ -c -std=c++17 hash.cpp

debug:
	g++ -g -o spellDebug.exe spellCheck.cpp hash.cpp

clean:
	rm -f *.exe *.o *.stackdump *~

backup:
	test -d backups || mkdir backups
	cp *.cpp backups
	cp *.h backups
	cp Makefile backups
