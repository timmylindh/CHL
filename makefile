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
	mv $(NAME_MAIN_LIB).$(EXTENSION) $(LIBSPATH)/
	cp $(wildcard $(PATH_PLUGINS_LIBS).so) $(LIBSPATH)/ 2>/dev/null || :
	cp $(PATH_CORE)/*.h $(HEADERSPATH)/
	cp $(wildcard $(PATH_PLUGINS)/*/*.h) $(HEADERSPATH)/ 2>/dev/null || :
	ln -f -s $(LIBSPATH)/* /usr/lib/

# Create main and plugin shared libraries
lib: compile
	# Create main shared library	
	gcc -shared -o $(NAME_MAIN_LIB).so *.o
	make clean

	# Create plugin libraries
	bash createlibs $(PATH_PLUGINS)	

# Compile source files to position independent object files
compile:
	# Check whether to compile for FastCGI or CGI 
	if [ "${TYPE}" != "FCGI" ]; then $(COMPILER) -c -Wall -Werror -fPIC $(PATH_SRC_CORE)/*.c $(wildcard $(PATH_PLUGINS_SRC)); else $(COMPILER) -c -D '_F_CHL_' -Wall -Werror -fPIC $(PATH_SRC_CORE)/*.c $(wildcard $(PATH_PLUGINS_SRC)); fi	
	$(eval EXTENSION = so)

# Clean up
clean:
	rm *.o

