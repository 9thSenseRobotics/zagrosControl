# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canoncical targets will work.
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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/alaina/ros/zagrosControl

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/alaina/ros/zagrosControl

# Include any dependencies generated for this target.
include CMakeFiles/zagrosServos.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/zagrosServos.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/zagrosServos.dir/flags.make

CMakeFiles/zagrosServos.dir/src/zagrosServos.o: CMakeFiles/zagrosServos.dir/flags.make
CMakeFiles/zagrosServos.dir/src/zagrosServos.o: src/zagrosServos.cpp
CMakeFiles/zagrosServos.dir/src/zagrosServos.o: manifest.xml
CMakeFiles/zagrosServos.dir/src/zagrosServos.o: /opt/ros/electric/ros/core/rosbuild/manifest.xml
CMakeFiles/zagrosServos.dir/src/zagrosServos.o: /opt/ros/electric/ros/core/roslang/manifest.xml
CMakeFiles/zagrosServos.dir/src/zagrosServos.o: /opt/ros/electric/stacks/ros_comm/utilities/cpp_common/manifest.xml
CMakeFiles/zagrosServos.dir/src/zagrosServos.o: /opt/ros/electric/stacks/ros_comm/clients/cpp/roscpp_traits/manifest.xml
CMakeFiles/zagrosServos.dir/src/zagrosServos.o: /opt/ros/electric/stacks/ros_comm/utilities/rostime/manifest.xml
CMakeFiles/zagrosServos.dir/src/zagrosServos.o: /opt/ros/electric/stacks/ros_comm/clients/cpp/roscpp_serialization/manifest.xml
CMakeFiles/zagrosServos.dir/src/zagrosServos.o: /opt/ros/electric/ros/tools/rospack/manifest.xml
CMakeFiles/zagrosServos.dir/src/zagrosServos.o: /opt/ros/electric/ros/core/roslib/manifest.xml
CMakeFiles/zagrosServos.dir/src/zagrosServos.o: /opt/ros/electric/stacks/ros_comm/utilities/xmlrpcpp/manifest.xml
CMakeFiles/zagrosServos.dir/src/zagrosServos.o: /opt/ros/electric/stacks/ros_comm/tools/rosconsole/manifest.xml
CMakeFiles/zagrosServos.dir/src/zagrosServos.o: /opt/ros/electric/stacks/ros_comm/messages/std_msgs/manifest.xml
CMakeFiles/zagrosServos.dir/src/zagrosServos.o: /opt/ros/electric/stacks/ros_comm/messages/rosgraph_msgs/manifest.xml
CMakeFiles/zagrosServos.dir/src/zagrosServos.o: /opt/ros/electric/stacks/ros_comm/clients/cpp/roscpp/manifest.xml
CMakeFiles/zagrosServos.dir/src/zagrosServos.o: /opt/ros/electric/stacks/ros_comm/clients/rospy/manifest.xml
CMakeFiles/zagrosServos.dir/src/zagrosServos.o: /opt/ros/electric/ros/tools/rosclean/manifest.xml
CMakeFiles/zagrosServos.dir/src/zagrosServos.o: /opt/ros/electric/stacks/ros_comm/tools/rosgraph/manifest.xml
CMakeFiles/zagrosServos.dir/src/zagrosServos.o: /opt/ros/electric/stacks/ros_comm/tools/rosparam/manifest.xml
CMakeFiles/zagrosServos.dir/src/zagrosServos.o: /opt/ros/electric/stacks/ros_comm/tools/rosmaster/manifest.xml
CMakeFiles/zagrosServos.dir/src/zagrosServos.o: /opt/ros/electric/stacks/ros_comm/tools/rosout/manifest.xml
CMakeFiles/zagrosServos.dir/src/zagrosServos.o: /opt/ros/electric/stacks/ros_comm/tools/roslaunch/manifest.xml
CMakeFiles/zagrosServos.dir/src/zagrosServos.o: /opt/ros/electric/ros/tools/rosunit/manifest.xml
CMakeFiles/zagrosServos.dir/src/zagrosServos.o: /opt/ros/electric/stacks/ros_comm/tools/rostest/manifest.xml
CMakeFiles/zagrosServos.dir/src/zagrosServos.o: /opt/ros/electric/stacks/ros_comm/tools/topic_tools/manifest.xml
CMakeFiles/zagrosServos.dir/src/zagrosServos.o: /opt/ros/electric/stacks/ros_comm/tools/rosbag/manifest.xml
CMakeFiles/zagrosServos.dir/src/zagrosServos.o: /opt/ros/electric/stacks/ros_comm/tools/rosbagmigration/manifest.xml
CMakeFiles/zagrosServos.dir/src/zagrosServos.o: /opt/ros/electric/stacks/common_msgs/geometry_msgs/manifest.xml
CMakeFiles/zagrosServos.dir/src/zagrosServos.o: /opt/ros/electric/stacks/ros_comm/messages/std_msgs/msg_gen/generated
CMakeFiles/zagrosServos.dir/src/zagrosServos.o: /opt/ros/electric/stacks/ros_comm/messages/rosgraph_msgs/msg_gen/generated
CMakeFiles/zagrosServos.dir/src/zagrosServos.o: /opt/ros/electric/stacks/ros_comm/clients/cpp/roscpp/msg_gen/generated
CMakeFiles/zagrosServos.dir/src/zagrosServos.o: /opt/ros/electric/stacks/ros_comm/clients/cpp/roscpp/srv_gen/generated
CMakeFiles/zagrosServos.dir/src/zagrosServos.o: /opt/ros/electric/stacks/ros_comm/tools/topic_tools/srv_gen/generated
CMakeFiles/zagrosServos.dir/src/zagrosServos.o: /opt/ros/electric/stacks/common_msgs/geometry_msgs/msg_gen/generated
	$(CMAKE_COMMAND) -E cmake_progress_report /home/alaina/ros/zagrosControl/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/zagrosServos.dir/src/zagrosServos.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -W -Wall -Wno-unused-parameter -fno-strict-aliasing -pthread -o CMakeFiles/zagrosServos.dir/src/zagrosServos.o -c /home/alaina/ros/zagrosControl/src/zagrosServos.cpp

