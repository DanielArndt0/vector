#pragma once

#include <cstddef>
#include <limits>
#include <stdexcept>
#include <utility>

template <typename T>
class Vector
{
public:
  typedef std::size_t size_type;

  explicit Vector(size_type bufferReserve = 5)
      : m_buffer_size(bufferReserve),
        m_data_amount(0),
        m_buff_preinit(bufferReserve),
        m_data_struct(bufferReserve ? new T[bufferReserve] : nullptr)
  {
  }

  Vector(const Vector &other)
      : m_buffer_size(other.m_buffer_size),
        m_data_amount(0),
        m_buff_preinit(other.m_buff_preinit),
        m_data_struct(other.m_buffer_size ? new T[other.m_buffer_size] : nullptr)
  {
    try
    {
      for (; m_data_amount < other.m_data_amount; ++m_data_amount)
        m_data_struct[m_data_amount] = other.m_data_struct[m_data_amount];
    }
    catch (...)
    {
      delete[] m_data_struct;
      throw;
    }
  }

  Vector(Vector &&other) noexcept
      : m_buffer_size(other.m_buffer_size),
        m_data_amount(other.m_data_amount),
        m_buff_preinit(other.m_buff_preinit),
        m_data_struct(other.m_data_struct)
  {
    other.m_buffer_size = 0;
    other.m_data_amount = 0;
    other.m_buff_preinit = 0;
    other.m_data_struct = nullptr;
  }

  ~Vector() { delete[] m_data_struct; }

  Vector &operator=(const Vector &other)
  {
    if (this != &other)
    {
      Vector copy(other);
      Swap(copy);
    }
    return *this;
  }

  Vector &operator=(Vector &&other) noexcept
  {
    if (this != &other)
    {
      delete[] m_data_struct;
      m_buffer_size = other.m_buffer_size;
      m_data_amount = other.m_data_amount;
      m_buff_preinit = other.m_buff_preinit;
      m_data_struct = other.m_data_struct;

      other.m_buffer_size = 0;
      other.m_data_amount = 0;
      other.m_buff_preinit = 0;
      other.m_data_struct = nullptr;
    }
    return *this;
  }

  void operator+=(T data) { Push(std::move(data)); }

  T &operator[](size_type pos) { return Get(pos); }
  const T &operator[](size_type pos) const { return Get(pos); }

  size_type getSize() const noexcept { return m_data_amount; }
  size_type getContainerSize() const noexcept { return m_buffer_size; }
  bool isEmpty() const noexcept { return m_data_amount == 0; }

  T &getFirst() { return Get(0); }
  const T &getFirst() const { return Get(0); }

  T &getLast()
  {
    if (isEmpty())
      throw std::out_of_range("Vector is empty");
    return m_data_struct[m_data_amount - 1];
  }

  const T &getLast() const
  {
    if (isEmpty())
      throw std::out_of_range("Vector is empty");
    return m_data_struct[m_data_amount - 1];
  }

  bool Exist(const T &data) const
  {
    for (size_type i = 0; i < m_data_amount; ++i)
      if (m_data_struct[i] == data)
        return true;
    return false;
  }

  T &Get(size_type pos)
  {
    if (pos >= m_data_amount)
      throw std::out_of_range("Vector index out of range");
    return m_data_struct[pos];
  }

  const T &Get(size_type pos) const
  {
    if (pos >= m_data_amount)
      throw std::out_of_range("Vector index out of range");
    return m_data_struct[pos];
  }

  bool Push(T data)
  {
    if (m_data_amount == m_buffer_size)
      grow();

    m_data_struct[m_data_amount] = std::move(data);
    ++m_data_amount;
    return true;
  }

  bool Pop()
  {
    if (isEmpty())
      return false;
    return Pop(m_data_amount - 1);
  }

  bool Pop(size_type pos)
  {
    if (pos >= m_data_amount)
      return false;

    for (size_type i = pos + 1; i < m_data_amount; ++i)
      m_data_struct[i - 1] = std::move(m_data_struct[i]);

    --m_data_amount;
    shrinkIfNeeded();
    return true;
  }

  Vector &Swap(Vector &other) noexcept
  {
    if (this == &other)
      return *this;

    std::swap(m_buffer_size, other.m_buffer_size);
    std::swap(m_data_amount, other.m_data_amount);
    std::swap(m_buff_preinit, other.m_buff_preinit);
    std::swap(m_data_struct, other.m_data_struct);
    return *this;
  }

  Vector &Copy(const Vector &other) { return (*this = other); }

  bool Reset()
  {
    T *fresh = m_buff_preinit ? new T[m_buff_preinit] : nullptr;
    delete[] m_data_struct;
    m_data_struct = fresh;
    m_buffer_size = m_buff_preinit;
    m_data_amount = 0;
    return true;
  }

  bool Delete() noexcept
  {
    const bool hadStorage = m_data_struct != nullptr;
    delete[] m_data_struct;
    m_data_struct = nullptr;
    m_buffer_size = 0;
    m_data_amount = 0;
    m_buff_preinit = 0;
    return hadStorage;
  }

private:
  size_type m_buffer_size;
  size_type m_data_amount;
  size_type m_buff_preinit;
  T *m_data_struct;

  void reallocate(size_type newCapacity)
  {
    if (newCapacity < m_data_amount)
      throw std::length_error("Vector capacity is smaller than its size");

    T *fresh = newCapacity ? new T[newCapacity] : nullptr;
    try
    {
      for (size_type i = 0; i < m_data_amount; ++i)
        fresh[i] = m_data_struct[i];
    }
    catch (...)
    {
      delete[] fresh;
      throw;
    }

    delete[] m_data_struct;
    m_data_struct = fresh;
    m_buffer_size = newCapacity;
  }

  void grow()
  {
    if (m_buffer_size > std::numeric_limits<size_type>::max() / 2)
      throw std::length_error("Vector capacity overflow");
    reallocate(m_buffer_size == 0 ? 1 : m_buffer_size * 2);
  }

  void shrinkIfNeeded()
  {
    if (m_buffer_size <= m_buff_preinit || m_data_amount > m_buffer_size / 4)
      return;

    size_type next = m_buffer_size / 2;
    if (next < m_buff_preinit)
      next = m_buff_preinit;
    if (next < m_data_amount)
      next = m_data_amount;

    if (next != m_buffer_size)
      reallocate(next);
  }
};
