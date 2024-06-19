from conan import ConanFile
from conan.tools.cmake import CMakeToolchain, CMake, cmake_layout, CMakeDeps


class opengl_chernoRecipe(ConanFile):
    name = "opengl-cherno"
    version = "1.0"
    package_type = "application"

    # Optional metadata
    license = "MIT"
    author = "Amir Nourinia"
    url = "amirnn/Opengl-Cherno"
    description = "OpenGL "
    topics = ("OpenGL", "Graphics", "Playground")

    # Binary configuration
    settings = "os", "compiler", "build_type", "arch"

    # Sources are located in the same place as this recipe, copy them to the recipe
    exports_sources = "CMakeLists.txt", "src/*"

    def layout(self):
        cmake_layout(self, src_folder="..", build_folder="../build")

    def generate(self):
        deps = CMakeDeps(self)
        deps.generate()
        tc = CMakeToolchain(self)
        tc.user_presets_path = "ConanPresets.json"
        tc.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def package(self):
        cmake = CMake(self)
        cmake.install()

    def requirements(self):
        self.requires("boost/[~1]")
        self.requires("glfw/[~3]")
        self.requires("glm/cci.20230113")
        self.requires("eigen/[~3]")
        # self.requires("opencv/[~4]")

    
