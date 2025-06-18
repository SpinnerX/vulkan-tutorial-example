# 3 -- Vulkan Logical Device


In this code tutorial, in this readme I will get started on going over what are logical devices. Why they are needed? Using vulkan, and how these can be used?

## Overview

After selecting a vulkan physical device. The next thing when using vulkan is needing to create and specify a logical *device* to work with.  Logical devices is similar to the `VkInstance` creation, which involves descriptively setting up the features needed to use for the logical device.

In this code tutorial, we are only going to be focusing on getting the base setup for logical device. Only using the discrete GPU that is available on your machine. When you create logical devices, you also need to specify which queues are created, that get queried from queue families that are available.

There are cases where you can create multiple logical devices from the same physical device if the requirements vary, but for now we will only be creating a single logic device to get the fundamentals of how they are created using Vulkan's API.

## Control Flow of Creating Logical Devices

<!-- When creating a logical device these are the following specifications when doing so:

* Setup `VkDeviceQueueCreateInfo` which is for specifying the priorities of the queue's you want to create.
* Extract from `vk_physical_driver` to get the graphics queue index.
* Once retrieving the graphics queue index, we then use `vkGetQueue` to assign our handler to the graphics queue of our specifications.
* Specify `VkPhysicalDeviceFeatures` which are features that helps vulkan to know what sets of features for your current device, you want to enable for vulkan to use.
 -->

In this code you are going to notice a class called `vk_driver`, this class is to abstract a lot of the requirements of specifying the creation of logical devices. This is to simplify the development of working with vulkan and focusing on simpler designs for these code to allow for direct use of how it works.

Logical devices uses the queue families searched and found from the physical device that we created in the previous code example tutorial.

If you are new to vulkan, logical devices are going to be the main points of submitting work. Meaning all of the handlers in vulkan are going to be heavily relying on the `vk_driver` to setup your Vulkan handlers. 

This class does the following thing:

* Sets up queue priorities. Vulkan allows you to assign priorities to queues to influence scheduling of command execution using floating-point, you will se I set it to `0.0f`.
* Extracting the device queue index, to set in the struct `VkDeviceQueueCreateInfo` that gets set when calling the `VkDeviceCreateInfo` struct.
* Then creating logical device using the `VkDeviceCreateInfo` to prepare configuring the `VkDevice`
* Creating a logical device through `vkCreateDevice` function.
    * Parameters for that function is `vkCreateDevice(VkPhysicalDevice, const VkDeviceCreateInfo*, const const VkAllocationCallbacks* pAllocator, VkDevice* pDevice)`


### vk_driver class

In the `vk_driver` class, has a `VkDevice` that is the handler for the class. You can also treat `vk_driver` class as a handler of VkDevice because we overload the operator to be `operator VkDevice() { return m_driver_handler; }`. Which enables us to use this class as if we are directly working with VkDevice.

When you look in the `vk_driver` class, you see I added a few functions.

* select_memory_type
    * 
* get_queue(const queue_info&)
    * This function is used for retrieving queue handlers that you can specify through `queue_info`
    * To retrieve the queue handler it uses a call to the `vkGetDveiceQueue(VkDevice device, uint32_t queueFamilyIndex, uint32_t queueIndex, VkQueue* pQueue)`
    * Parameters are the logical device, queue family, queue index, and pointer to the handler of the specific queue that gets assigned.

* depth_format
    * This function actually retrieves the depth format. (Will be used later when enabling depth buffering)
    * It does checks for the kinds of depth format that is supported by your current physical hardware.
    * `search_depth_format` sets the candidates formats for searching for the feature of the attachment and formats available.

## Conclusion

Once you create the object and you check if the validity of the `vk_driver` class is completely implemented. Then you should be able to check if the validation errors either throw you an error and you can check if the handler was successfully assigned by checking if the handler is `nullptr`.

If it is successfully, then you successfully created a logical device in Vulkan!!

At this point in the code example, the tricky part is completed. This is the base implementation to getting the physical and logical devices implemented.

The next code tutorial we are now going to get a GLFW window and setting up a vulkan surface.