# Symmetric encryption

Symmetric encryption uses the same key for both the operation of encoding and decoding.\
Abyss make data encryption using libsodium algorithms as easy as possible, for a deeper understanding of how the algorithm works check the libsodium official documentation [here](https://doc.libsodium.org/secret-key\_cryptography/secretbox#algorithm-details).

Additionally, Abyss always uses the authenticated version of the encryption algorithms provided by libsodium so that the encrypted messages cannot be tampered with without corrupting the whole message.

### Algorithm

The algorithms used are the ones defaulting in libsodium 1.0.18.

* Encryption: XSalsa20 stream cipher
* Authentication: Poly1305 MAC

### Encryption

The encryption of a message can be done with two methods: `encrypt(...)` and `encrypt_detached(...)`.\
Both versions have many overloads in order to allow for full and easy flexibility in the construction of the encrypted text.

What makes the  `_detached` method different from the standard `encrypt` is that the authentication tag is not automatically stored within the message, it is instead stored in a separate attribute of the returned structure.

#### Resulting struct

```cpp
struct encryption_data {
    std::string message;
    std::string key;
    std::string nonce;
};

struct encryption_data_detached {
    std::string authentication_tag;
    std::string message;
    std::string key;
    std::string nonce;
};
```
