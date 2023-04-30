/** @file
 *
 * @brief This file contains the logic for primitive types.
 * It contains loading and saving information (@c evm::load_primitive and @c evm::save_primitive),
 * type information, and a @c std::variant type for convenience.
 *
 */

#ifndef EVM_COMMON_VALUES_H_
#define EVM_COMMON_VALUES_H_

#include <cstdint>
#include <optional>
#include <string_view>
#include <variant>

namespace evm
{

/**
 * @brief This enum contains the different types, such as i8 (8-bit signed
 * integer).
 *
 * The type names are fairly self explanatory, taking the form @c
 * <prefix><size>_TYPE. A prefix of @c I means a signed integer, @c U an unsigned
 * integer, and @c F a floating point.
 *
 * Currently only numbers are implemented.
 */
enum primitive_type : uint8_t
{
  I8_TYPE, /**< 8-bit signed integer */
  I16_TYPE, /**< 16-bit signed integer */
  I32_TYPE, /**< 32-bit signed integer */
  I64_TYPE, /**< 64-bit signed integer */
  U8_TYPE, /**< 8-bit unsigned integer */
  U16_TYPE, /**< 16-bit unsigned integer */
  U32_TYPE, /**< 32-bit unsigned integer */
  U64_TYPE, /**< 64-bit unsigned integer */
  F32_TYPE, /**< 32-bit floating point number */
  F64_TYPE, /**< 64-bit floating point number */
};

/**
 * @brief A primitive value.
 * This is a wrapper over the raw types.
 *
 * This value in memory is always 64-bits,
 * due to limitations of @c std::variant.
 *
 * @see evm::get_primitive ().
 */
using primitive_value
    = std::variant<int8_t, int16_t, int32_t, int64_t, uint8_t, uint16_t,
                   uint32_t, uint64_t, float, double>;

/**
 * @brief The associated type for the given @c primitive_type.
 *
 * This type is instanciated for each member of @c primitive_type
 * and **will** produce a linker error if you try use an arbitrary integer.
 */
template <primitive_type TYPE>
using primitive_value_t = std::variant_alternative_t<TYPE, primitive_value>;

/**
 * @brief Gets the value as an optional out of the @c primitive_value wrapper.
 *
 * This function is instanciated for each member of @c primitive_type, 
 * and will produce a linker error if you try use an arbitrary integer.
 *
 * @return A value if the @c primitive_value contains the given
 * type, otherwise @c std::nullopt.
 */
template <primitive_type TYPE>
std::optional<primitive_value_t<TYPE>> get_primitive (primitive_value value);

/**
 * @brief Makes a primitive value out of the value.
 * Uses @c TYPE to figure out what variant to make.
 *
 * This function is instanciated for each member of @c primitive_type, 
 * and will produce a linker error if you try use an arbitrary integer.
 *
 * @tparam TYPE Type to make.
 */
template <primitive_type TYPE>
primitive_value make_primitive (primitive_value_t<TYPE> value);

/**
 * @brief Returns the type of value stored within the primitive_value.
 *
 * This function runs in *O(1)* time.
 */
primitive_type primitive_get_type (primitive_value val);

/**
 * @brief Loads a primitive value given the type.
 *
 * This overload does not load the type information
 * and if at the buffer address there is a fat primitive value
 * then you will get incorrect results.
 * For this reason, if you know that the value at `*buffer` will be
 * a fat primitive, please pass in `buffer + 1`.
 *
 * @param type Type of the primitive.
 * @param buffer Buffer to load from.
 */
primitive_value load_primitive (primitive_type type, const uint8_t *buffer);
/**
 * @brief Loads a primitive value,
 * using the first byte to determain the type.
 *
 * The other overload of @c load_primitive should be preferred if the type is
 * known.
 * This overload loads fat primitives.
 * This will return incorrect results if there is a thin primitive at `*buffer`.
 *
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
void save_primitive (const primitive_value &value, uint8_t *buffer,
                     bool fat = false);

/**
 * @brief The size needed to load a primitive of type @c type.
 *
 * This returns the size without the type as it presumes you want a thin primitive,
 * see the other overload of this function for fat primitives.
 *
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
 * @param value Value who's size is calculated.
 * @param fat Whether or not to use a fat primitive.
 */
uint64_t primitive_save_size (const primitive_value &value, bool fat = false);

/**
 * @brief Gets the type name of the type.
 */
const std::string_view primitive_type_name (primitive_type t);

}

#endif // EVM_COMMON_VALUES_H_
