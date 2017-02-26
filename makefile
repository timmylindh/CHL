# STANDARD MAKEFILE FOR CHL
# https://github.com/it4e/CHL

install: move_files

# Put files in proper locations
move_files: create_lib
	mv libchl.so /usr/lib/chl/
	cp core/*.h /usr/include/chl
	# Move plugin dependent libraries and headers
	if [ "${PLUGINS}" != "FALSE" ]; then bash findplugindeps plugins; fi
	# Make CHL libs available
	ln -f -s /usr/lib/chl/* /usr/lib/
	

# Create library
create_lib: create_path compile_core
	gcc -shared -o libchl.so cmp/*.o
	make clean
	
# Handle compilation of core
compile_core: compile_plugins
	if [ "${TYPE}" != "FCGI" ]; then gcc -c -Wall -Werror -fPIC core/src/*.c; mv *.o cmp; else gcc -c -D '_F_CHL_' -Wall -Werror -fPIC core/src/*.c; mv *.o cmp; fi # Check whether to compile as fcgi or cgi


# Handle plugins compilation
compile_plugins:
	# Check whether to compile plugins or not
	if [ "${PLUGINS}" != "FALSE" ]; then bash pluginhandler plugins; fi

# Create path for compilation and library
create_path:
	# Check whether library paths already exists
	if ! [ -d "/usr/lib/chl" ]; then mkdir /usr/lib/chl; fi
	if ! [ -d "/usr/include/chl" ]; then mkdir /usr/include/chl; fi
	# Check whether compilation folder already exists
	if ! [ -d "cmp" ]; then mkdir cmp; fi

# Clean cmp
clean: 
	if [ -d "cmp" ]; then rm -r cmp; fi
