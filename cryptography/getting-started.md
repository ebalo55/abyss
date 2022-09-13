# Getting started

Cryptography is always difficult and heavily depends on random sources but libsodium tries to ease the process of secure initialization and Abyss follows.\
In order to initialize the secure random sources before ever using the crypto library, you should initialize it using the easy-to-remember yet powerful init method

```cpp
int main() {
    abyss::crypto::init();
    
    // do some magic here
}
```

The namespace for every cryptography-related method or function is always `abyss::crypto` in the following chapters we'll assume you have used that namespace and alias it as follow

```cpp
using namespace ac = abyss::crypto;
```
