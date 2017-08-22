# %Tag(FULLTEXT)%
cmake_minimum_required(VERSION 2.8.3)
project(broadcast)

## Find catkin and any catkin packages
find_package(catkin REQUIRED COMPONENTS roscpp rospy std_msgs geometry_msgs sensor_msgs
  visualization_msgs genmsg)

## Declare ROS messages and services
add_message_files(FILES Num.msg)
add_message_files(FILES RecObject.msg)
add_message_files(FILES CloudPiece.msg)
add_message_files(FILES ObjectsStamped.msg)
add_service_files(FILES AddTwoInts.srv)

## Generate added messages and services
generate_messages(DEPENDENCIES std_msgs geometry_msgs sensor_msgs
  visualization_msgs)

## Declare a catkin package
catkin_package()

## Build talker and listener
include_directories(include ${catkin_INCLUDE_DIRS})

add_executable(talker src/talker.cpp)
target_link_libraries(talker ${catkin_LIBRARIES})
add_dependencies(talker beginner_tutorials_generate_messages_cpp)

add_executable(listener src/listener.cpp)
target_link_libraries(listener ${catkin_LIBRARIES})
add_dependencies(listener beginner_tutorials_generate_messages_cpp)

# %EndTag(FULLTEXT)%
