cmake_minimum_required(VERSION 2.8.3)
project(section01_skeleton)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  std_msgs
  message_generation
  hello_friend
)

# TODO add message 
# add_message_files(
# 	FILES
	
# )

# TODO add service here 
# add_service_files(
# 	FILES

# )

# TODO uncomment to generate messages and services
# generate_messages(
#    DEPENDENCIES
#    std_msgs
# )

catkin_package(
  CATKIN_DEPENDS message_runtime
)

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
)

add_executable(friend_hello_pub src/friend_hello_pub.cpp)
# add_dependencies(friend_hello_pub  hello_friend_generate_messages_cpp)
target_link_libraries(friend_hello_pub ${catkin_LIBRARIES})

add_executable(friend_hello_sub src/friend_hello_sub.cpp)
# add_dependencies(friend_hello_sub  hello_friend_generate_messages_cpp)
target_link_libraries(friend_hello_sub ${catkin_LIBRARIES})

# add_executable(friend_service_server src/friend_service_server.cpp)
# add_dependencies(friend_service_server  hello_friend_generate_messages_cpp)
# target_link_libraries(friend_service_server ${catkin_LIBRARIES})

# add_executable(friend_service_client src/friend_service_client.cpp)
# add_dependencies(friend_service_client  hello_friend_generate_messages_cpp)
# target_link_libraries(friend_service_client ${catkin_LIBRARIES})

