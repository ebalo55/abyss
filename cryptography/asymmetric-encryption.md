# Asymmetric encryption

Asymmetric encryption grants message's security by using a couple of related key namely a _secret key_ and a _public key_.\
Public keys as the name suggests can be shared safely with other parties while secret keys should be kept secret.\
Asymmetric encryption can also be used to verify the sender of a message as a message encrypted using a given public key 
can only be decrypted using its associated secret key and vice versa.

In this chapter, the following namespace aliasing is considered imported before each sample.

```cpp
using namespace acam = ac::asymmetric::message;
using namespace ace = ac::encode;
```

### Encryption

The encryption of a message can be done with two methods: `encrypt(...)` and `encrypt_detached(...)`.\
Both versions have many overloads in order to allow for full and easy flexibility in the construction of the encrypted
text.

What makes the `_detached` method different from the standard `encrypt` is that the authentication tag is not
automatically stored within the message, it is instead stored in a separate attribute of the returned structure.

### Resulting struct

Abyss provides encryption return types as structures, this is done in order to allow anyone to use it without any
difficulty.

```cpp
struct keypair {
    std::string public_key;
    std::string secret_key;
};

struct encryption_data {
    std::string message;
    std::string nonce;
    keypair_t keypair;
};

struct encryption_data_detached {
    std::string authentication_tag;
    std::string message;
    std::string nonce;
    keypair_t keypair;
};
```

Some type alias are also defined in order to provide a more expressive syntax in method parameters.\
Is always suggested to use type aliases when developing your code for easier understanding.

```cpp
typedef struct keypair keypair_t;
typedef struct keypair transitional_keypair_t;

typedef struct encryption_data encrypted_data_t;
typedef struct encryption_data decryption_data_t;

typedef struct encryption_data_detached encrypted_data_detached_t;
typedef struct encryption_data_detached decryption_data_detached_t;
```

#### Combined mode

Combined mode uses the `encrypt(...)` method and stores the authentication tag with the encrypted message.

```cpp
```

#### Detached mode

Detached mode uses the `encrypt_detached(...)` method and stores the authentication tag separately from the message.

```cpp
```