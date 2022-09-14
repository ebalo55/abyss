# Symmetric stream

Symmetric encryption is awesome for messages or for unrelated data but if a message start becoming larger and larger,
let's say 1Gb loading it all in memory and encrypting it using standard API can become a heavy task taking more than
1Gb of memory.\
Streaming mode allows for the reading and encryption of a set of related messages without any need to load everything
in memory all at once.\
For a full explanation of how the encryption algorithm works refer to the
[official Libsodium documentation](https://doc.libsodium.org/secret-key_cryptography/secretstream#algorithm).

In this chapter, the following namespace aliasing is considered imported before each sample.

```cpp
using namespace acs = ac::symmetric;
using namespace acss = acs::stream;
using namespace ace = ac::encode;
```

### Stream tags

Each stream chunk can be completed with an additional tag stating its type or the operation to run once the chunk
encryption
is completed.\
Tags are defined in the `symmetric_stream_tag` enum under the `abyss::crypto::symmetric` namespace.

```cpp
enum symmetric_stream_tag {
    _message = crypto_secretstream_xchacha20poly1305_TAG_MESSAGE,
    _stream_end = crypto_secretstream_xchacha20poly1305_TAG_FINAL,
    _message_end = crypto_secretstream_xchacha20poly1305_TAG_PUSH,
    _rekey = crypto_secretstream_xchacha20poly1305_TAG_REKEY
};
```

Tags are defined as follows:

* `_message`: Used to state that a chunk is simply a message, followed by other messages, no other operation are needed
  once the encryption is completed.
* `_message_end`: Used to state that a message is completed and a new one will start with the next chunk.
* `_rekey`: Used to state that a forced rekey is required at the end of the current message.
  New keys are automatically used for the encryption of following chunks.
* `_stream_end`: States the end of the stream, no other messages will be received, the stream is closed.

### Encryption

All encryption operation gets done via a `symmetric_stream` object containing all the data of the current stream, this
means that multiple encryption (or decryption) stream can be executed simultaneously using a thread pool or parallel
processing.\
The initialization of the object is guided via the `make_encryption_stream(...)` method.

```cpp
// Create an encryption key, key must always be defined and stored before differently from symmetric message encryption
// that can automatically generate a key on the fly for each message and echoes it back once the encryption is completed
auto encryption_key = acss::makeEncryptionKey();
auto encryption_stream = acss::makeEncryptionStream(encryption_key);

// The stream encryption always computes an header, the header **MUST** be sent (or stored) before all the other messages
// as it is required for the decryption
auto header = encryption_stream->header();

std::string m1 = "Lorem ipsum dolor sit amet, ",
m2 = "consectetur adipiscing elit. ",
m3 = "Proin aliquam arcu massa, vel pharetra nisl congue sed.",
chunk_1, chunk_2, chunk_3, chunk_4, chunk_5;

// Encrypts a message with the `_message` tag
chunk_1 = encryption_stream->write(m1);
// Encrypts the second message with the `_rekey` tag
chunk_2 = encryption_stream->write(m2, acs::symmetric_stream_tag::_rekey);

// Stream and message closing can be done in two different ways:
// Encrypting the last chunk and then sending an empty message with the appropriate method.
chunk_3 = encryption_stream->write(m3);
chunk_4 = encryption_stream->closeMessage(); // equal to write("", acs::symmetric_stream_tag::_message_end)
// Or including the stream/message closing tag in the last message.
chunk_5 = encryption_stream->write(m3, acs::symmetric_stream_tag::_stream_end);


cout << ace::base64(header) << endl
     << ace::base64(chunk_1) << endl
     << ace::base64(chunk_2) << endl
     << ace::base64(chunk_3) << endl
     << ace::base64(chunk_4) << endl
     << ace::base64(chunk_5) << endl;
```

### Decryption

The decryption works almost the same as the encryption; initialization of the object is guided via the
`make_decryption_stream(...)` method.

```cpp
// Messages received in some way from the previous code-block
std::vector<std::string> messages = {
    chunk_1,
    chunk_2,
    chunk_3,
    chunk_4,
    chunk_5
};

// Initialize the decryption stream with the header resulting from the encryption and the encryption key used
auto decryption_stream = symmetric_stream::makeDecryptionStream(header, encryption_key);

for(auto msg : messages) {
    // Decrypt the message chunk and return it, if an error occurs the decryption stops and cannot be recovered.
    // It is not necessary to read until the stream end to find errors or possible tampering.
    auto plain = decryption_stream->write(msg);
    
    // always check the tag attached to the decoded message to trace message ending or stream closure
    switch(decryption_stream->lastTag()) {
        default:
            cout << "message decoded: " << plain << endl;
            break;
        case symmetric_stream_tag::_message_end:
            cout << "message decoding completed, last chunk: " << plain << endl;
            break;
        case symmetric_stream_tag::_stream_end:
            cout << "stream ended, last chunk: " << plain << endl;
            break;
    }
}
```