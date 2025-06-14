cmake_minimum_required(VERSION 3.27)
project(1-example CXX)


build_application(
    SOURCES
    application.cpp
    vk_context.cpp

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