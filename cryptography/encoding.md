# Encoding

Abyss provides quick and easy encoding and decoding capabilities to and from:

* binary&#x20;
* hexadecimal
* base 64

### Hex encoding & decoding

Hex encoding and decoding can be done easily via the `hex(...)` and `hex_to_plain(...)` methods in the `abyss::crypto::encode` namespace

```cpp
int main() {
    cout << ac::encode::hex("test") << endl;                // 74657374
    cout << ac::encode::hex_to_plain("74657374") << endl;   // test
}
```

The generic encoding utilities `encode(...)` and `decode(...)` can also be used as follow

```cpp
int main() {
    cout << ac::encode::encode("test", encodings::_hex) << endl;        // 74657374
    cout << ac::encode::decode("74657374", encodings::_hex) << endl;   // test
}
```

### Base64 encoding & decoding

Base64 encoding and decoding can be done easily via the `base64(...)` and `base64_to_plain(...)` methods in the `abyss::crypto::encode` namespace

```cpp
int main() {
    cout << ac::encode::base64("test") << endl;                // dGVzdA==
    cout << ac::encode::base64_to_plain("dGVzdA==") << endl;   // test
}
```

The generic encoding utilities `encode(...)` and `decode(...)` can also be used as follow

```cpp
int main() {
    cout << ac::encode::encode("test", encodings::_base64) << endl;       // dGVzdA==
    cout << ac::encode::decode("74657374", encodings::_base64) << endl;   // test
}
```

#### variants

Base64 encoding comes in four (4) variants:

* Classic (default)
* Without padding
* Url safe
* Url safe without padding

Each variant can be easily selected by providing an additional parameter to the encode/decode method.

```cpp
// no padding variant
ac::encode::base64("test", base64_variants::_no_padding); 
// or
ac::encode::encode("test", encodings::_base64, base64_variants::_no_padding); 


// url safe variant
ac::encode::base64("test", base64_variants::_url_safe);  
// or
ac::encode::encode("test", encodings::_base64, base64_variants::_url_safe);  


// url safe w/o padding variant
ac::encode::base64("test", base64_variants::_url_safe_no_padding); 
// or
ac::encode::encode("test", encodings::_base64, base64_variants::_url_safe_no_padding);


// classic - default
ac::encode::base64("test", base64_variants::_classic);    
// or
ac::encode::encode("test", encodings::_base64, base64_variants::_classic); 


// no variant provided falls back to classic
ac::encode::base64("test"); 
```

The same logic applies also for the decoding, an exception will be thrown if a two different variants are used for encoding & decoding

```cpp
// no padding variant
ac::encode::base64_to_plain("dGVzdA", base64_variants::_no_padding); 
// or
ac::encode::decode("dGVzdA", encodings::_base64, base64_variants::_no_padding); 

// url safe variant
ac::encode::base64_to_plain("dGVzdA==", base64_variants::_url_safe);  
// or
ac::encode::decode("dGVzdA", encodings::_base64, base64_variants::_url_safe);   

// url safe w/o padding variant
ac::encode::base64_to_plain("dGVzdA", base64_variants::_url_safe_no_padding); 
// or
ac::encode::decode("dGVzdA", encodings::_base64, base64_variants::_url_safe_no_padding); 

// classic - default
ac::encode::base64_to_plain("dGVzdA==", base64_variants::_classic);   
// or
ac::encode::decode("dGVzdA", encodings::_base64, base64_variants::_classic);   

// no variant provided falls back to classic
ac::encode::base64_to_plain("dGVzdA=="); 

// ERROR: trying to decode no-padding variant with classic variant
ac::encode::base64_to_plain("dGVzdA"); 
```
