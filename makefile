# Which compiler to use
COMPILER = gcc

# Path to core
PATH_CORE = core

# Path to plugins
PATH_PLUGINS = plugins

# Path to plugins src
PATH_PLUGINS_SRC = $(PATH_PLUGINS)/*/src/*.c

# Path to plugins libs
PATH_PLUGINS_LIBS = $(PATH_PLUGINS)/*/libs/*

# Path to core source files
PATH_SRC_CORE = $(PATH_CORE)/src

# Name of CHL library
NAME_MAIN_LIB = libchl

# Name of CHL directories
NAME_CHL_DIR = chl

# Path to default location for libraries and headers
LIBSPATH = /usr/lib/$(NAME_CHL_DIR)
HEADERSPATH = /usr/include/$(NAME_CHL_DIR)

# Default, compile to object files
all: compile

# Move lib and header files to proper locations
install: lib
	if ! [ -d "$(LIBSPATH)" ]; then mkdir $(LIBSPATH); fi
	if ! [ -d "$(HEADERSPATH)" ]; then mkdir $(HEADERSPATH); fi
	cp $(NAME_MAIN_LIB).a $(LIBSPATH)/
	cp $(wildcard $(PATH_PLUGINS_LIBS)) $(LIBSPATH)/ 2>/dev/null || :
	cp $(PATH_CORE)/*.h $(HEADERSPATH)/
	cp $(wildcard $(PATH_PLUGINS)/*/*.h) $(HEADERSPATH)/ 2>/dev/null || :
	rm $(NAME_MAIN_LIB).a

# Create static library
lib: compile	
	ar rcs $(NAME_MAIN_LIB).a *.o
	make clean

# Compile source files to object files
compile:
	$(COMPILER) -c $(PATH_SRC_CORE)/*.c $(wildcard $(PATH_PLUGINS_SRC))	

# Clean up
clean:
	rm *.o

