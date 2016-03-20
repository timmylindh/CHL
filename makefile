# Which compiler to use
COMPILER = gcc

# Path to core source files
CORE_SRC_PATH = core/src

# Main path
MAINPATH = chl

# Path to where to put libraries
LIBPATH = /usr/lib/$(MAINPATH)

# Path to where to put header files
HEADERPATH = /usr/include/$(MAINPATH)

# Core library name
CORE_LIB_NAME = libchl

# Core header path
CORE_HEADER_PATH = core/chl

all: lib

# Move lib and header files to proper location
install: lib
	if ! [ -d "$(LIBPATH)" ]; then mkdir $(LIBPATH); fi
	if ! [ -d "$(HEADERPATH)" ]; then mkdir $(HEADERPATH); fi
	cp $(CORE_LIB_NAME).a $(LIBPATH)/
	cp $(CORE_HEADER_PATH).h $(HEADERPATH)/

# Create static library
lib:
	$(COMPILER) -c $(CORE_SRC_PATH)/*.c
	ar rcs $(CORE_LIB_NAME).a *.o
	make clean

# Clean up
clean:
	rm *.o

