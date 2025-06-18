#pragma once
#include <vulkan/vulkan.h>
#include <vector>

class vk_physical_driver {
    struct surface_properties {
        VkSurfaceCapabilitiesKHR surface_capabilities;
        VkSurfaceFormatKHR surface_format;
    };

    struct queue_family_indices {
        uint32_t graphics=-1;
        uint32_t compute=-1;
        uint32_t transfer=-1;
    };
public:
    vk_physical_driver() = default;
    vk_physical_driver(const VkInstance& p_instance);
    ~vk_physical_driver() = default;

    [[nodiscard]] queue_family_indices family_indices() const { return m_queue_indices; }

    // Request the queue specific family through vulkan
    uint32_t presentation_index(const VkSurfaceKHR& p_surface);

    // Request specified surface properties
    surface_properties read_surface_properties(const VkSurfaceKHR& p_surface);

    // Treats `vk_physical_driver` as a VkPhysicalDevice handler entirely with helpful functions
    operator VkPhysicalDevice() const { return m_physical; }

    operator VkPhysicalDevice() { return m_physical; }

private:
    queue_family_indices select_queue_family_indices();

private:
    VkPhysicalDevice m_physical=nullptr;
    queue_family_indices m_queue_indices{};
    std::vector<VkQueueFamilyProperties> m_queue_family_properties;
    surface_properties m_surface_properties{};
};