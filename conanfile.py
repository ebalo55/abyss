from conans import ConanFile, CMake, tools
from conans.model.options import Options
from conan.tools.cmake import CMakeToolchain


class ConanAbyss(ConanFile):
    name = "abyss"
    version = "0.1.1"
    license = "MIT"
    url = "https://github.com/ebalo55/abyss"
    description = "Abyss fullstack framework for C++"

    # Binary configuration
    settings = "os", "compiler", "build_type", "arch"
    options: Options = {
        "shared": [True, False],
        "abyss_logger_includes_qt_sink": [True, False],
        "abyss_logger_includes_systemd_sink": [True, False],
        "abyss_logger_includes_mongo_db_sink": [True, False],
    }
    default_options = {
        "shared": False,
        "*:shared": False,
        "fmt:header_only": True,
        "spdlog:header_only": True,
        "abyss_logger_includes_qt_sink": False,
        "abyss_logger_includes_systemd_sink": False,
        "abyss_logger_includes_mongo_db_sink": False,

    }
    generators = "cmake", "cmake_find_package", "cmake_find_package_multi"

    # Sources are located in the same place as this recipe, copy them to the recipe
    exports_sources = "CMakeLists.txt", "src/*", "include/*", "cmake/*"
    requires = "spdlog/1.10.0", "fmt/8.1.1"

    _cmake = None

    def imports(self):
        if self.options.shared:
            self.copy("*.dll", "", "bin")
            self.copy("*.dylib*", "", "lib")

    def requirements(self):
        if tools.Version(self.version) >= "0.1.0":
            self.requires("spdlog/1.10.0")
            self.requires("fmt/8.1.1")

    def generate(self):
        tc = CMakeToolchain(self)
        # customize toolchain "tc"
        tc.generate()

    def configure_cmake(self):
        if self._cmake is not None:
            return self._cmake

        # init a new cmake instance
        self._cmake = CMake(self)
        if self.options.abyss_logger_includes_qt_sink:
            self._cmake.definitions["ABYSS_LOGGER_INCLUDES_QT_SINK"] = True
        if self.options.abyss_logger_includes_systemd_sink:
            self._cmake.definitions["ABYSS_LOGGER_INCLUDES_SYSTEMD_SINK"] = True
        if self.options.abyss_logger_includes_mongo_db_sink:
            self._cmake.definitions["ABYSS_LOGGER_INCLUDES_MONGO_DB_SINK"] = True

        return self._cmake

    def build(self):
        self.configure_cmake()
        self._cmake.configure()
        self._cmake.build()
        self._cmake.install()

    def package(self):
        self.copy("*.h", dst="include", src="src")
        self.copy("*.lib", dst="lib", keep_path=False)
        self.copy("*.dll", dst="bin", keep_path=False)
        self.copy("*.dylib*", dst="lib", keep_path=False)
        self.copy("*.so", dst="lib", keep_path=False)
        self.copy("*.a", dst="lib", keep_path=False)

    def package_info(self):
        if not self.settings.os == "Windows":
            self.cpp_info.libs = [
                "libLogger.a"
            ] if not self.options.shared else [
                "libLogger.so"
            ]
