all:
	mkdir -p bin
	g++ main.cpp -o ./bin/moostard --std=c++14

clean:
	rm -rf bin
