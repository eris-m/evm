#include <evm/loading.h>
#include <gtest/gtest.h>

TEST (loading_tests, uint16_t_load)
{
  constexpr uint8_t data[] = { 0x00, 0x01 }; // Should be 256
  constexpr auto expected = 256;

  auto u16_ls_info = evm::value_ls_info<uint16_t> ();
  auto u16_value = u16_ls_info.load (data);

  EXPECT_EQ (u16_value, expected);
}

/**
 * A struct that implements custom loading behaviour
 */
struct custom_loader_t
{
  int x;

  static constexpr evm::ls_info<custom_loader_t>
  ls_info ()
  {
    return evm::ls_info<custom_loader_t>{
      .load_size = ld_size,
      .save_size = sv_size,
      .load = load,
      .save = save,
    };
  }

private:
  static uint64_t
  ld_size (const uint8_t *)
  {
    return sizeof (custom_loader_t);
  }

  static uint64_t
  sv_size (const custom_loader_t &value)
  {
    return sizeof (value);
  }

  static custom_loader_t
  load (const uint8_t *buffer)
  {
    int x = evm::value_ls_info<int> ().load (buffer);
    return custom_loader_t{ .x = x + 1 };
  }

  static void
  save (const custom_loader_t &self, uint8_t *buffer)
  {
    evm::value_ls_info<int> ().save (self.x, buffer);
  }
};

TEST (loading_tests, custom_test)
{
  constexpr size_t buff_size = 16;
  constexpr auto c_ls_info = custom_loader_t::ls_info ();

  uint8_t buffer[buff_size];
  custom_loader_t value = custom_loader_t{ .x = 50 };

  c_ls_info.save (value, buffer);

  auto value_loaded = c_ls_info.load (buffer);

  EXPECT_EQ (value_loaded.x, value.x + 1);
}

TEST (loading_tests, string_test)
{
  const auto str_view_info = evm::value_ls_info<std::string_view> ();
  const auto str_info = evm::value_ls_info<std::string> ();

  std::string_view str = "hi!";
  uint8_t buffer[128];

  str_view_info.save (str, buffer);

  std::string str_loaded = str_info.load (buffer);

  EXPECT_STREQ (str_loaded.data (), str.data ());
}
