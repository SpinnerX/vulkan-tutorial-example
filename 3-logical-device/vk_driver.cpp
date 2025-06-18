#include "vk_driver.hpp"
#include <span>
#include <array>
#include "helper_functions.hpp"
#include "vulkan-imports.hpp"

static VkFormat search_supported_depth_format(
      const VkPhysicalDevice& p_physical,
      const std::span<VkFormat>& p_formats,
      VkImageTiling p_tiling,
      VkFormatFeatureFlags p_feature_flag) {
        VkFormat format = VK_FORMAT_UNDEFINED;

        for (size_t i = 0; i < p_formats.size(); i++) {
            VkFormat current_format = p_formats[i];
            VkFormatProperties format_properties;
            vkGetPhysicalDeviceFormatProperties(
              p_physical, current_format, &format_properties);

            if (p_tiling == VK_IMAGE_TILING_LINEAR) {
                if (format_properties.linearTilingFeatures & p_feature_flag) {
                    format = current_format;
                }
            }
            else if (p_tiling == VK_IMAGE_TILING_OPTIMAL and
                     format_properties.optimalTilingFeatures & p_feature_flag) {
                format = current_format;
            }
        }

        return format;
    }

static VkFormat search_depth_format(const VkPhysicalDevice& p_physical) {
    std::vector<VkFormat> candidate_formats = {
        VK_FORMAT_D32_SFLOAT,
        VK_FORMAT_D32_SFLOAT_S8_UINT,
        VK_FORMAT_D24_UNORM_S8_UINT
    };

    VkFormat format = search_supported_depth_format(
        p_physical,
        candidate_formats,
        VK_IMAGE_TILING_OPTIMAL,
        VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT);
    return format;
}

static VkFormat s_depth_format_selected;

vk_driver::vk_driver(const vk_physical_driver& p_physical) : m_physical(p_physical) {
    s_depth_format_selected = search_depth_format(p_physical);
    // float queue_priority[]
    std::array<float, 1> queue_priority = {0.0f};

    std::vector<const char*> device_extensions = {
        VK_KHR_SWAPCHAIN_EXTENSION_NAME
    };

    uint32_t graphics_index = p_physical.family_indices().graphics;
    printf("graphics_index = %i\n", (int)graphics_index);
    VkDeviceQueueCreateInfo queue_ci = {
        .sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO,
        .pNext = nullptr,
        .flags = 0,
        .queueFamilyIndex = graphics_index,
        .queueCount = static_cast<uint32_t>(queue_priority.size()),
        .pQueuePriorities = queue_priority.data(),
    };

    VkDeviceCreateInfo device_ci = {
        .sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO,
        .pNext = nullptr,
        .flags = 0,
        .queueCreateInfoCount = 1,
        .pQueueCreateInfos = &queue_ci,
        .enabledLayerCount = 0,
        .ppEnabledLayerNames = nullptr,
        .enabledExtensionCount =
            static_cast<uint32_t>(device_extensions.size()),
        .ppEnabledExtensionNames = device_extensions.data(),
    };

    VkPhysicalDeviceFeatures features;
    vkGetPhysicalDeviceFeatures(m_physical, &features);
    features.robustBufferAccess = false;
    device_ci.pEnabledFeatures = &features;

    vk_check(vkCreateDevice(m_physical, &device_ci, nullptr, &m_driver), "vkCreateDevice");

    vkGetDeviceQueue(m_driver, graphics_index, 0, &m_device_queues.graphics);
}

VkQueue vk_driver::get_queue(const queue_info& p_info) {
    VkQueue queue_handler;
    vkGetDeviceQueue(m_driver,
                        p_info.family_queue,
                        p_info.index,
                        &queue_handler);
    return queue_handler;
}

//! @note Returns -1 if there are no flags available/compatible/valid
uint32_t vk_driver::select_memory_type(
    const uint32_t& p_type_filter,
    VkMemoryPropertyFlags p_property_flag) {
    VkPhysicalDeviceMemoryProperties mem_props;
    vkGetPhysicalDeviceMemoryProperties(m_physical, &mem_props);

    for (uint32_t i = 0; i < mem_props.memoryTypeCount; i++) {
        if ((p_type_filter & (1 << i)) and
            (mem_props.memoryTypes[i].propertyFlags & p_property_flag) ==
                p_property_flag) {
            return i;
        }
    }

    return -1;
}

VkFormat vk_driver::depth_format() {
    return s_depth_format_selected;
}

void vk_driver::destroy() {
    vkDestroyDevice(m_driver, nullptr);
}