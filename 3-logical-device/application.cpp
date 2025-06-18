#include "vk_context.hpp"
#include "vk_driver.hpp"
#include <spdlog/spdlog.h>

int main() {
    vk_instance instance = vk_instance("Vulkan Application");
    vk_physical_driver physical = vk_physical_driver(instance);
    vk_driver logical_device = vk_driver(physical);

    bool is_instance_valid = (logical_device != nullptr);

    spdlog::info("vk_physical_driver is valid? = {}", is_instance_valid);
    return 0;
}