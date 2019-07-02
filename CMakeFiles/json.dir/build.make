# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.14

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /tmp/pdns

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /tmp/pdns

# Utility rule file for json.

# Include the progress variables for this target.
include CMakeFiles/json.dir/progress.make

CMakeFiles/json: CMakeFiles/json-complete


CMakeFiles/json-complete: json-prefix/src/json-stamp/json-install
CMakeFiles/json-complete: json-prefix/src/json-stamp/json-mkdir
CMakeFiles/json-complete: json-prefix/src/json-stamp/json-download
CMakeFiles/json-complete: json-prefix/src/json-stamp/json-update
CMakeFiles/json-complete: json-prefix/src/json-stamp/json-patch
CMakeFiles/json-complete: json-prefix/src/json-stamp/json-configure
CMakeFiles/json-complete: json-prefix/src/json-stamp/json-build
CMakeFiles/json-complete: json-prefix/src/json-stamp/json-install
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/tmp/pdns/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Completed 'json'"
	/usr/local/bin/cmake -E make_directory /tmp/pdns/CMakeFiles
	/usr/local/bin/cmake -E touch /tmp/pdns/CMakeFiles/json-complete
	/usr/local/bin/cmake -E touch /tmp/pdns/json-prefix/src/json-stamp/json-done

json-prefix/src/json-stamp/json-install: json-prefix/src/json-stamp/json-build
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/tmp/pdns/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Performing install step for 'json'"
	cd /tmp/pdns/json-build && $(MAKE) install
	cd /tmp/pdns/json-build && /usr/local/bin/cmake -E touch /tmp/pdns/json-prefix/src/json-stamp/json-install

json-prefix/src/json-stamp/json-mkdir:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/tmp/pdns/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Creating directories for 'json'"
	/usr/local/bin/cmake -E make_directory /tmp/pdns/json-src
	/usr/local/bin/cmake -E make_directory /tmp/pdns/json-build
	/usr/local/bin/cmake -E make_directory /tmp/pdns/json-prefix
	/usr/local/bin/cmake -E make_directory /tmp/pdns/json-prefix/tmp
	/usr/local/bin/cmake -E make_directory /tmp/pdns/json-prefix/src/json-stamp
	/usr/local/bin/cmake -E make_directory /tmp/pdns/json-prefix/src
	/usr/local/bin/cmake -E make_directory /tmp/pdns/json-prefix/src/json-stamp
	/usr/local/bin/cmake -E touch /tmp/pdns/json-prefix/src/json-stamp/json-mkdir

json-prefix/src/json-stamp/json-download: json-prefix/src/json-stamp/json-gitinfo.txt
json-prefix/src/json-stamp/json-download: json-prefix/src/json-stamp/json-mkdir
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/tmp/pdns/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Performing download step (git clone) for 'json'"
	/usr/local/bin/cmake -P /tmp/pdns/json-prefix/tmp/json-gitclone.cmake
	/usr/local/bin/cmake -E touch /tmp/pdns/json-prefix/src/json-stamp/json-download

json-prefix/src/json-stamp/json-update: json-prefix/src/json-stamp/json-download
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/tmp/pdns/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Performing update step for 'json'"
	cd /tmp/pdns/json-src && /usr/local/bin/cmake -P /tmp/pdns/json-prefix/tmp/json-gitupdate.cmake

json-prefix/src/json-stamp/json-patch: json-prefix/src/json-stamp/json-download
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/tmp/pdns/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "No patch step for 'json'"
	/usr/local/bin/cmake -E echo_append
	/usr/local/bin/cmake -E touch /tmp/pdns/json-prefix/src/json-stamp/json-patch

json-prefix/src/json-stamp/json-configure: json-prefix/tmp/json-cfgcmd.txt
json-prefix/src/json-stamp/json-configure: json-prefix/src/json-stamp/json-update
json-prefix/src/json-stamp/json-configure: json-prefix/src/json-stamp/json-patch
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/tmp/pdns/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Performing configure step for 'json'"
	cd /tmp/pdns/json-build && /usr/local/bin/cmake "-GUnix Makefiles" /tmp/pdns/json-src
	cd /tmp/pdns/json-build && /usr/local/bin/cmake -E touch /tmp/pdns/json-prefix/src/json-stamp/json-configure

json-prefix/src/json-stamp/json-build: json-prefix/src/json-stamp/json-configure
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/tmp/pdns/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Performing build step for 'json'"
	cd /tmp/pdns/json-build && $(MAKE)
	cd /tmp/pdns/json-build && /usr/local/bin/cmake -E touch /tmp/pdns/json-prefix/src/json-stamp/json-build

json: CMakeFiles/json
json: CMakeFiles/json-complete
json: json-prefix/src/json-stamp/json-install
json: json-prefix/src/json-stamp/json-mkdir
json: json-prefix/src/json-stamp/json-download
json: json-prefix/src/json-stamp/json-update
json: json-prefix/src/json-stamp/json-patch
json: json-prefix/src/json-stamp/json-configure
json: json-prefix/src/json-stamp/json-build
json: CMakeFiles/json.dir/build.make

.PHONY : json

# Rule to build all files generated by this target.
CMakeFiles/json.dir/build: json

.PHONY : CMakeFiles/json.dir/build

CMakeFiles/json.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/json.dir/cmake_clean.cmake
.PHONY : CMakeFiles/json.dir/clean

CMakeFiles/json.dir/depend:
	cd /tmp/pdns && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /tmp/pdns /tmp/pdns /tmp/pdns /tmp/pdns /tmp/pdns/CMakeFiles/json.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/json.dir/depend

