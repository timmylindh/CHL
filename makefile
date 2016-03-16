# Which compiler to use
COMPILER = gcc

# Path to source files
SRC_PATH = core

# Main path
MAINPATH = chl

# Path to where to put library
LIBPATH = /usr/lib/$(MAINPATH)

# Path to where to put header file
HEADERPATH = /usr/include/$(MAINPATH)

# Library name
LIBNAME = libchl

# Header name
HEADERNAME = chl

all: lib

# Move lib and header files to proper location
install: lib
	if ! [ -d "$(LIBPATH)" ]; then mkdir $(LIBPATH); fi
	if ! [ -d "$(HEADERPATH)" ]; then mkdir $(HEADERPATH); fi
	cp $(LIBNAME).a $(LIBPATH)/
	cp $(HEADERNAME).h $(HEADERPATH)/

# Create static library
lib:
	$(COMPILER) -c $(SRC_PATH)/*.c
	ar rcs $(LIBNAME).a *.o
	make clean

# Clean up
clean:
	rm *.o

