import os
from conan import ConanFile
from conan.tools.cmake import CMakeToolchain, CMake, cmake_layout, CMakeDeps
from conan.tools.system.package_manager import Apt, Yum, PacMan, Zypper
from conan.tools.scm import Git
from conan.tools.files import copy
import os

class VulkanExample(ConanFile):
    name = "vulkan-examples"
    version = "1.0"
    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeDeps", "CMakeToolchain"

    # Putting all of your build-related dependencies here
    def build_requirements(self):
        self.tool_requires("make/4.4.1")
        self.tool_requires("cmake/3.27.1")
        self.tool_requires("engine3d-cmake-utils/4.0")

    # Putting all of your packages here
    def requirements(self):
      self.requires("glfw/3.4")
      self.requires("spdlog/1.14.1")
      self.requires("glm/1.0.1")
      self.requires("imguidocking/2.0")
      self.requires("vulkan-headers/1.3.290.0")

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def package(self):
        cmake = CMake(self)
        cmake.install()
    
    def layout(self):
        cmake_layout(self)