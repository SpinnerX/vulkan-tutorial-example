#pragma once
#include <string>
#include "vulkan-imports.hpp"

struct window_settings {
    std::string name="";
    int width=0;
    int height=0;
    VkPhysicalDevice physical=nullptr;
    VkDevice logical_device=nullptr;
};

class vk_window {
public:
    vk_window() = default;
    vk_window(const VkInstance& p_instance, const window_settings& p_settings);
    ~vk_window();

    void center_window();

    void create_vk_surface(const VkInstance& p_instance);

    [[nodiscard]] bool active() const;

    operator GLFWwindow*() const { return m_window_handler; }

    operator GLFWwindow*() { return m_window_handler; }


    void destroy();

private:
    GLFWwindow* m_window_handler=nullptr;
    VkSurfaceKHR m_surface_handler=nullptr;
    VkInstance m_vk_instance=nullptr;
    window_settings m_settings{};
};