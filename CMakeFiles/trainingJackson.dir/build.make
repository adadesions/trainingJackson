# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.7

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
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.7.2/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.7.2/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/adacodeio/GitHub/trainingJackson

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/adacodeio/GitHub/trainingJackson

# Include any dependencies generated for this target.
include CMakeFiles/trainingJackson.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/trainingJackson.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/trainingJackson.dir/flags.make

CMakeFiles/trainingJackson.dir/src/app.cpp.o: CMakeFiles/trainingJackson.dir/flags.make
CMakeFiles/trainingJackson.dir/src/app.cpp.o: src/app.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/adacodeio/GitHub/trainingJackson/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/trainingJackson.dir/src/app.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/trainingJackson.dir/src/app.cpp.o -c /Users/adacodeio/GitHub/trainingJackson/src/app.cpp

CMakeFiles/trainingJackson.dir/src/app.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/trainingJackson.dir/src/app.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/adacodeio/GitHub/trainingJackson/src/app.cpp > CMakeFiles/trainingJackson.dir/src/app.cpp.i

CMakeFiles/trainingJackson.dir/src/app.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/trainingJackson.dir/src/app.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/adacodeio/GitHub/trainingJackson/src/app.cpp -o CMakeFiles/trainingJackson.dir/src/app.cpp.s

CMakeFiles/trainingJackson.dir/src/app.cpp.o.requires:

.PHONY : CMakeFiles/trainingJackson.dir/src/app.cpp.o.requires

CMakeFiles/trainingJackson.dir/src/app.cpp.o.provides: CMakeFiles/trainingJackson.dir/src/app.cpp.o.requires
	$(MAKE) -f CMakeFiles/trainingJackson.dir/build.make CMakeFiles/trainingJackson.dir/src/app.cpp.o.provides.build
.PHONY : CMakeFiles/trainingJackson.dir/src/app.cpp.o.provides

CMakeFiles/trainingJackson.dir/src/app.cpp.o.provides.build: CMakeFiles/trainingJackson.dir/src/app.cpp.o


# Object files for target trainingJackson
trainingJackson_OBJECTS = \
"CMakeFiles/trainingJackson.dir/src/app.cpp.o"

# External object files for target trainingJackson
trainingJackson_EXTERNAL_OBJECTS =

build/trainingJackson: CMakeFiles/trainingJackson.dir/src/app.cpp.o
build/trainingJackson: CMakeFiles/trainingJackson.dir/build.make
build/trainingJackson: /usr/local/lib/libopencv_dnn.3.3.0.dylib
build/trainingJackson: /usr/local/lib/libopencv_ml.3.3.0.dylib
build/trainingJackson: /usr/local/lib/libopencv_objdetect.3.3.0.dylib
build/trainingJackson: /usr/local/lib/libopencv_shape.3.3.0.dylib
build/trainingJackson: /usr/local/lib/libopencv_stitching.3.3.0.dylib
build/trainingJackson: /usr/local/lib/libopencv_superres.3.3.0.dylib
build/trainingJackson: /usr/local/lib/libopencv_videostab.3.3.0.dylib
build/trainingJackson: dlib_build/libdlib.a
build/trainingJackson: /usr/local/lib/libopencv_calib3d.3.3.0.dylib
build/trainingJackson: /usr/local/lib/libopencv_features2d.3.3.0.dylib
build/trainingJackson: /usr/local/lib/libopencv_flann.3.3.0.dylib
build/trainingJackson: /usr/local/lib/libopencv_highgui.3.3.0.dylib
build/trainingJackson: /usr/local/lib/libopencv_photo.3.3.0.dylib
build/trainingJackson: /usr/local/lib/libopencv_video.3.3.0.dylib
build/trainingJackson: /usr/local/lib/libopencv_videoio.3.3.0.dylib
build/trainingJackson: /usr/local/lib/libopencv_imgcodecs.3.3.0.dylib
build/trainingJackson: /usr/local/lib/libopencv_imgproc.3.3.0.dylib
build/trainingJackson: /usr/local/lib/libopencv_core.3.3.0.dylib
build/trainingJackson: /usr/X11R6/lib/libSM.dylib
build/trainingJackson: /usr/X11R6/lib/libICE.dylib
build/trainingJackson: /usr/X11R6/lib/libX11.dylib
build/trainingJackson: /usr/X11R6/lib/libXext.dylib
build/trainingJackson: /usr/local/lib/libPng.dylib
build/trainingJackson: /usr/lib/libz.dylib
build/trainingJackson: /usr/lib/libcblas.dylib
build/trainingJackson: /usr/lib/liblapack.dylib
build/trainingJackson: /usr/lib/libsqlite3.dylib
build/trainingJackson: CMakeFiles/trainingJackson.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/adacodeio/GitHub/trainingJackson/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable build/trainingJackson"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/trainingJackson.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/trainingJackson.dir/build: build/trainingJackson

.PHONY : CMakeFiles/trainingJackson.dir/build

CMakeFiles/trainingJackson.dir/requires: CMakeFiles/trainingJackson.dir/src/app.cpp.o.requires

.PHONY : CMakeFiles/trainingJackson.dir/requires

CMakeFiles/trainingJackson.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/trainingJackson.dir/cmake_clean.cmake
.PHONY : CMakeFiles/trainingJackson.dir/clean

CMakeFiles/trainingJackson.dir/depend:
	cd /Users/adacodeio/GitHub/trainingJackson && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/adacodeio/GitHub/trainingJackson /Users/adacodeio/GitHub/trainingJackson /Users/adacodeio/GitHub/trainingJackson /Users/adacodeio/GitHub/trainingJackson /Users/adacodeio/GitHub/trainingJackson/CMakeFiles/trainingJackson.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/trainingJackson.dir/depend

