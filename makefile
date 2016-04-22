CXX=g++
CXXFLAGS=-Wall -std=c++11

SRC=iprouter.cpp datagram.cpp ipforward.cpp table.cpp
OBJS=$(subst .cpp,.o,$(SRC))

ipforward: $(OBJS)
	$(CXX) $(CXXFLAGS) -o ipforward $(OBJS)

%.o: %.cpp %.h
	$(CXX) -c $(CXXFLAGS) $< -o $@

debug: $(SRC)
	$(CXX) -g $(CXXFLAGS) -o debug $(SRC)

clean: 
	rm -rf $(OBJS) ipforward debug
