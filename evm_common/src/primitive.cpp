#include <evm/primitive.h>

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
