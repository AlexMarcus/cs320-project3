all: project3
project3: Cache.h Cache.cpp Main.cpp
	g++ -std=c++11 Cache.cpp Main.cpp -o project3
clean:
	rm -f project3
