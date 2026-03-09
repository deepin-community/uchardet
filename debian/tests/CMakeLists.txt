# Test CMake project to ensure uchardet config files work properly

cmake_minimum_required(VERSION 3.13)
project(uchardet_test)

# Try to find uchardet using CMake config file
find_package(uchardet 0.0.7 REQUIRED CONFIG)

# Build the executables
add_executable(detect_dynamic detect.c)
target_link_libraries(detect_dynamic PRIVATE uchardet::libuchardet)

add_executable(detect_static detect.c)
target_link_libraries(detect_static PRIVATE uchardet::libuchardet_static)
target_link_options(detect_static PRIVATE -static)
