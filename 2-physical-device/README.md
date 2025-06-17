# 2 -- Vulkan Physical Device

In this tutorial, we are going to try getting a basic physical device setup working with vulkan. Before we continue to vulkan logical devices, this is the first thing to setup as the logical devices rely on the information we pull from the physical device abstraction.


## Overview

Vulkan uses the concept of a physical device to check what hardware of graphics cards to look for. Including selecting a graphics card that is supported on your current machine. This involves what features does your current GPU support. As that can vary from GPU-to-GPU, as well hardware specifications of your machine.

The process selecting a physical driver, and a lot of tutorials are either outdated or very complex in their designs. This code tutorial aims to be standalone and simpler enough to be able to get the base working that should work for your specific machine.

## Process of Picking Physical Devices

When selecting a physical device in vulkan it would be referred to as, enumeration. Referred through API's such as `vkEnumeratePhysicalDevices`. That can provide you information of your current hardware specifications.


During this selection process, you can also provide checks such as suitability checks, and queue family checks.


## Queue Families

In Vulkan, to draw anything from meshes geometry to textures, to even materials. Queue families are essential for doing drawing operations. There are different types of queues that can originate from different queue families and each family of queues that allows for subsets of commands.

Example some GPU's do not support a transfer queue. Transfer queue's are really good if you need to take a task (command) and do fast data transfer offloading from the CPU to the GPU. If your familiar with compute shaders and their use, its essentially that but from the vulkan-side and their utilization of transfer queues.

During configuring physical devices, that is one of the checks required to see if queue families are supported on your current hardware GPU.


## Vulkan Physical Device Control Flow

The following flow for setting up physical devices are the following:

* enumerate physical devices -- for the count of GPU's devices available
* second enumeration of physical devices -- for the properties to the physical devices and their metadata information.
* Firstly query the queue family count
* Secondly query family metadata information
* Select queue family indices