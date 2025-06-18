#include "vk_physical_driver.hpp"
#include "vulkan-imports.hpp"
#include <stdio.h>
#include <vector>
#include <array>
#include "helper_functions.hpp"

vk_physical_driver::vk_physical_driver(const VkInstance& p_instance) {

    // Requesting device count of GPU's available
    uint32_t device_count=0;
    vkEnumeratePhysicalDevices(p_instance, &device_count, nullptr);

    if(device_count == 0) {
        printf("Vulkan: Failed to find any available GPU's on your current machine as device_count = 0\n");
        return;
    }

    std::vector<VkPhysicalDevice> devices(device_count);
    vkEnumeratePhysicalDevices(p_instance, &device_count, devices.data());

    for(const auto& gpu_device : devices) {
        VkPhysicalDeviceProperties device_properties;
        VkPhysicalDeviceFeatures device_features;
        vkGetPhysicalDeviceProperties(gpu_device, &device_properties);
        vkGetPhysicalDeviceFeatures(gpu_device, &device_features);

        // Select the available GPU that is currently on you machine
        if(device_properties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU) {
            m_physical = gpu_device;
            break;
        }
    }

    uint32_t queue_family_count;
    vkGetPhysicalDeviceQueueFamilyProperties(m_physical, &queue_family_count, nullptr);
    
    m_queue_family_properties.resize(queue_family_count);
    vkGetPhysicalDeviceQueueFamilyProperties(m_physical, &queue_family_count, m_queue_family_properties.data());

    m_queue_indices = select_queue_family_indices();
}

vk_physical_driver::queue_family_indices vk_physical_driver::select_queue_family_indices() {
    VkPhysicalDeviceMemoryProperties physical_device_memory_properties;
    vkGetPhysicalDeviceMemoryProperties(m_physical, &physical_device_memory_properties);
    vk_physical_driver::queue_family_indices indices;
    int i = 0;
    for (const auto& queue_family : m_queue_family_properties) {
        if (queue_family.queueFlags & VK_QUEUE_GRAPHICS_BIT) {
            indices.graphics = i;
            break;
        }
        i++;
    }

    return indices;
}

uint32_t vk_physical_driver::presentation_index(const VkSurfaceKHR& p_surface) {
    uint32_t present_index = -1;
    VkBool32 compatible = false;
    uint32_t i = 0;
    for(const auto& queue_family : m_queue_family_properties) {
        if(queue_family.queueFlags & VK_QUEUE_GRAPHICS_BIT) {
            vk_check(vkGetPhysicalDeviceSurfaceSupportKHR(m_physical, i, p_surface, &compatible), "vkGetPhysicalDeviceSurfaceSupportKHR");

            if(compatible) {
                present_index = i;
            }
        }

        i++;
    }
    return present_index;
}