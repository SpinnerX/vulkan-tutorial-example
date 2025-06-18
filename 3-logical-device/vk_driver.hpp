#pragma once
#include <vulkan/vulkan.h>
#include "vk_physical_driver.hpp"

class vk_driver {
    struct queue_info {
        uint32_t index=-1;
        uint32_t family_queue=-1;
    };
    struct device_queues {
        VkQueue graphics;
        VkQueue transfer;
        VkQueue compute;
    };
public:
    vk_driver() = default;
    vk_driver(const vk_physical_driver& p_physical);
    ~vk_driver() = default;

    // Returns -1 if no flags available/compatible/valid
    uint32_t select_memory_type(const uint32_t& p_type_filter, VkMemoryPropertyFlags p_property_flags);

    [[nodiscard]] VkQueue graphics_queue() const { return m_graphics_queue; }

    // Returns specific queue handler based on queue index
    VkQueue get_queue(const queue_info& p_info);

    VkFormat depth_format();

    operator VkDevice() const { return nullptr; }

    operator VkDevice() { return nullptr; }

    void destroy();

private:
    VkPhysicalDevice m_physical=nullptr;
    VkDevice m_driver=nullptr;
    VkQueue m_graphics_queue=nullptr;
    device_queues m_device_queues;
};