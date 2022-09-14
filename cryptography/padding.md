# Padding

In cryptography knowing the exact length of a message can become an issue, especially in critical appliances.\
Padding is the technique of hiding the exact message length rounding it to a defined size (or multiple of a size).

In Abyss padding and unpadding can be achieved easily via `pad(...)` and `unpad(...)` additionally, some common use pre-made helpers are defined to help you pad your messages to 4, 8, 16, 32 or 64 characters.

```cpp
using namespace acp = ac::pad;

acp::pad("test", 8); // test\0\0\0\0
acp::unpad("test\0\0\0\0", 8); // test

acp::pad("test", 8) == acp::pad_8("test"); // true
```
