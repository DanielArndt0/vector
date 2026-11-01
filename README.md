# Vector

A lightweight, header-only dynamic array implementation for C++11 and later.

Vector provides dynamic storage management, indexed element access, automatic capacity adjustment, and copy and move operations.

## Requirements

- C++11 or later
- CMake 3.16 or later for project integration

## Usage

```cpp
#include "Vector.h"

int main()
{
    Vector<int> numbers;

    numbers.Push(10);
    numbers.Push(20);
    numbers.Push(30);

    numbers.Pop(1);

    return numbers.getLast() == 30 ? 0 : 1;
}
```

For additional examples and API documentation, see [Usage Documentation](docs/usage.md).

## Manual Integration

Download [Vector.h](https://github.com/DanielArndt0/Vector/blob/main/include/Vector.h) from the repository and add it to your project's include directory.

Include the header using `#include "Vector.h"`. No additional dependencies or separate compilation are required.

## CMake Integration

Vector can be integrated directly from GitHub using CMake's `FetchContent` module.

Add the following to your project's `CMakeLists.txt`:

```cmake
include(FetchContent)

FetchContent_Declare(
    Vector
    GIT_REPOSITORY https://github.com/DanielArndt0/Vector.git
    GIT_TAG 1.0.0
)

FetchContent_MakeAvailable(Vector)

target_link_libraries(my_target PRIVATE Vector::Vector)
```

Replace `my_target` with your application's CMake target.

CMake automatically retrieves the specified version and configures the required include directories. No separately compiled library is needed.

## Compatibility

Vector requires C++11 or later. Its implementation uses dynamic allocation and standard C++ exceptions.

## Disclaimer

Vector is a lightweight C++ library developed for educational purposes, focusing on dynamic memory management and data structure implementation.

It is intended for learning and experimentation and is not designed to replace `std::vector` or other standard C++ containers.
