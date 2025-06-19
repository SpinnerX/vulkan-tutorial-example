# 2. Vulkan Window

In this tutorial, we are going to be seeing how to create a window using GLFW. If you've used GLFW before, this tutorial will show how to just initialize GLFW and creating a window with GLFW.

This is going to involve a class called `vk_window`, which will be used to handle creation of the GLFW window and the vulkan VkSurface.



# Vulkan Surface

In this tutorial, we create a GLFW window using GLFW's API, `glfwCreateWindow`. Then for vulkan we need to create a vulkan surface, using the `VkSurfaceKHR` handler.

