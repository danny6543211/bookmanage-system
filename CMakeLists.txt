cmake_minimum_required(VERSION 3.15)

# set the project name
project(IS)

include_directories(./include)
aux_source_directory(./src DIR_SRCS)

# add the executable
add_executable(IS ${DIR_SRCS})

target_link_libraries(IS LINK_PUBLIC sqlite3)