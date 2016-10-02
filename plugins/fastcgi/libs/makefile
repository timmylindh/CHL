COMPILER = gcc
LIB_NAME = libfcgi

all: install

# Compile object files to shared library
install: compile
	gcc -shared -o $(LIB_NAME).so *.o
	make clean

# Compile source files
compile:
	$(COMPILER) -c -w -Wall -Werror -fPIC src/*.c

# Clean up
clean:
	rm *.o
	
