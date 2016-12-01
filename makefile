all: project3
project3: source/Cache.h source/Cache.cpp source/Main.cpp
	g++ -std=c++11 source/Cache.cpp source/Main.cpp -o project3
clean:
	rm -f project3
