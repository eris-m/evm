#include <gtest/gtest.h>

#include <evm/primitive.h>
#include <cmath>

TEST (primitive_tests, get_set_test)
{
  constexpr float f32_value = 10.0f;
  constexpr int8_t i8_value = -50;

  auto val_f32 = evm::make_primitive<evm::F32_TYPE> (f32_value);
  auto val_i8 = evm::primitive_value (i8_value);

  auto f32 = evm::get_primitive<evm::F32_TYPE> (val_f32);
  auto i8 = evm::get_primitive<evm::I8_TYPE> (val_i8);

  EXPECT_TRUE (f32.has_value ());
  EXPECT_TRUE (i8.has_value ());

  EXPECT_EQ (*f32, f32_value);
  EXPECT_EQ (*i8, i8_value);
}

TEST (primitive_tests, thin_load_save_test)
{
  auto val = evm::make_primitive<evm::F32_TYPE> (1.1e12f);
  auto val2 = evm::make_primitive<evm::F64_TYPE> (9.6e-53);

  uint8_t buffer[16] = {};

  constexpr auto val_offset = 0;
  constexpr auto val2_offset = 4;

  evm::save_primitive (val, buffer + val_offset);
  evm::save_primitive (val2, buffer + val2_offset);

  auto val_loaded = evm::load_primitive (evm::F32_TYPE, buffer + val_offset);
  auto val2_loaded = evm::load_primitive (evm::F64_TYPE, buffer + val2_offset);

  EXPECT_EQ (val_loaded, val);
  EXPECT_EQ (val2_loaded, val2);
}
