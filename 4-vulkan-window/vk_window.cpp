#include "vulkan-imports.hpp"
#include "vk_window.hpp"
#include "helper_functions.hpp"

vk_window::vk_window(const VkInstance& p_instance, const window_settings& p_settings) : m_vk_instance(p_instance), m_settings(p_settings) {

    // 1. creating glfw window
    m_window_handler = glfwCreateWindow(m_settings.width, m_settings.height, m_settings.name.c_str(), nullptr, nullptr);
}

void vk_window::create_vk_surface(const VkInstance& p_instance) {
    // 2. creating vulkan surface
    // Using GLFW's builtin API for creating the surface to the VkSurface handler since they do that for you automatically
    // As GLFW is cross-platform
    vk_check(glfwCreateWindowSurface(p_instance, m_window_handler, nullptr, &m_surface_handler), "glfwCreateWindowSurface");
}

vk_window::~vk_window() {
    glfwDestroyWindow(m_window_handler);
}

void vk_window::center_window() {
    GLFWmonitor* monitor = glfwGetPrimaryMonitor();
    const GLFWvidmode* mode = glfwGetVideoMode(monitor);
    int width = (mode->width / 2) - (m_settings.width / 2);
    int height = (mode->height / 2) - (m_settings.height / 2);
    glfwSetWindowPos(m_window_handler, width, height);

}

bool vk_window::active() const {
    return !glfwWindowShouldClose(m_window_handler);
}

void vk_window::destroy() {
    if(m_surface_handler != nullptr) {
        vkDestroySurfaceKHR(m_vk_instance, m_surface_handler, nullptr);
    }
}