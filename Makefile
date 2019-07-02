# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.14

# Default target executed when no arguments are given to make.
default_target: all

.PHONY : default_target

# Allow only one "make -f Makefile2" at a time, but pass parallelism.
.NOTPARALLEL:


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

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/usr/local/bin/cmake -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache

.PHONY : rebuild_cache/fast

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "No interactive CMake dialog available..."
	/usr/local/bin/cmake -E echo No\ interactive\ CMake\ dialog\ available.
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache

.PHONY : edit_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /tmp/pdns/CMakeFiles /tmp/pdns/CMakeFiles/progress.marks
	$(MAKE) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /tmp/pdns/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean

.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named json-install

# Build rule for target.
json-install: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 json-install
.PHONY : json-install

# fast build rule for target.
json-install/fast:
	$(MAKE) -f CMakeFiles/json-install.dir/build.make CMakeFiles/json-install.dir/build
.PHONY : json-install/fast

#=============================================================================
# Target rules for targets named libtins-build

# Build rule for target.
libtins-build: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 libtins-build
.PHONY : libtins-build

# fast build rule for target.
libtins-build/fast:
	$(MAKE) -f CMakeFiles/libtins-build.dir/build.make CMakeFiles/libtins-build.dir/build
.PHONY : libtins-build/fast

#=============================================================================
# Target rules for targets named boost

# Build rule for target.
boost: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 boost
.PHONY : boost

# fast build rule for target.
boost/fast:
	$(MAKE) -f CMakeFiles/boost.dir/build.make CMakeFiles/boost.dir/build
.PHONY : boost/fast

#=============================================================================
# Target rules for targets named libtins-install

# Build rule for target.
libtins-install: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 libtins-install
.PHONY : libtins-install

# fast build rule for target.
libtins-install/fast:
	$(MAKE) -f CMakeFiles/libtins-install.dir/build.make CMakeFiles/libtins-install.dir/build
.PHONY : libtins-install/fast

#=============================================================================
# Target rules for targets named passivedns

# Build rule for target.
passivedns: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 passivedns
.PHONY : passivedns

# fast build rule for target.
passivedns/fast:
	$(MAKE) -f CMakeFiles/passivedns.dir/build.make CMakeFiles/passivedns.dir/build
.PHONY : passivedns/fast

#=============================================================================
# Target rules for targets named boost-build

# Build rule for target.
boost-build: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 boost-build
.PHONY : boost-build

# fast build rule for target.
boost-build/fast:
	$(MAKE) -f CMakeFiles/boost-build.dir/build.make CMakeFiles/boost-build.dir/build
.PHONY : boost-build/fast

#=============================================================================
# Target rules for targets named libtins

# Build rule for target.
libtins: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 libtins
.PHONY : libtins

# fast build rule for target.
libtins/fast:
	$(MAKE) -f CMakeFiles/libtins.dir/build.make CMakeFiles/libtins.dir/build
.PHONY : libtins/fast

#=============================================================================
# Target rules for targets named boost-install

# Build rule for target.
boost-install: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 boost-install
.PHONY : boost-install

# fast build rule for target.
boost-install/fast:
	$(MAKE) -f CMakeFiles/boost-install.dir/build.make CMakeFiles/boost-install.dir/build
.PHONY : boost-install/fast

#=============================================================================
# Target rules for targets named json

# Build rule for target.
json: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 json
.PHONY : json

# fast build rule for target.
json/fast:
	$(MAKE) -f CMakeFiles/json.dir/build.make CMakeFiles/json.dir/build
.PHONY : json/fast

#=============================================================================
# Target rules for targets named json-build

# Build rule for target.
json-build: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 json-build
.PHONY : json-build

# fast build rule for target.
json-build/fast:
	$(MAKE) -f CMakeFiles/json-build.dir/build.make CMakeFiles/json-build.dir/build
.PHONY : json-build/fast

KafkaConnector.o: KafkaConnector.cpp.o

.PHONY : KafkaConnector.o

# target to build an object file
KafkaConnector.cpp.o:
	$(MAKE) -f CMakeFiles/passivedns.dir/build.make CMakeFiles/passivedns.dir/KafkaConnector.cpp.o
.PHONY : KafkaConnector.cpp.o

KafkaConnector.i: KafkaConnector.cpp.i

.PHONY : KafkaConnector.i

# target to preprocess a source file
KafkaConnector.cpp.i:
	$(MAKE) -f CMakeFiles/passivedns.dir/build.make CMakeFiles/passivedns.dir/KafkaConnector.cpp.i
.PHONY : KafkaConnector.cpp.i

