#include "vk_context.hpp"
#include <spdlog/spdlog.h>

int main() {
    vk_instance instance = vk_instance("Vulkan Application");
    
    bool is_instance_valid = (instance != nullptr);

    spdlog::info("instance instance is valid? = {}", is_instance_valid);
    return 0;
}