#include <evm/instruction.h>

namespace evm
{

instruction_args
instruction_args::load (instruction_kind kind, const uint8_t *buffer)
{
  instruction_args args;

  switch (kind)
    {
    case instruction_kind::lonely:
      args.lonely = {};
    }

  return args;
}

void
instruction_args::save(const instruction_args &args, instruction_kind kind, uint8_t *buffer)
{
  switch (kind)
    {
    case instruction_kind::lonely:
      return;
    }
}

static uint64_t
opcode_ld_size (const uint8_t *)
{
  return sizeof (opcode);
}

static uint64_t
opcode_st_size (const opcode &)
{
  return sizeof (opcode);
}

opcode
load_opcode (const uint8_t *buffer)
{
  auto byte = buffer[0];
  return static_cast<opcode> (byte);
}

void
save_opcode (const opcode &self, uint8_t *buffer)
{
  auto byte = static_cast<uint8_t> (self);
  buffer[0] = byte;
}

ls_info<opcode>
opcode_ls_info ()
{
  return ls_info<opcode>{ .load_size = opcode_ld_size,
                          .save_size = opcode_st_size,
                          .load = load_opcode,
                          .save = save_opcode };
}

} // evm
