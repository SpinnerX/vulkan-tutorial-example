cmake_minimum_required(VERSION 3.27)
project(vulkan-tutorial C CXX)

add_subdirectory(1-vulkan-instance)
add_subdirectory(2-physical-device)
add_subdirectory(3-logical-device)
add_subdirectory(4-vulkan-window)

generate_compile_commands()