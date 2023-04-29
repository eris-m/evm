#define EVM_INTERNAL
#include <evm/loading.h>

#include <stdexcept>
#include <string>
#include <string_view>
#include <type_traits>

namespace evm
{

template <typename T>
static uint64_t
basic_size ()
{
  return sizeof (T);
}

template <typename T, typename A>
static uint64_t
basic_size (const A)
{
  return basic_size<T> ();
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

template <typename T>
static void
basic_save (const T &value, uint8_t *buff)
{
  auto *bytes = reinterpret_cast<const uint8_t *> (&value);

  for (uint64_t i = 0; i < sizeof (T); i++)
    buff[i] = bytes[i];
}

static uint64_t
string_load_size (const uint8_t *buffer)
{
  return basic_load<uint64_t> (buffer);
}

template <typename S>
static uint64_t
string_save_size (const S &s)
{
  return s.length ();
}

static std::string
string_load (const uint8_t *buffer)
{
  auto size = string_load_size (buffer);
  buffer += basic_size<uint64_t> ();

  std::string str;
  str.reserve (size);

  for (uint64_t i = 0; i < size; i++)
    str[i] = static_cast<char> (buffer[i]);

  return str;
}

static std::string_view
string_view_load (const uint8_t *)
{
  throw std::runtime_error (
      "Tried to load std::string_view from memory (which is not supported).");
}

template <typename S>
static void
string_save (const S &s, uint8_t *buffer)
{
  for (uint64_t i = 0; i < string_save_size (s); i++)
    buffer[i] = static_cast<uint8_t> (s[i]);
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

template <>
ls_info<std::string>
primitive_ls_info<std::string> ()
{
  return ls_info<std::string>{ .load_size = string_load_size,
                               .save_size = string_save_size<std::string>,
                               .load = string_load,
                               .save = string_save<std::string> };
}

template <>
ls_info<std::string_view>
primitive_ls_info<std::string_view> ()
{
  return ls_info<std::string_view>{ .load_size = string_load_size,
                                    .save_size
                                    = string_save_size<std::string_view>,
                                    .load = string_view_load,
                                    .save = string_save<std::string_view> };
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

} // evm
