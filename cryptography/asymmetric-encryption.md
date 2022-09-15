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
// Generate keypairs for sender and receiver, usually the sender keypair is fully known while only the public key of
// the receiver keypair is known, in this example we generate both the full keypair here
auto sender_kp = acam::make_keypair();
auto receiver_kp = acam::make_keypair();

auto encrypted_message_0 = acam::encrypt("test", sender_kp, receiver_kp);
encrypted_message_0.message;              // contains the binary representation of the encrypted message
encrypted_message_0.nonce;                // contains the randomly generated nonce

// The keypair object contains the shared keypair (alias transitional), the public key is the receiver public key
// while the secret key is the sender secret key.
// NOTE: This object is not natively safe to share or send via network, you should always at least strip the secret key
//       field
encrypted_message_0.keypair.public_key;   // contains the public key of the receiver
encrypted_message_0.keypair.secret_key;   // contains the secret key of the sender

// Encryption can also be achieved by the prior computation of the shared keypair
auto shared_keypair = acam::make_encryption_shared_keypair(sender_kp, receiver_kp);
auto encrypted_message_1 = acam::encrypt("test", shared_keypair);

// If you don't like structured method calls you can always use the string overloads.
// Note that using the string method call is more error-prone than using the structured methods.
auto sender_sk = "...";
auto receiver_pk = "***";
auto encrypted_message_2 = acam::encrypt("test", sender_sk, receiver_pk);

// Note that exists also overloads including a provided nonce as a parameter
```

#### Detached mode

Detached mode uses the `encrypt_detached(...)` method and stores the authentication tag separately from the message.

```cpp
// Generate keypairs for sender and receiver, usually the sender keypair is fully known while only the public key of
// the receiver keypair is known, in this example we generate both the full keypair here
auto sender_kp = acam::make_keypair();
auto receiver_kp = acam::make_keypair();

auto encrypted_message_0 = acam::encrypt_detached("test", sender_kp, receiver_kp);
encrypted_message_0.message;              // contains the binary representation of the encrypted message
encrypted_message_0.nonce;                // contains the randomly generated nonce
encrypted_message_0.authentication_tag;   // contains the message authentication tag

// The keypair object contains the shared keypair (alias transitional), the public key is the receiver public key
// while the secret key is the sender secret key.
// NOTE: This object is not natively safe to share or send via network, you should always at least strip the secret key
//       field
encrypted_message_0.keypair.public_key;   // contains the public key of the receiver
encrypted_message_0.keypair.secret_key;   // contains the secret key of the sender

// Encryption can also be achieved by the prior computation of the shared keypair
auto shared_keypair = acam::make_encryption_shared_keypair(sender_kp, receiver_kp);
auto encrypted_message_1 = acam::encrypt_detached("test", shared_keypair);

// If you don't like structured method calls you can always use the string overloads.
// Note that using the string method call is more error-prone than using the structured methods.
auto sender_sk = "...";
auto receiver_pk = "***";
auto encrypted_message_2 = acam::encrypt_detached("test", sender_sk, receiver_pk);

// Note that exists also overloads including a provided nonce as a parameter
```

### Decryption
The encryption of a message can be done with two methods: `decrypt(...)` and `decrypt_detached(...)`.\
Both versions have some overloads in order to allow for additional flexibility in the decryption of messages.\
Resulting structs of the decryption are defined as aliases of the one used in encryption, refer to the definition of
encryption structs [here](#Resulting struct).

```cpp
auto sender_kp = acam::make_keypair();
auto receiver_kp = acam::make_keypair();

auto encrypted = acam::encrypt("test", sender_kp, receiver_kp);
auto encrypted_detached = acam::encrypt_detached("test", sender_kp, receiver_kp);

// decrypt a compact encrypted message via its struct definition.
// NOTE: in this case decoding is achieved via receiver's public key and sender's secret, in a realworld scenario
//       the provided object will contain the sender's public key and the receiver's secret one instead.
acsm::decrypt(encrypted); // test
// or
// NOTE: in this case decoding is achieved via receiver's public key and sender's secret, in a realworld scenario
//       the provided object will contain the sender's public key and the receiver's secret one instead.
acsm::decrypt(encrypted.message, encrypted.nonce, encrypted.keypair); // test
// or
acsm::decrypt(encrypted.message, encrypted.nonce, sender_kp.public_key, receiver_kp.secret_key); // test


// decrypt a detached encrypted message via its struct definition
// NOTE: in this case decoding is achieved via receiver's public key and sender's secret, in a realworld scenario
//       the provided object will contain the sender's public key and the receiver's secret one instead.
acsm::decrypt_detached(encrypted_detached); // test
// or 
// NOTE: in this case decoding is achieved via receiver's public key and sender's secret, in a realworld scenario
//       the provided object will contain the sender's public key and the receiver's secret one instead.
acsm::decrypt_detached(
        encrypted_detached.authentication_tag, 
        encrypted_detached.message, 
        encrypted_detached.nonce
        encrypted_detached.keypair
); // test
// or
acsm::decrypt_detached(
        encrypted_detached.authentication_tag,
        encrypted_detached.message, 
        encrypted_detached.nonce, 
        sender_kp.public_key, 
        receiver_kp.secret_key
); // test
```