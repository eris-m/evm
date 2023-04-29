#define EVM_INTERNAL
#include <evm/loading.h>

template <typename T>
static uint64_t
basic_ld_size (const uint8_t *)
{
  return sizeof (T);
}

template <typename T>
static uint64_t
basic_save_size (const T &)
{
  return sizeof (T);
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

template <typename T>
evm::ls_info<T>
evm::primitive_ls_info ()
{
  return evm::ls_info<T>{
    .load_size = basic_ld_size<T>,
    .save_size = basic_save_size<T>,
    .load = basic_load<T>,
    .save = basic_save<T>,
  };
}


#define PRIMITIVE_LS_INFO(T) template evm::ls_info<T> evm::primitive_ls_info<T> ()

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
