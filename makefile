
ipforward: iprouter.o ipforward.cpp
	c++ -Wall -std=c++11 -o ipforward ipforward.cpp iprouter.o

iprouter.o: iprouter.cpp
	g++ -c -Wall -std=c++11 -o iprouter.o iprouter.cpp

debug: iprouter.cpp ipforward.cpp
	g++ -g -Wall -std=c++11 -o debug *.cpp

clean: 
	rm -rf *.o ipforward debug
