cmake_minimum_required(VERSION 3.15)

# set the project name
project(server)

include_directories(./include)
aux_source_directory(./src DIR_SRCS)

# add the executable
add_executable(server ${DIR_SRCS})

add_executable(client client.cpp src/message.cpp)

target_link_libraries(server LINK_PUBLIC sqlite3)