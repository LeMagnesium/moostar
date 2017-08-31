all:
	mkdir -p bin
	mkdir -p objs
	g++ -c src/bfinterpretor.cpp -o ./objs/bfinterpretor.o --std=c++14
	g++ -c src/main.cpp -o ./objs/main.o --std=c++14
	g++ objs/main.o objs/bfinterpretor.o -o ./bin/moostard

clean:
	rm -rf bin objs
