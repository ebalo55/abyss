# Symmetric encryption

Symmetric encryption uses the same key for both the operation of encoding and decoding.\
Abyss make data encryption using libsodium algorithms as easy as possible, for a deeper understanding of how the 
algorithm works check the libsodium official documentation 
[here](https://doc.libsodium.org/secret-key\_cryptography/secretbox#algorithm-details).

Additionally, Abyss always uses the authenticated version of the encryption algorithms provided by libsodium so that the 
encrypted messages cannot be tampered with without corrupting the whole message.

In this chapter, the following namespace aliasing is considered imported before each sample.

```cpp
using namespace acsm = ac::symmetric::message;
using namespace ace = ac::encode;
```

### Algorithm

The algorithms used are the ones defaulting in libsodium 1.0.18.

* Encryption: XSalsa20 stream cipher
* Authentication: Poly1305 MAC

### Encryption

The encryption of a message can be done with two methods: `encrypt(...)` and `encrypt_detached(...)`.\
Both versions have many overloads in order to allow for full and easy flexibility in the construction of the encrypted 
text.

What makes the  `_detached` method different from the standard `encrypt` is that the authentication tag is not 
automatically stored within the message, it is instead stored in a separate attribute of the returned structure.

#### Resulting struct

Abyss provides encryption return types as structures, this is done in order to allow anyone to use it without any 
difficulty.

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

Some type alias are also defined in order to provide a more expressive syntax in method parameters.\
Is always suggested to use type aliases when developing your code for easier understanding.
```cpp
typedef struct encryption_data encryption_data_t;
typedef struct encryption_data encrypted_data_t;
typedef struct encryption_data decryption_data_t;

typedef struct encryption_data_detached encrypted_data_detached_t;
typedef struct encryption_data_detached decryption_data_detached_t;
```

### Combined mode samples
Combined mode uses the `encrypt(...)` method and stores the authentication tag with the encrypted message.
```cpp
// Encrypt a message with a random key and a random nonce
auto encrypted_0 = acsm::encrypt("test");
encrypted_0.key;      // contains the random key used
encrypted_0.nonce;    // contains the random nonce used
encrypted_0.message;  // contains a binary representation of the encrypted message

// In order to print or save encrypted messages or data like key and nonce
// you should consider the usage of some encoding method such as base64.
// Always remember that in order to allow the decryption of the text you need all the data 
// contained in the resulting structure.
cout << ace::base64(encrypted_0.key) << endl
     << ace::base64(encrypted_0.nonce) << endl
     << ace::base64(encrypted_0.message) << endl;


// Generate a key & encrypt with it
auto key_1 = acsm::make_key();
auto encrypted_1 = acsm::encrypt("test", key_1);

// Generate a key & nonce and use them in encryption
auto key_2 = acsm::make_key();
auto nonce_2 = acsm::make_nonce();
auto encrypted_2 = acsm::encrypt("test", key_2, nonce_2);

// Another way of calling the encryption function is via the encryption_data_t struct.
// This calling method will result in a new structure returned with the message encrypted
auto encrypted_3 = acsm::encrypt({
    .message = "test",
    .key = acsm::make_key(),
    .nonce = acsm::make_nonce(),
});
```

### Detached mode samples
Detached mode uses the `encrypt_detached(...)` method and stores the authentication tag separately from the message.
```cpp
// Encrypt a message with a random key and a random nonce
auto encrypted_0 = acsm::encrypt_detached("test");
encrypted_0.key;                 // contains the random key used
encrypted_0.nonce;               // contains the random nonce used
encrypted_0.message;             // contains a binary representation of the encrypted message
encrypted_0.authentication_tag;  // contains a binary representation of the authentication tag

// In order to print or save encrypted messages or data like key and nonce
// you should consider the usage of some encoding method such as base64.
// Always remember that in order to allow the decryption of the text you need all the data 
// contained in the resulting structure.
cout << ace::base64(encrypted_0.key) << endl
     << ace::base64(encrypted_0.nonce) << endl
     << ace::base64(encrypted_0.authentication_tag) << endl
     << ace::base64(encrypted_0.message) << endl;


// Generate a key & encrypt with it
auto key_1 = acsm::make_key();
auto encrypted_1 = acsm::encrypt_detached("test", key_1);

// Generate a key & nonce and use them in encryption
auto key_2 = acsm::make_key();
auto nonce_2 = acsm::make_nonce();
auto encrypted_2 = acsm::encrypt_detached("test", key_2, nonce_2);

// Another way of calling the encryption function is via the encryption_data_t struct.
// This calling method will result in a new structure returned with the message encrypted
auto encrypted_3 = acsm::encrypt_detached({
    .message = "test",
    .key = acsm::make_key(),
    .nonce = acsm::make_nonce(),
});
```