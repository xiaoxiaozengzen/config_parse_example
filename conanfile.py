from conan import ConanFile
from conan.tools.env import VirtualRunEnv, VirtualBuildEnv
from conan.tools.cmake import CMakeDeps, CMakeToolchain

required_conan_version = ">=1.53.0"


class ConfigParseConan(ConanFile):
    name = "config_parse"
    version = "dev"
    settings = "os", "compiler", "build_type", "arch"

    @property
    def _min_cppstd(self):
        return 14

    def requirements(self):
        self.requires("nlohmann_json/3.11.2")
        self.requires("yaml-cpp/0.8.0")
        self.requires("toml11/3.7.0")
        self.requires("tinyxml2/9.0.0")        

    def generate(self):
        tc = CMakeToolchain(self)
        tc.cache_variables["CMAKE_POLICY_DEFAULT_CMP0077"] = "NEW"
        tc.generate()
        tc = CMakeDeps(self)
        tc.generate()
        tc = VirtualRunEnv(self)
        tc.generate()
        tc = VirtualBuildEnv(self)
        tc.generate(scope="build")