KafkaConnector.s: KafkaConnector.cpp.s

.PHONY : KafkaConnector.s

# target to generate assembly for a file
KafkaConnector.cpp.s:
	$(MAKE) -f CMakeFiles/passivedns.dir/build.make CMakeFiles/passivedns.dir/KafkaConnector.cpp.s
.PHONY : KafkaConnector.cpp.s

PeriodicListPrunning.o: PeriodicListPrunning.cpp.o

.PHONY : PeriodicListPrunning.o

# target to build an object file
PeriodicListPrunning.cpp.o:
	$(MAKE) -f CMakeFiles/passivedns.dir/build.make CMakeFiles/passivedns.dir/PeriodicListPrunning.cpp.o
.PHONY : PeriodicListPrunning.cpp.o

PeriodicListPrunning.i: PeriodicListPrunning.cpp.i

.PHONY : PeriodicListPrunning.i

# target to preprocess a source file
PeriodicListPrunning.cpp.i:
	$(MAKE) -f CMakeFiles/passivedns.dir/build.make CMakeFiles/passivedns.dir/PeriodicListPrunning.cpp.i
.PHONY : PeriodicListPrunning.cpp.i

PeriodicListPrunning.s: PeriodicListPrunning.cpp.s

.PHONY : PeriodicListPrunning.s

# target to generate assembly for a file
PeriodicListPrunning.cpp.s:
	$(MAKE) -f CMakeFiles/passivedns.dir/build.make CMakeFiles/passivedns.dir/PeriodicListPrunning.cpp.s
.PHONY : PeriodicListPrunning.cpp.s

TrafficeVolumeReduction.o: TrafficeVolumeReduction.cpp.o

.PHONY : TrafficeVolumeReduction.o

# target to build an object file
TrafficeVolumeReduction.cpp.o:
	$(MAKE) -f CMakeFiles/passivedns.dir/build.make CMakeFiles/passivedns.dir/TrafficeVolumeReduction.cpp.o
.PHONY : TrafficeVolumeReduction.cpp.o

TrafficeVolumeReduction.i: TrafficeVolumeReduction.cpp.i

.PHONY : TrafficeVolumeReduction.i

# target to preprocess a source file
TrafficeVolumeReduction.cpp.i:
	$(MAKE) -f CMakeFiles/passivedns.dir/build.make CMakeFiles/passivedns.dir/TrafficeVolumeReduction.cpp.i
.PHONY : TrafficeVolumeReduction.cpp.i

TrafficeVolumeReduction.s: TrafficeVolumeReduction.cpp.s

.PHONY : TrafficeVolumeReduction.s

# target to generate assembly for a file
TrafficeVolumeReduction.cpp.s:
	$(MAKE) -f CMakeFiles/passivedns.dir/build.make CMakeFiles/passivedns.dir/TrafficeVolumeReduction.cpp.s
.PHONY : TrafficeVolumeReduction.cpp.s

main.o: main.cpp.o

.PHONY : main.o

# target to build an object file
main.cpp.o:
	$(MAKE) -f CMakeFiles/passivedns.dir/build.make CMakeFiles/passivedns.dir/main.cpp.o
.PHONY : main.cpp.o

main.i: main.cpp.i

.PHONY : main.i

# target to preprocess a source file
main.cpp.i:
	$(MAKE) -f CMakeFiles/passivedns.dir/build.make CMakeFiles/passivedns.dir/main.cpp.i
.PHONY : main.cpp.i

main.s: main.cpp.s

.PHONY : main.s

# target to generate assembly for a file
main.cpp.s:
	$(MAKE) -f CMakeFiles/passivedns.dir/build.make CMakeFiles/passivedns.dir/main.cpp.s
.PHONY : main.cpp.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... rebuild_cache"
	@echo "... json-install"
	@echo "... libtins-build"
	@echo "... boost"
	@echo "... edit_cache"
	@echo "... libtins-install"
	@echo "... passivedns"
	@echo "... boost-build"
	@echo "... libtins"
	@echo "... boost-install"
	@echo "... json"
	@echo "... json-build"
	@echo "... KafkaConnector.o"
	@echo "... KafkaConnector.i"
	@echo "... KafkaConnector.s"
	@echo "... PeriodicListPrunning.o"
	@echo "... PeriodicListPrunning.i"
	@echo "... PeriodicListPrunning.s"
	@echo "... TrafficeVolumeReduction.o"
	@echo "... TrafficeVolumeReduction.i"
	@echo "... TrafficeVolumeReduction.s"
	@echo "... main.o"
	@echo "... main.i"
	@echo "... main.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system

