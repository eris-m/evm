#ifndef EVM_COMMON_VALUES_H_
#define EVM_COMMON_VALUES_H_

#include <cstdint>
#include <optional>
#include <variant>
#include <string_view>

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

primitive_type primitive_get_type (primitive_value val);

/**
 * @brief Loads a primitive value given the type.
 * @param type Type of the primitive.
 * @param buffer Buffer to load from.
 */
primitive_value load_primitive (primitive_type type, const uint8_t *buffer);
/**
 * @brief Loads a primitive value,
 * using the first byte to determain the type.
 * The other overload of @c load_primitive should be preferred if the type is
 * known.
 * @param buffer Buffer to load from.
 */
primitive_value load_primitive (const uint8_t *buffer);

/**
 * @brief Saves the given primitive into the buffer.
 * @param value Value to save.
 * @param buffer Buffer to save into.
 * @param fat Whether or not the primitive should be a fat primitive,
 * ie one that saves a type specifying byte along with the value.
 */
void save_primitive (const primitive_value &value, uint8_t *buffer, bool fat = false);

/**
 * @brief The size needed to load a primitive of type @c type.
 * @param type Type of the primitive.
 */
uint64_t primitive_load_size (primitive_type type, const uint8_t *buffer);
/**
 * @brief The size needed to load a primitive with the type contained in the
 * first byte of the buffer.
 */
uint64_t primitive_load_size (const uint8_t *buffer);
/**
 * @brief The size needed to save the given primitive into a buffer.
 */
uint64_t primitive_save_size (const primitive_value &value);

/**
 * @brief Gets the type name of the type.
 */
const std::string_view primitive_type_name (primitive_type t);

}

#endif // EVM_COMMON_VALUES_H_
