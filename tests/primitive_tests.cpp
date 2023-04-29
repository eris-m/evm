#include <gtest/gtest.h>

#include <evm/primitive.h>

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
