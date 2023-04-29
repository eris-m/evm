#define EVM_INTERNAL
#include <evm/loading.h>

#include <stdexcept>
#include <string>
#include <string_view>
#include <type_traits>

namespace evm
{

template <typename T, typename A> static uint64_t basic_size (const A);
template <typename T> static T basic_load (const uint8_t *);
template <typename T> static uint64_t basic_save (const T &, const uint8_t *);

template <typename T>
static uint64_t
basic_size ()
{
  return sizeof (T);
}

template <typename T, typename A>
static uint64_t
basic_size (A)
{
  return basic_size<T> ();
}

template <>
uint64_t
basic_size<std::string> (const uint8_t *buffer)
{
  return basic_load<uint64_t> (buffer);
}

template <>
uint64_t
basic_size<std::string_view> (const uint8_t *buffer)
{
  return basic_load<uint64_t> (buffer);
}

template <>
uint64_t
basic_size<std::string> (const std::string &str)
{
  return str.length ();
}

template <>
uint64_t
basic_size<std::string_view> (const std::string_view &str)
{
  return str.length ();
}

template <typename T>
static T
basic_load (const uint8_t *buff)
{
  T output;
  // interpret T as bytes.
  auto *bytes = reinterpret_cast<uint8_t *> (&output);

  for (uint64_t i = 0; i < sizeof (T); i++)
    bytes[i] = buff[i];

  return output;
}

template <>
std::string
basic_load<std::string> (const uint8_t *buff)
{
  auto size = basic_size<std::string> (buff);
  buff += basic_size<uint64_t> ();

  std::string str;
  str.reserve (size);

  for (uint64_t i = 0; i < size; i++)
    {
      auto *character = reinterpret_cast<const char *> (&buff[i]);
      str.append (character, 1);
    }

  return str;
}

template <>
std::string_view
basic_load<std::string_view> (const uint8_t *buff)
{
  throw std::runtime_error (
      "Tried to load std::string_view from memory (which is not supported).");
}

template <typename T>
static void
basic_save (const T &value, uint8_t *buff)
{
  auto *bytes = reinterpret_cast<const uint8_t *> (&value);

  for (uint64_t i = 0; i < sizeof (T); i++)
    buff[i] = bytes[i];
}

template <typename S>
static void
str_save (const S &value, uint8_t *buff)
{
  auto size = basic_size<std::string> (value);

  // write size
  basic_save<uint64_t> (size, buff);
  buff += 8;

  // write bytes
  for (uint64_t i = 0; i < size; i++)
    buff[i] = static_cast<uint8_t> (value[i]);
}

template <>
void
basic_save<std::string> (const std::string &value, uint8_t *buff)
{
  str_save<std::string> (value, buff);
}

template <>
void
basic_save<std::string_view> (const std::string_view &value, uint8_t *buff)
{
  str_save<std::string_view> (value, buff);
}

template <typename T>
ls_info<T>
primitive_ls_info ()
{
  return ls_info<T>{
    .load_size = basic_size<T>,
    .save_size = basic_size<T>,
    .load = basic_load<T>,
    .save = basic_save<T>,
  };
}

#define PRIMITIVE_LS_INFO(T) template ls_info<T> primitive_ls_info<T> ()

PRIMITIVE_LS_INFO (uint8_t);
PRIMITIVE_LS_INFO (uint16_t);
PRIMITIVE_LS_INFO (uint32_t);
PRIMITIVE_LS_INFO (uint64_t);
PRIMITIVE_LS_INFO (int8_t);
PRIMITIVE_LS_INFO (int16_t);
PRIMITIVE_LS_INFO (int32_t);
PRIMITIVE_LS_INFO (int64_t);
PRIMITIVE_LS_INFO (float);
PRIMITIVE_LS_INFO (double);

PRIMITIVE_LS_INFO (std::string);
PRIMITIVE_LS_INFO (std::string_view);

} // evm
