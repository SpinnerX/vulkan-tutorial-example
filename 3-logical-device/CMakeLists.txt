cmake_minimum_required(VERSION 3.27)
project(3-example CXX)


build_application(
    SOURCES
    application.cpp
    vk_context.cpp
    helper_functions.cpp
    vk_physical_driver.cpp
    vk_driver.cpp

    PACKAGES
    glfw3
    spdlog
    VulkanHeaders
    Vulkan

    LINK_PACKAGES
    glfw
    spdlog::spdlog
    vulkan-headers::vulkan-headers
    Vulkan::Vulkan
)