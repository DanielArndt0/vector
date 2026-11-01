#include "Vector.h"

#include <iostream>

int main()
{
  Vector<int> values(2);
  values.Push(10);
  values += 20;
  values.Push(30);

  std::cout << "Elements: " << values.getSize() << '\n';
  std::cout << "Capacity: " << values.getContainerSize() << '\n';

  values.Pop(1);
  for (Vector<int>::size_type i = 0; i < values.getSize(); ++i)
    std::cout << "values[" << i << "] = " << values[i] << '\n';

  Vector<int> copy(values);
  copy.Push(40);
  std::cout << "Copy last: " << copy.getLast() << '\n';
  std::cout << "Original last: " << values.getLast() << '\n';
}