CMakeFiles/zagrosServos.dir/src/zagrosServos.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/zagrosServos.dir/src/zagrosServos.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -W -Wall -Wno-unused-parameter -fno-strict-aliasing -pthread -E /home/alaina/ros/zagrosControl/src/zagrosServos.cpp > CMakeFiles/zagrosServos.dir/src/zagrosServos.i

CMakeFiles/zagrosServos.dir/src/zagrosServos.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/zagrosServos.dir/src/zagrosServos.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -W -Wall -Wno-unused-parameter -fno-strict-aliasing -pthread -S /home/alaina/ros/zagrosControl/src/zagrosServos.cpp -o CMakeFiles/zagrosServos.dir/src/zagrosServos.s

CMakeFiles/zagrosServos.dir/src/zagrosServos.o.requires:
.PHONY : CMakeFiles/zagrosServos.dir/src/zagrosServos.o.requires

CMakeFiles/zagrosServos.dir/src/zagrosServos.o.provides: CMakeFiles/zagrosServos.dir/src/zagrosServos.o.requires
	$(MAKE) -f CMakeFiles/zagrosServos.dir/build.make CMakeFiles/zagrosServos.dir/src/zagrosServos.o.provides.build
.PHONY : CMakeFiles/zagrosServos.dir/src/zagrosServos.o.provides

CMakeFiles/zagrosServos.dir/src/zagrosServos.o.provides.build: CMakeFiles/zagrosServos.dir/src/zagrosServos.o

# Object files for target zagrosServos
zagrosServos_OBJECTS = \
"CMakeFiles/zagrosServos.dir/src/zagrosServos.o"

# External object files for target zagrosServos
zagrosServos_EXTERNAL_OBJECTS =

bin/zagrosServos: CMakeFiles/zagrosServos.dir/src/zagrosServos.o
bin/zagrosServos: CMakeFiles/zagrosServos.dir/build.make
bin/zagrosServos: CMakeFiles/zagrosServos.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable bin/zagrosServos"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/zagrosServos.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/zagrosServos.dir/build: bin/zagrosServos
.PHONY : CMakeFiles/zagrosServos.dir/build

CMakeFiles/zagrosServos.dir/requires: CMakeFiles/zagrosServos.dir/src/zagrosServos.o.requires
.PHONY : CMakeFiles/zagrosServos.dir/requires

CMakeFiles/zagrosServos.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/zagrosServos.dir/cmake_clean.cmake
.PHONY : CMakeFiles/zagrosServos.dir/clean

CMakeFiles/zagrosServos.dir/depend:
	cd /home/alaina/ros/zagrosControl && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/alaina/ros/zagrosControl /home/alaina/ros/zagrosControl /home/alaina/ros/zagrosControl /home/alaina/ros/zagrosControl /home/alaina/ros/zagrosControl/CMakeFiles/zagrosServos.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/zagrosServos.dir/depend

