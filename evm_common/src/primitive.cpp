#include <evm/primitive.h>

#include <evm/loading.h>
#include <stdexcept>
#include <utility>

namespace evm
{

template <primitive_type TY>
std::optional<primitive_value_t<TY>>
get_primitive (primitive_value value)
{
  if (value.index () != TY)
    return std::nullopt;

  return std::get<TY> (value);
}

template <primitive_type TYPE>
primitive_value
make_primitive (primitive_value_t<TYPE> value)
{
  return primitive_value (std::in_place_index_t<TYPE> (), value);
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
  auto val_ls_info = value_ls_info<primitive_value_t<TYPE>> ();

  return primitive_value (val_ls_info.load (buffer));
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
      CASE_OF (I8_TYPE);
      CASE_OF (I16_TYPE);
      CASE_OF (I32_TYPE);
      CASE_OF (I64_TYPE);
      CASE_OF (U8_TYPE);
      CASE_OF (U16_TYPE);
      CASE_OF (U32_TYPE);
      CASE_OF (U64_TYPE);
      CASE_OF (F32_TYPE);
      CASE_OF (F64_TYPE);
    default:
      throw std::runtime_error ("Invalid Type Specifier.");
    }
#undef CASE_OF
}
primitive_value
load_primitive (const uint8_t *buffer)
{
  auto type = load_primitive_type (buffer);

  return load_primitive (type, buffer + 1);
}

void
save_type (primitive_type type, uint8_t *buffer)
{
  *buffer = static_cast<uint8_t> (type);
}

void save_value (auto v, uint8_t *buffer)
{
  value_ls_info<typeof (v)> ().save (v, buffer);
}

void
save_primitive (primitive_value value, uint8_t *buffer, bool fat)
{
  auto type = primitive_get_type (value);

  if (fat)
    {
      save_type (type, buffer);
      buffer++;
    }

  std::visit (
      [buffer] (auto v) { save_value (v, buffer); },
      value);
}

// Instance generic functions for all values possible values.
#define PRIM_INST(TY)                                                         \
  template std::optional<primitive_value_t<TY>> get_primitive<TY> (           \
      primitive_value);                                                       \
  template primitive_value make_primitive<TY> (primitive_value_t<TY> value);

PRIM_INST (I8_TYPE);
PRIM_INST (I16_TYPE);
PRIM_INST (I32_TYPE);
PRIM_INST (I64_TYPE);

PRIM_INST (U8_TYPE);
PRIM_INST (U16_TYPE);
PRIM_INST (U32_TYPE);
PRIM_INST (U64_TYPE);

PRIM_INST (F32_TYPE);
PRIM_INST (F64_TYPE);
}
