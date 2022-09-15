# Symmetric message authentication

Message authentication is the tecnique of computing a unique cryptographically secure authentication tag that identifies
a message and ensures that the message was not modified or tampered.\
Abyss makes message authentication as easy as possible, for a deeper understanding of how the 
algorithm works check the libsodium official documentation 
[here](https://doc.libsodium.org/secret-key_cryptography/secret-key_authentication#algorithm-details).

Additionally, Abyss always uses the authenticated version of the encryption algorithms provided by libsodium so that the 
encrypted messages cannot be tampered with without corrupting the whole message.

In this chapter, the following namespace aliasing is considered imported before each sample.

```cpp
using namespace acsa = ac::symmetric::auth;
```

### Signing & verification

Message signature can be computed with `sign(...)` while signature verification can be done using `verify(...)`.\
Note that encryption algorithms are already shipped with message authentication.

```cpp
// Generate key for signature computation and verification
auto key = acsa::make_key();
auto signature = acsa::sign("sample text", key);

// verify the message signature
acsa::verify(signature, "sample text", key); // true
acsa::verify(signature, "sample_text", key); // false
```