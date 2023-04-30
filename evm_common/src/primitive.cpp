#include <evm/primitive.h>

#include <evm/loading.h>
#include <stdexcept>
#include <utility>

namespace evm
{

/**
 * @brief Macro to instance the provided macro @c M for all primitive types
 */
#define INSTANCE_MACRO(M)                                                     \
  M (I8_TYPE);                                                                \
  M (I16_TYPE);                                                               \
  M (I32_TYPE);                                                               \
  M (I64_TYPE);                                                               \
  M (U8_TYPE);                                                                \
  M (U16_TYPE);                                                               \
  M (U32_TYPE);                                                               \
  M (U64_TYPE);                                                               \
  M (F32_TYPE);                                                               \
  M (F64_TYPE);

template <primitive_type TY>
std::optional<primitive_value_t<TY>>
get_primitive (primitive_value value)
{
  // return nullopt if type is wrong.
  if (value.index () != TY)
    return std::nullopt;

  return std::get<TY> (value);
}

template <primitive_type TYPE>
primitive_value
make_primitive (primitive_value_t<TYPE> value)
{
  auto idx = std::in_place_index_t<TYPE> ();
  return primitive_value (idx, value);
}

primitive_type
primitive_get_type (primitive_value value)
{
  return static_cast<primitive_type> (value.index ());
}

template <primitive_type TYPE>
static primitive_value
load_primitive_raw (const uint8_t *buffer)
{
  // load info.
  auto val_ls_info = value_ls_info<primitive_value_t<TYPE>> ();
  // load value.
  auto val = val_ls_info.load (buffer);

  return primitive_value (val);
}

static primitive_type
load_primitive_type (const uint8_t *buffer)
{
  return static_cast<primitive_type> (*buffer);
}

primitive_value
load_primitive (primitive_type type, const uint8_t *buffer)
{
#define CASE_OF(V)                                                            \
  case V:                                                                     \
    return load_primitive_raw<V> (buffer)

  switch (type)
    {
      INSTANCE_MACRO (CASE_OF);
    default:
      throw std::runtime_error ("Invalid Type Specifier.");
    }

#undef CASE_OF
}

primitive_value
load_primitive (const uint8_t *buffer)
{
  auto type = load_primitive_type (buffer);

  // load with explicit type.
  return load_primitive (type, buffer + 1);
}

static void
save_type (primitive_type type, uint8_t *buffer)
{
  // Only one byte, so it just copies.
  *buffer = static_cast<uint8_t> (type);
}

void
save_primitive (const primitive_value &value, uint8_t *buffer, bool fat)
{
  auto type = primitive_get_type (value);

  // save type info if fat.
  if (fat)
    {
      save_type (type, buffer);
      buffer++;
    }

  // Function to save value.
  auto save_value = [buffer] (auto v) {
    auto info = value_ls_info<typeof (v)> ();
    info.save (v, buffer);
  };

  std::visit (save_value, value);
}

uint64_t
primitive_load_size (primitive_type type, const uint8_t *)
{
#define CASE_OF(T)                                                            \
  case T:                                                                     \
    return sizeof (primitive_value_t<T>)

  switch (type)
    {
      // all the cases.
      INSTANCE_MACRO (CASE_OF);
    default:
      throw std::runtime_error ("Invalid Type Specifier.");
    }

#undef CASE_OF
}

uint64_t
primitive_load_size (const uint8_t *buffer)
{
  auto type = load_primitive_type (buffer);
  return 1 + primitive_load_size (type, buffer);
}

uint64_t
primitive_save_size (const primitive_value &value, bool fat)
{
  auto type = primitive_get_type (value);
  // passing in nullptr is fine, primitive_load_size doesn't use it.
  auto base = primitive_load_size (type, nullptr);

  if (fat)
    {
      base += 1;
    }

  return base;
}

const std::string_view
primitive_type_name (primitive_type t)
{
#define CASE_OF(T)                                                            \
  case T:                                                                     \
    return #T;

  switch (t)
    {
      INSTANCE_MACRO (CASE_OF);
    default:
      return "";
    }

#undef CASE_OF
}

// Instance generic functions for all values possible values.
#define PRIM_INST(TY)                                                         \
  template std::optional<primitive_value_t<TY>> get_primitive<TY> (           \
      primitive_value);                                                       \
  template primitive_value make_primitive<TY> (primitive_value_t<TY> value);

// Instance generic functions for all values of primitive_type
INSTANCE_MACRO (PRIM_INST);
}
