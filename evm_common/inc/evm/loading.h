#ifndef EVM_COMMON_LOADING_H_
#define EVM_COMMON_LOADING_H_

#include <cstdint>

namespace evm
{

/**
 * A struct containing the loading and saving information for a type.
 * The name means load save info.
 */
template <typename T> struct ls_info
{
  /**
   * This function gets the size of the value before it is loaded.
   */
  uint64_t (*load_size) (const uint8_t *);
  /**
   * This function gets the size of the type passed in as a @c void @c * for
   * saving.
   */
  uint64_t (*save_size) (const T &);

  /**
   * This function loads the value and returns the result.
   * @return The value as a @c void*, such that it can be cast to @c T*
   * where @c T is the type loaded. This is freed if @c load_fn_ownership is
   * @c LOAD_FN_TRANSFER
   */
  T (*load) (const uint8_t *);

  /**
   * This function saves the function into the buffer.
   */
  void (*save) (const T &, uint8_t *);
}; // struct ls_info

/**
 * @brief The @c ls_info for some primitive types,
 * This includes numeric types (such as int64_t) for now.
 * @return @c ls_info for the primitive.
 */
template <typename T> ls_info<T> primitive_ls_info ();


} // evm

#endif // EVM_COMMON_LOADING_H_
