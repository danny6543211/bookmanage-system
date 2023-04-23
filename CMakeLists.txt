cmake_minimum_required(VERSION 3.15)

# set the project name
project(server)

# 库文件夹
link_directories(dll)


include_directories(./include)
aux_source_directory(./src DIR_SRCS)

# add the executable
add_executable(server ${DIR_SRCS})
add_executable(demo demo.cpp client_socket.cpp src/message.cpp src/database.cpp)


target_link_libraries(server wsock32 ws2_32 sqlite3.dll)
target_link_libraries(demo wsock32 ws2_32)


target_link_libraries(demo sqlite3.dll)
