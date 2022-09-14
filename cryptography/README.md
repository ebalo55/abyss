# Cryptography



The cryptography module included in Abyss is based on the awesome [libsodium](https://doc.libsodium.org/) library and provides many tweaks and shortcuts for almost all the sodium functionalities.

### Include in cmake

The cmake inclusion is as easy as possible:\
Start finding the required library component as follows

```cmake
find_package(Abyss COMPONENTS crypto REQUIRED)
```

Then link it to your executable or library

```cmake
# library linking
target_link_libraries(sample_library_name Abyss::Crypto)
target_link_libraries(sample_executable PRIVATE Abyss::Crypto)
```

### Library generation

The library is natively shipped with a [Conan](https://conan.io/) install script to ease the inclusion in new software, all you need to do in order to compile the library is:

* Install the Conan package manager
* Clone the repository\
  `git clone git@github.com:ebalo55/abyss.git`&#x20;
* Run the Conan creation command `conan create .` from within the repository folder.
