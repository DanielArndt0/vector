# Vector Usage Documentation

This document provides basic examples of the Vector API.

## Initialization

Create a vector with the default initial capacity of five elements:

```cpp
Vector<int> numbers;
```

Specify a different initial capacity:

```cpp
Vector<int> numbers(10);
```

The initial capacity determines the allocated storage, not the number of stored elements.

## Adding Elements

### Push()

Append an element to the vector:

```cpp
Vector<int> numbers;

numbers.Push(10);
numbers.Push(20);
numbers.Push(30);
```

### operator+=

An alternative way to append elements:

```cpp
numbers += 40;
```

## Accessing Elements

### Get()

Retrieve an element by its index:

```cpp
int value = numbers.Get(0);
```

### operator[]

Access or modify an element:

```cpp
numbers[0] = 100;

int value = numbers[0];
```

### getFirst()

Retrieve the first element:

```cpp
int first = numbers.getFirst();
```

### getLast()

Retrieve the last element:

```cpp
int last = numbers.getLast();
```

### Exist()

Check whether an element exists:

```cpp
bool exists = numbers.Exist(20);
```

## Capacity

### getSize()

Return the number of stored elements:

```cpp
std::size_t size = numbers.getSize();
```

### getContainerSize()

Return the currently allocated capacity:

```cpp
std::size_t capacity = numbers.getContainerSize();
```

### isEmpty()

Check whether the vector is empty:

```cpp
if (numbers.isEmpty())
{
    // The vector contains no elements.
}
```

## Removing Elements

### Pop()

Remove the last element:

```cpp
numbers.Pop();
```

### Pop(index)

Remove an element at a specified position:

```cpp
numbers.Pop(1);
```

Both methods return `false` if removal cannot be performed because the vector is empty or the index is invalid.

## Copying Elements

### Copy Constructor

Create an independent copy:

```cpp
Vector<int> original;

original.Push(10);
original.Push(20);

Vector<int> copied(original);
```

### Copy()

Copy the contents of another vector:

```cpp
Vector<int> destination;

destination.Copy(original);
```

### Copy Assignment

```cpp
Vector<int> destination;

destination = original;
```

Copies have independent storage.

## Moving Elements

Transfer ownership of a vector's storage:

```cpp
#include <utility>

Vector<int> original;

original.Push(10);

Vector<int> destination(std::move(original));
```

The destination receives the original storage. The moved-from vector remains valid and empty.

## Swapping Elements

### Swap()

Exchange the contents of two vectors:

```cpp
Vector<int> first;
Vector<int> second;

first.Push(10);
second.Push(20);

first.Swap(second);
```

The operation exchanges the internal storage without copying individual elements.

## Clearing Elements

### Reset()

Remove all elements and restore the initial capacity:

```cpp
numbers.Reset();
```

### Delete()

Release the allocated storage:

```cpp
numbers.Delete();
```

After `Delete()`, the vector is empty and its capacity is zero. New elements can still be inserted with `Push()`.

## Access Validation

The following operations throw `std::out_of_range` when accessing an invalid position:

- `Get()`
- `operator[]`
- `getFirst()`
- `getLast()`

Example:

```cpp
#include <stdexcept>

try
{
    numbers.Get(100);
}
catch (const std::out_of_range&)
{
    // Invalid index.
}
```

## Memory Management

Vector automatically manages its allocated storage.

- Capacity grows when additional storage is required.
- Capacity may shrink after element removal.
- Copy operations create independent storage.
- Move operations transfer storage ownership.
- The destructor releases the allocated memory.

The current implementation requires element types to be default-constructible, copy-assignable, and move-assignable.
