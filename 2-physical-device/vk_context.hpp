#pragma once
#include <string>
#include <vulkan/vulkan.h>

class vk_instance {
public:
    vk_instance() = default;
    vk_instance(const std::string& p_name);

    operator VkInstance() const { return m_instance; }
    
    operator VkInstance() { return m_instance; }

private:
    VkInstance m_instance=nullptr;
};