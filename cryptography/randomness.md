# Randomness

Randomness in cryptography is crucial and libsodium does it extremely well.

In this chapter, the following namespace aliasing is considered imported before each sample.

```cpp
using namespace acr = ac::random;
```

### Random integer

Random integer generation is restricted to 32bit unsigned integer but can be easily extended using the low-level libsodium API.

```cpp
acr::generate(); // random number between 0 and 4.294.967.295 (included)
acr::generate(10); // random number between 0 and 10 (excluded)

// random number between 0 and 5 (excluded)
// uniform distribution of probability is guaranteed meaning the probability of 
// extraction is as follow:
//  - 0: 20%
//  - 1: 20%
//  - 2: 20%
//  - 3: 20%
//  - 4: 20%
acr::generate_uniform(5); 

// generate a random double
double container = 0;
acr::generate(&container, sizeof(container));
// container is now a random double

// this last generation method can be used to randomize almost everything once its 
// size is known
long long int value_0 = 0;
int8_t value_1 = 0;
int16_t value_2 = 0;
int value_3[] = [0, 0, 0, 0]:
acr::generate(&value_0, sizeof(value_0));
acr::generate(&value_1, sizeof(value_1));
acr::generate(&value_2, sizeof(value_2));
acr::generate(&value_3, sizeof(value_3));
```

### Random string

Random strings can be generated via the `generate_buffer(...)` method

```cpp
acr::generate_buffer(10); // 10 chars random string

std::string container;
acr::generate_buffer(container, 10);
// now container is a 10 chars random string
```
