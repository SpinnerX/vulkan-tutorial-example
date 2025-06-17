#include "vulkan-imports.hpp"
#include "helper_functions.hpp"
#include <stdio.h>

void vk_check(const VkResult& p_result,
                  const char* p_tag){
    if(p_result != VK_SUCCESS) {
        printf("%s errorred with status %i\n", p_tag, (int)p_result);
    }
}