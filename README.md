# float128

**Header-only C++ constexpr `float128` implementation**

`float128` is a **constexpr-capable, header-only C++17 library** that provides a 128-bit floating-point type and related math functionality. It was originally developed as part of the [NeuroTensor](https://github.com/moldenha/NeuroTensor.git) framework and extracted to be standalone for reuse.

## Features

-   **128-bit floating-point type** (`nt::float128_t`)
    
-   **Header-only** — no linking required
    
-   Designed for **C++17 and newer**
    
-   Implements core math operations in `constexpr` where practical
    
-   Easy to embed in other projects
    

## Usage

Include the library in your project:

```cpp
#include "float128.h"
```

Use the `nt::float128_t` type just like a regular floating-point type:

```cpp
nt::float128_t a = 1.23456789012345678901234567890_f128;
```

You can perform arithmetic and use provided math helpers (see examples in `test.cpp`).

## 🧪 Example

Here’s a simple usage example from `test.cpp`:

```cpp
#include "float128.h"
#include <iostream>

int main() {
    constexpr nt::float128_t x = 2.0_f128;
    constexpr nt::float128_t y = 3.0_f128;
    constexpr nt::float128_t z = x + y;
    std::cout << "z = " << z << "\n";
    return 0;
}
```

> *Note:* The `_f128` suffix denotes a literal for a 128-bit float.

## Contents

-   `float128.h` — Main header with type definition and operations
    
-   `test.cpp` — Example usage and basic tests
    
-   `src/` — source code
    

## Requirements

-   C++17-compatible compiler
    
-   Works with major compilers (GCC, Clang, MSVC)
    

> Compilers may differ in native support for `__float128` or `_Float128`. This implementation handles those differences internally and aims for broad portability.

## Building & Testing

You can compile the test program like this:

```sh
g++ -std=c++17 test.cpp -o test
./test
```

or with Clang/MSVC as appropriate for your toolchain.

## Notes

-   This library focuses on **constexpr and header-only use** rather than performance tuning.
    
-   Some math functions may fall back to slower C++ computations depending on platform support.
    


