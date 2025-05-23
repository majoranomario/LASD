
cc = g++

cflags = -Wall -pedantic -O3 -std=c++20 -fsanitize=address

objects = main.o container.o myexc1a.o myexc1b.o mytest.o #test.o exc1as.o exc1af.o exc1bs.o exc1bf.o

libcon = container/container.hpp container/testable.hpp container/traversable.hpp container/traversable.cpp container/mappable.hpp container/mappable.cpp container/dictionary.hpp container/dictionary.cpp container/linear.hpp container/linear.cpp

libexc = $(libcon) zlasdtest/container/container.hpp zlasdtest/container/testable.hpp zlasdtest/container/traversable.hpp zlasdtest/container/mappable.hpp zlasdtest/container/dictionary.hpp zlasdtest/container/linear.hpp

#libexc = $(libcon) zmytest/container/container.hpp zmytest/container/testable.hpp zmytest/container/traversable.hpp zmytest/container/mappable.hpp zmytest/container/dictionary.hpp zmytest/container/linear.hpp

libexc1a = $(libexc) vector/vector.hpp vector/vector.cpp list/list.hpp list/list.cpp

libexc1b = $(libexc1a) set/set.hpp set/lst/setlst.hpp set/lst/setlst.cpp set/vec/setvec.hpp set/vec/setvec.cpp

main: $(objects)
	$(cc) $(cflags) $(objects) -g -o main

clean:
	clear; rm -rfv *.o; rm -fv main

main.o: main.cpp
	$(cc) $(cflags) -c main.cpp

#test.o: zlasdtest/test.cpp zlasdtest/test.hpp
#	$(cc) $(cflags) -c zlasdtest/test.cpp -o test.o

mytest.o: zmytest/test.cpp zmytest/test.hpp
	$(cc) $(cflags) -c zmytest/test.cpp -o mytest.o

container.o: $(libcon) zlasdtest/container/container.cpp zlasdtest/container/container.hpp
	$(cc) $(cflags) -c zlasdtest/container/container.cpp -o container.o

myexc1a.o: zmytest/exercise1a/exercise1a.cpp zmytest/exercise1a/test.hpp
	$(cc) $(cflags) -c zmytest/exercise1a/exercise1a.cpp -o myexc1a.o

myexc1b.o : zmytest/exercise1b/exercise1b.cpp zmytest/exercise1b/test.hpp
	$(cc) $(cflags) -c zmytest/exercise1b/exercise1b.cpp -o myexc1b.o

#exc1as.o: $(libexc1a) zlasdtest/exercise1a/simpletest.cpp
#	$(cc) $(cflags) -c zlasdtest/exercise1a/simpletest.cpp -o exc1as.o

#exc1af.o: $(libexc1a) zlasdtest/exercise1a/fulltest.cpp
#	$(cc) $(cflags) -c zlasdtest/exercise1a/fulltest.cpp -o exc1af.o

#exc1bs.o: $(libexc1b) zlasdtest/exercise1b/simpletest.cpp
#	$(cc) $(cflags) -c zlasdtest/exercise1b/simpletest.cpp -o exc1bs.o

#exc1bf.o: $(libexc1b) zlasdtest/exercise1b/fulltest.cpp
#	$(cc) $(cflags) -c zlasdtest/exercise1b/fulltest.cpp -o exc1bf.o
