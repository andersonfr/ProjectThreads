cmake_minimum_required(VERSION 3.20)
#set the project name and version
project(ProjectThreads VERSION 0.1)

#specify the c++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED true)

#configure file
configure_file("src/ProjectThreadsConfig.h.in" "ProjectThreadsConfig.h")

#add the executable
add_executable(ProjectThreads "src/main.cpp")

#target include dir
target_include_directories(ProjectThreads PUBLIC "${PROJECT_BINARY_DIR}")