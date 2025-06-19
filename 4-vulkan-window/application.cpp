#include "vulkan-imports.hpp"
#include "vk_context.hpp"
#include "vk_window.hpp"
#include "vk_driver.hpp"
#include <GLFW/glfw3.h>
#include <spdlog/spdlog.h> // logger framework

int main() {
    // 0. Setting up GLFW API
    if(!glfwInit()) {
        return -1;
    }

    // This configures GLFW API to use only the windowing system
    // Letting vulkan handle the rest and disable resizability
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, true);

    // 1.) Setting up vulkan API with VkInstance
    vk_instance instance = vk_instance("Vulkan Application");
    window_settings settings = {
        .name = "vulkan tutorial",
        .width = 800,
        .height = 600,
        // .physical = physical,
        // .logical_device = logical_device
    };

    // 2. Setting up physical device
    vk_physical_driver physical = vk_physical_driver(instance);

    // 3. Setting up logical device
    vk_driver logical_device = vk_driver(physical);

    vk_window window = vk_window(instance, settings);

    window.create_vk_surface(instance);

    while(window.active()) {

        glfwPollEvents();
    }

    window.destroy();
    return 0;
}