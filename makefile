install: bin/
	g++ src/*.cpp -o bin/main.out

bin/:
	mkdir bin	
