#! /usr/bin/env python
# -*- coding: utf-8 -*-

from conan import ConanFile
from conan.tools.cmake import CMake


class ConanRecipt(ConanFile):
    name = 'CPPCraft'

    settings = [
        'os',
        "compiler",
        'arch',
        'build_type',
    ]

    generators = [
        "CMakeToolchain", "CMakeDeps"
    ]

    def requirements(self) -> None:
        self.requires('glew/2.2.0')
        self.requires('glfw/3.3.8')
        self.requires('libpng/1.6.40')
        self.requires('glm/cci.20230113')

    def build(self) -> None:
        cmake: CMake = CMake(self)

        cmake.configure()
        cmake.build()