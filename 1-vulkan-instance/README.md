# 1 Vulkan Code Example

This is the first code example to learn the basics of implementing vulkan.

The next following tutorial code examples are stand alone of setting up and focuses on getting minimal code examples to get vulkan working. Including just to help review or getting the basics of how vulkan works.


Each vulkan code tutorial is going to described specific new things that each tutorial introduces, how they are used, why they are used, and the interpretation on the vulkan-side as best I can possibly add.

## Overview

1-vulkan-instance covers the basics of setting up `VkApplicationInfo` and `VkInstance`. When initializing vulkan, this is the first thing needed to initialize the vulkan API.


## VkApplicationInfo and VkInstance Overview

`VkInstance` is the connection between the application-side and vulkan API. There are details specify some details about your application to the driver.


Before initializing the `VkInstance`, you need to firs tell vulkan about information about the application. This includes information such as the `applicationName`, `applicationVersion`, and `apiVersion`.

These information are optional, but provide information to the driver to optimize for specific applications, this spoecification is for the struct called `VkApplicationInfo`.

Here are the properties of setting the `VkApplicationInfo` properties below.

```C++

VkApplicationInfo app_info = {
    .sType = VK_STRUCTURE_TYPE_APPLICATION_INFO,
    .pApplicationName = "1-vulkan-instance",
    .applicationVersion = VK_MAKE_VERSION(1, 0, 0),
    .pEngineName = "No Engine",
    .engineVersion = 1,
    .apiVersion = VK_API_VERSION_1_3,
};
```

`sType` - vulkan requires you to specify the `sType` member.
`pNext` - This value can just be set to `nullptr`. This is one of the struct members which can point to an extension information.

## VkInstanceCreateInfo

Vulkan requires structs to be passsed to create handlers by specifying member information on how the handlers are going to be utilized and specify how the resources that handler needs.

```C++
VkInstanceCreateInfo create_info = {
    .sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
    .pNext = nullptr,
    .flags = 0,
    .pApplicationInfo = &app_info
};
```

In vulkan, a lot of information. This struct tells vulkan about the specific global extensions that is needed by Vulkan to interface with the windowing system.

These following vulkan tutorial code will be utilizing GLFW as the window integration system.


```C++
uint32_t glfw_extension_count = 0;
const char** glfw_extensions;
glfw_extensions = glfwGetRequiredInstanceExtensions(&glfw_extension_count);

std::vector<const char*> extensions(glfw_extensions, glfw_extensions + glfw_extension_count);

extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);

create_info.enabledExtensionCount = (uint32_t)extensions.size();
create_info.ppEnabledExtensionNames = extensions.data();
```

Last two members determine global validation layers to enable.

```C++
create_info.enableLayerCount =0;
```

## Creating VkInstance

Now, that `VkApplicationInfo` and `VkInstanceCreateInfo` have been created, now its time to create the actual `VkInstance` handler.

`vk_check` function is to validate if the `vkCreateInstance` was created successfully.

```C++
// Reference to vk_context.hpp on its creation
VkInstance m_instance=nullptr;
vk_check(vkCreateInstance(&create_info, nullptr& m_instance))
```

## General Pattern for Object Creation in Vulkan

* Pointer to struct + creation info
* Pointer to custom alloator callbacks, default to `nullptr`
* Pointer to variable; stores the handle to new object


## Validation Layers

In vulkan, validation layers are helpful for debugging. It provides debugging capabilities that can make developing vulkan code easier.

In the code you will see validation layers be initialized as the following. These can be toggle between debug and release builds.

```C++
const std::vector<const char*> validation_layers = {
    "VK_LAYER_KHRONOS_validation"
};
```

## Debugging Callback

When creating the `VkInstance`, there is a `debug_callback` which is used for performing debugging statements. This callback is specifically useful for validating instances that have been created through `vkDestroyDebugUtilsMessengerEXT`.

That requires a valid instance handler. The `VkDebugUtilsMessengerCreateInfoEXT` struct requires the same members

`sType` - is a member for specifying what kinds of struct type this vulkan create information is.
`messageSeverity` - a member for specifying message severity of the logs the validation layers will provide you.
`pfnUserCallback` - is the `debug_callback` member that is a proxy functino that will be used for processing the logged validation layers to stderr. 

## Thats it!

There you go! You instantiated your very first vulkan object, which is the instance that instantiates the vulkan API.

This is instantiated inside of a `vk_instance` to simplify handling vulkan objects, with only specifying properties you need to communicate to vulkan.


## Few Last Notes

Something you notice is there is a line that has `operator VkInstance() { return m_instance; }`, this allows to treat the object of `vk_instance` as a literal vulkan object that can be passed to the vulkan API.

Rather then having a getter `get_instance_handler()`, you can pass in the object itself and because C++ has type inference. The vulkan API would infer its type of the object as if its a `VkInstance` type.

