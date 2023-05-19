cmake_minimum_required(VERSION 3.15)

# set the project name
project(server)

# 库文件夹
link_directories(dll)


include_directories(./include ./ref)
# aux_source_directory(./src DIR_SRCS)

# add the executable
add_executable(server ./src/main.cpp ./src/user_library.cpp ./src/book_library.cpp ./src/user.cpp ./src/manager.cpp ./src/visitor.cpp ./src/server.cpp)
add_executable(demo demo.cpp)


target_link_libraries(server wsock32 ws2_32 sqlite3.dll)
target_link_libraries(demo wsock32 ws2_32)


# target_link_libraries(demo sqlite3.dll)
