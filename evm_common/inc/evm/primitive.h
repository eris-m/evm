#ifndef EVM_COMMON_VALUES_H_
#define EVM_COMMON_VALUES_H_

#include <cstdint>
#include <optional>
#include <variant>

namespace evm
{

/**
 * @brief This enum contains the different types, such as i8 (8-bit signed
 * integer).
 * @details The type names are fairly self explanatory, taking the form @c
 * <prefix><size>. A prefix of @c I means a signed integer, @c U an unsigned
 * integer, and @c F a floating point.
 *
 * Currently only numbers are implemented.
 */
enum primitive_type : uint8_t
{
  I8_TYPE,
  I16_TYPE,
  I32_TYPE,
  I64_TYPE,
  U8_TYPE,
  U16_TYPE,
  U32_TYPE,
  U64_TYPE,
  F32_TYPE,
  F64_TYPE,
};

/**
 * @brief A primitive value.
 * This is a wrapper over the raw types.
 * To get the raw values, see @c get_primitive.
 */
using primitive_value
    = std::variant<int8_t, int16_t, int32_t, int64_t, uint8_t, uint16_t,
                   uint32_t, uint64_t, float, double>;

/**
 * @brief The associated type for the given @c primitive_type.
 */
template <primitive_type TYPE>
using primitive_value_t = std::variant_alternative_t<TYPE, primitive_value>;

/**
 * @brief Gets the value as an optional out of the @c primitive_value wrapper.
 * @return An optional with value if the @c primitive_value contains the given
 * type, otherwise @c nullopt.
 */
template <primitive_type TYPE>
std::optional<primitive_value_t<TYPE>> get_primitive (primitive_value value);

/**
 * @brief Makes a primitive value out of the value.
 * Uses @c TYPE to figure out what variant to make.
 * @tparam TYPE Type to make.
 * @return
 */
template <primitive_type TYPE>
primitive_value make_primitive (primitive_value_t<TYPE> value);

}

#endif // EVM_COMMON_VALUES_H_
